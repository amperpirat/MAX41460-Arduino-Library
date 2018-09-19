/**********************************************************************
* Copyright (C) 2018 Maxim Integrated Products, Inc., All Rights Reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
* OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
* Except as contained in this notice, the name of Maxim Integrated
* Products, Inc. shall not be used except as stated in the Maxim Integrated
* Products, Inc. Branding Policy.
*
* The mere transfer of this software does not imply any licenses
* of trade secrets, proprietary technology, copyrights, patents,
* trademarks, maskwork rights, or any other form of intellectual
* property whatsoever. Maxim Integrated Products, Inc. retains all
* ownership rights.
* 
* Authors: 
* Ole Dreessen; ole.dreessen@maximintegrated.com
* 
* Revisions:
* 0.1.0       18.09.2018      initial code
* 
**********************************************************************/


#include <MAX41460-Arduino-Library.h>



/**********************************************************************
*@brief The MAX41460 is a UHF sub-GHz ISM/SRD transmitter is designed to transmit On-Off 
*Keying (OOK), AmplitudeShift Keying (ASK), Frequency-Shift Keying (FSK), and Gaussian 
*(G)FSK (or 2GFSK) data in the 286MHz to 960MHz frequency range. It integrates a fractional 
*phaselocked-loop (PLL) so a single low cost crystal can be used to generate commonly used 
*world-wide sub-GHz frequencies. The fast response time of the PLL allows for frequency 
*hopping spread spectrum protocols for increased range and security. The only frequency 
*dependent components required are for the external antenna matching network.
*The crystal based architecture of the MAX41460 provides greater modulation depth, 
*faster frequency settling, higher tolerance of the transmit frequency, and reduced 
*temperature dependence. The MAX41460 provides output power up to +13dBm into 
*a 50Ω load while only drawing <8mA for ASK (Manchestercoded) and <12mA for (G)FSK 
*transmission at 315MHz. The output load can be adjusted to increase power up to +16dBm,
*and a PA boost mode can be enabled at frequencies above 850MHz to compensate for
*losses. The PA output power can also be controlled using programmable register settings.
*The MAX41460 features single supply operation from +1.8V to +3.6V. The device has an 
*auto-shutdown feature to extend battery life and a fast oscillator wake-up on data activity 
*detection. A serial programmable interface make the MAX41460 compatible with almost 
*any microcontroller or code-hopping generator. The MAX41460 is available in a 10-pin 
*TSSOP package and is specified over the -40°C to +105°C extended temperature range. 
*The MAX41460 has an ESD rating of 2.5kV HBM.
*
*Ressources can be found at
*https://www.maximintegrated.com/en/products/power/battery-management/MAX77650.html
*https://www.maximintegrated.com/en/app-notes/index.mvp/id/6428
**********************************************************************/
   
void MAX41460_init(part_used device, byte MAX41460_port_number);{
  #if MAX41460_debug Serial.begin(115200); //enable serial interface and set it up
  #if MAX41460_debug Serial.println("Debug Port enabled for MAX41460-4 family debug messages.");
   
  if (device == MAX41460) {
  	//Code to init SPI
  } else {
  	//Code to init I2C
	#if MAX41460_debug Serial.print("Enable and setup I2C port: ");
	#if MAX41460_debug Serial.print(MAX41460_port_number);
	switch (MAX41460_port_number){
		case 0: 
		  Wire.beginn();
		break;
		case 1: 
		  Wire1.beginn();
		break;
		case 2: 
		  Wire2.beginn();
		break;
		default: 
		  Wire.beginn();
		break;						
	}	
  }
}

int MAX41460_read_register(part_used device, byte MAX41460_port_number, byte ADDR){
  int retval = -1; 
  
  if (device == MAX41460) {
  	//Code to init SPI
  } else {
  	//Code to init I2C
	#if MAX41460_debug Serial.print("Enable and setup I2C port: ");
	#if MAX41460_debug Serial.print(MAX41460_port_number);
	switch (MAX41460_port_number){
		case 0: 
          Wire.beginTransmission(MAX77650_ADDR);
          Wire.write(ADDR);
          Wire.endTransmission();
          Wire.requestFrom(MAX77650_ADDR,1);
          if (Wire.available()<=1)
           retval = (Wire.read());  	
		  break;
		case 1: 
          Wire1.beginTransmission(MAX77650_ADDR);
          Wire1.write(ADDR);
          Wire1.endTransmission();
          Wire1.requestFrom(MAX77650_ADDR,1);
          if (Wire1.available()<=1)
           retval = (Wire1.read());
		break;
		case 2: 
          Wire2.beginTransmission(MAX77650_ADDR);
          Wire2.write(ADDR);
          Wire2.endTransmission();
          Wire2.requestFrom(MAX77650_ADDR,1);
          if (Wire2.available()<=1)
           retval = (Wire2.read()); 
		break;
		default: 
          Wire.beginTransmission(MAX77650_ADDR);
          Wire.write(ADDR);
          Wire.endTransmission();
          Wire.requestFrom(MAX77650_ADDR,1);
          if (Wire.available()<=1)
           retval = (Wire.read());  	
		break;						
	}	
  }  
}


//Read functions for Configuration Register 1
byte MAX41460_getXOCLKDELAY(void){ //Start delay before enabling XO clock to digital block; Return Value: 0x0 No delay, 0x1 XO clock is enabled after 16 cycles,  0x2 XO clock is enabled after 32 cycles, 0x3 XO clock is enabled after 64 cycles
 return ((MAX41460_read_register(MAX41460_CFG1) >> 6) & 0b00000011);   
}

byte MAX41460_getXOCLKDIV(void){ // XO clock division ratio for digital block; 0x0: Divide XO clock by 4 for digital clock 0x1: Divide XO clock by 5 for digital clock. High time is 2 cycles, low time is 3 cycles 0x2: Divide XO clock by 6 for digital clock. 0x3: Divide XO clock by 7 for digital clock. High, time is 3 cycles, and low time is 4 cycles.
return ((MAX41460_read_register(MAX41460_CFG1) >> 4) & 0b00000011);   
}

boolean MAX41460_getFSKSHAPE(void){ //Sets the state of FSK Gaussain Shapin; 0x0: FSK Shaping disabled, 0x1: FSK Shaping enabled
return ((MAX41460_read_register(MAX41460_CFG1) >> 2) & 0b00000001);   
}

boolean MAX41460_getSYNC(void){ //Controls if clock output acts as an input. When an input, it will sample the DATA pin; 0x0 , 0x1
return ((MAX41460_read_register(MAX41460_CFG1) >> 1) & 0b00000001);   
}

boolean MAX41460_getMODMODE(void){ //Configures modulator mode; 0x0: ASK Mode, 0x1: FSK Mode
return ((MAX41460_read_register(MAX41460_CFG1) >> 0) & 0b00000001);   
}

//Read functions for Configuration Register 2
byte MAX41460_getCLKOUT_DELAY(void){ //Selects the delay when CLKOUT starts toggling upon exiting SHUTDOWN mode, in divided XO clock cycles; 0x0: CLKOUT will start toggling after 64 cycles whenever moving into normal mode from shutdown mode 0x1: CLKOUT will start toggling after 128 cycles whenever moving into normal mode from shutdown mode 0x2: CLKOUT will start toggling after 256 cycles whenever moving into normal mode from shutdown mode 0x3: CLKOUT will start toggling after 512 cycles whenever moving into normal mode from shutdown mode
return ((MAX41460_read_register(MAX41460_CFG2) >> 6) & 0b00000011);  
}

//Read functions for Configuration Register 3 *** not available for MAX41460 ***
byte MAX41460_getBCLK_PREDIV(void){ //Baud clock predivision ratio. Valid values are from 3 to 255; 0x00: RESERVED 0x01: RESERVED 0x02: RESERVED 0x03: Divide by 3 ... 0xFF: Divide by 255
return ((MAX41460_read_register(MAX41460_CFG3) >> 0) & 0b00000011);  
}

//Read functions for Configuration Register 4
byte MAX41460_getPWDN_MODE(void){ //Power Down Mode Select; 0x0: SHUTDOWN low power state is enabled. While entering low power state, XO, PLL, and PA are shutdown. 0x1: STANDBY low power state is enabled. While entering low power state, XO is enabled. PLL and PA are shutdown 0x2: FAST WAKEUP low power state is enabled. While entering low power state, XO and PLL are enabled. PA is shutdown. 0x3: Will revert to 0x2
return ((MAX41460_read_register(MAX41460_CFG4) >> 0) & 0b00000011);  
}

//Read functions for Configuration Register 5
byte MAX41460_getTSTEP(void){ //Controls GFSK shaping. See Digital FSK Modulation section in Datasheet.
return ((MAX41460_read_register(MAX41460_CFG5) >> 0) & 0b00111111);  
}

//Read functions for SHDN Register
boolean MAX41460_getPA_BOOST(void){ //Enables a boost in PA output power for frequencies above 850MHz. This requires a different PA match compared to normal operation. 0x0: PA Output power in normal operation. 0x1: PA Output power in boost mode for more output power.
return ((MAX41460_read_register(MAX41460_SHDN) >> 0) & 0b00000001);  
}

//Read functions for PA1 Register
byte MAX41460_getPAPWR(void){ //Controls the PA output power by enabling parallel drivers; 0x0: Minimum, 1 driver 0x1: 2 Drivers 0x2: 3 Drivers 0x3: 4 Drivers 0x4: 5 Drivers 0x5: 6 Drivers 0x6: 7 Drivers 0x7: 8 Drivers
return ((MAX41460_read_register(MAX41460_PA1) >> 0) & 0b00000111);  
}

//Read functions for PA2 Register
byte MAX41460_getPACAP(void){ //Controls shunt capacitance on PA output in fF; 0x00: 0, 0x01: 175, 0x02: 350, 0x03: 525, 0x04: 700, 0x05: 875, 0x06: 1050, 0x07: 1225, 0x08: 1400, 0x09: 1575, 0x0A: 1750, 0x0B: 1925, 0x0C: 2100, 0x0D: 2275, 0x0E: 2450, 0x0F: 2625, 0x10: 2800, 0x11: 2975, 0x12: 3150, 0x13: 3325, 0x14: 3500, 0x15: 3675, 0x16: 3850, 0x17: 4025, 0x18: 4200, 0x19: 4375, 0x1A: 4550, 0x1B: 4725, 0x1C: 4900, 0x1D: 5075, 0x1E: 5250, 0x1F: 5425
return ((MAX41460_read_register(MAX41460_PA2) >> 0) & 0b00011111);  
}

//Read functions for PLL1 Register
byte MAX41460_getCPLIN(void){ //Sets the level of charge pump offset current for fractional N mode to improve close in phase noise. Set to 'DISABLED' for integer N mode. 0x0: No extra current, 0x1: 5% of charge pump current, 0x2: 10% of charge pump current, 0x3: 15% of charge pump current
return ((MAX41460_read_register(MAX41460_PLL1) >> 6) & 0b00000011);  
}

boolean MAX41460_getFRACMODE(void){ //Sets PLL between fractional-N and integer-N mode. 0x0: Integer N Mode, 0x1: Fractional N Mode
return ((MAX41460_read_register(MAX41460_PLL1) >> 5) & 0b0000001);  
}

byte MAX41460_getLODIV(void){ //0x0: Disabled, 0x1: LC VCO divided by 4, 0x2: LC VCO divided by 8, 0x3: LC VCO divided by 12
return ((MAX41460_read_register(MAX41460_PLL1) >> 1) & 0b0000011);  
}

boolean MAX41460_getLOMODE(void){ //Sets LO generation. For lower power, choose LOWCURRENT. For higher performance, choose LOWNOISE. 0x0: Ring Oscillator Mode, 0x1: LC VCO Mode
return ((MAX41460_read_register(MAX41460_PLL1) >> 0) & 0b0000001);  
}

//Read functions for PLL2 Register
byte MAX41460_getCPVAL(void){ //Sets Charge Pump Current, 0x0: 5µA, 0x1: 10µA, 0x2: 15µA, 0x3: 20µA
return ((MAX41460_read_register(MAX41460_PLL2) >> 0) & 0b0000011);  
}

//Read functions for Configuration Register 6
boolean MAX41460_getSPI_TXEN1(void){ //Transmission enable; 0x0: Transmission disabled, 0x1: Transmission enabled.
return ((MAX41460_read_register(MAX41460_CFG6) >> 1) & 0b0000001);  
}

boolean MAX41460_getFOURWIRE1(void){ //Four wire readback on CLKOUT pin mode; 0x0: Four wire readback disabled, 0x1: Four wire readback enabled.
return ((MAX41460_read_register(MAX41460_CFG6) >> 0) & 0b0000001);  
}

//Read functions for PLL3, PLL4 and PLL5 Register (3 times 8 bit frequency value)
unsigned int MAX41460_getFREQ(void){ //FREQ value to PLL. LO frequency= FREQ<23:0>/2^16*fXTAL
 return ((MAX41460_read_register(MAX41460_PLL3) <<16) +(MAX41460_read_register(MAX41460_PLL4) <<8)+(MAX41460_read_register(MAX41460_PLL5)));
}

//Read functions for PLL6 Register
byte MAX41460_getDELTAF(void){ //For FSK mode, MODMODE=1 and FSKSHAPE=0, sets the frequency deviation from the space frequency for the mark frequency. fDELTA = DELTAF[6:0] * fXTAL/ 8192

}

//Read functions for PLL7 Register
byte MAX41460_getDELTAF_SHAPE(void){ //For FSK mode, MODMODE = 1 and FSKSHAPE = 1, sets the frequency deviation from the space frequency for the mark frequency. fDELTA = DELTAF_SHAPE[3:0] * fXTAL / 81920

}

//Read functions for Configuration Register 7
boolean MAX41460_getSPI_TXEN2(void){ //0x0: Transmission disabled; 0x1: Transmission enabled.

}

boolean MAX41460_getFOURWIRE2(void){ //Four wire readback on CLKOUT pin mode. Aliased address for FOURWIRE1; 0x0: Four wire readback disabled, 0x1: Four wire readback enabled.

}

//I2C Configuration Register 1 and 2 *** not available for MAX41460 ***
boolean MAX41460_getPKTLEN_MODE(void){ //Packet Length Mode; 0x0: PKTLEN[14:0] need not be programmed. FIFO underflow event will be treated as end of packet event. For cases where actual packet length is greater than 32767 bits, this is the only mode that will be supported, and it is expected that the µC will pad such a packet to make it an integral multiple of 8-bits 0x1: PKTLEN[14:0] will provide the length of packet. Once FIFO is read for PKTLEN[14:0] bits, or if FIFO underflow, LF21 will consider that as an end of packet event.

}

unsigned int MAX41460_getPKTLEN(void){ //Packet Length 15 bit of Packet length information

}

//I2C Configuration Register 3 *** not available for MAX41460 ***
byte MAX41460_getI2C_TX_DATA(void){ //Transmit data to be written into FIFO for I2C mode of operation. At this address, I2C register address will not auto increment within an I2C transaction burst, and subsequent writes will keep going to FIFO

}

//I2C Configuration Register 4 and 5 *** not available for MAX41460 ***
boolean MAX41460_getPKTCOMPLETE(void){ //

}

unsigned int MAX41460_getTX_PKTLEN(void){ //Provides status information of bits transmitted for the current packet; 15 bit of Packet length information

}

//I2C Configuration Register 6 *** not available for MAX41460 ***
boolean MAX41460_getUFLOW(void){ //FIFO Underflow status

}

boolean MAX41460_getOFLOW(void){ //FIFO Overflow status

}

boolean MAX41460_getFIFO_EMPTY(void){ //FIFO Empty Status

}

boolean MAX41460_getFIFO_FULL(void){ //FIFO Full Status

}

byte MAX41460_getFIFO_WORDS(void){ //This field captures the number of locations currently filled in FIFO. Each location corresponds to 8-bit data word

}

//Read functions for Configuration Register 8
boolean MAX41460_getSOFTRESET(void){ //Places DUT into software reset; 0x0: Deassert the reset 0x1: Resets the entire digital, until this bit is set to 0

}

//Read functions for Configuration Register 9
//Nothing here at the moment

//Read functions for ADDL1 *** not available for MAX41460 ***
byte MAX41460_getADDL1(void){ // Reserved Registers for the moment

}

//Read functions for ADDL2 *** not available for MAX41460 ***
byte MAX41460_getADDL2(void){ // Reserved Registers for the moment

}

/////////////////////////////////////////////////////////////////////////////////////

//Write functions for Configuration Register 1
boolean MAX41460_setXOCLKDELAY(byte){ //Start delay before enabling XO clock to digital block; Return Value: 0x0 No delay, 0x1 XO clock is enabled after 16 cycles,  0x2 XO clock is enabled after 32 cycles, 0x3 XO clock is enabled after 64 cycles
  MAX77650_write_register(MAX77650_CNFG_CHG_I_ADDR,((MAX77650_read_register(MAX77650_CNFG_CHG_I_ADDR) & 0b00001111) | ((target_val & 0b00001111) << 4)));
  if(MAX77650_getIMON_DISCHG_SCALE()==target_val)
   return true;
  else
   return false;    
}

boolean MAX41460_setXOCLKDIV(byte){ // XO clock division ratio for digital block; 0x0: Divide XO clock by 4 for digital clock 0x1: Divide XO clock by 5 for digital clock. High time is 2 cycles, low time is 3 cycles 0x2: Divide XO clock by 6 for digital clock. 0x3: Divide XO clock by 7 for digital clock. High, time is 3 cycles, and low time is 4 cycles.

}

boolean MAX41460_setFSKSHAPE(boolean){ //Sets the state of FSK Gaussain Shapin; 0x0: FSK Shaping disabled, 0x1: FSK Shaping enabled

}

boolean MAX41460_setSYNC(boolean){ //Controls if clock output acts as an input. When an input, it will sample the DATA pin; 0x0 , 0x1

}

boolean MAX41460_setMODMODE(boolean){ //Configures modulator mode; 0x0: ASK Mode, 0x1: FSK Mode

}

//Write functions for Configuration Register 2
boolean MAX41460_setCLKOUT_DELAY(byte){ //Selects the delay when CLKOUT starts toggling upon exiting SHUTDOWN mode, in divided XO clock cycles; 0x0: CLKOUT will start toggling after 64 cycles whenever moving into normal mode from shutdown mode 0x1: CLKOUT will start toggling after 128 cycles whenever moving into normal mode from shutdown mode 0x2: CLKOUT will start toggling after 256 cycles whenever moving into normal mode from shutdown mode 0x3: CLKOUT will start toggling after 512 cycles whenever moving into normal mode from shutdown mode

}

//Write functions for Configuration Register 3 *** not available for MAX41460 ***
boolean MAX41460_setBCLK_PREDIV(byte){ //Baud clock predivision ratio. Valid values are from 3 to 255; 0x00: RESERVED 0x01: RESERVED 0x02: RESERVED 0x03: Divide by 3 ... 0xFF: Divide by 255

}

//Write functions for Configuration Register 4
boolean MAX41460_setPWDN_MODE(byte){ //Power Down Mode Select; 0x0: SHUTDOWN low power state is enabled. While entering low power state, XO, PLL, and PA are shutdown. 0x1: STANDBY low power state is enabled. While entering low power state, XO is enabled. PLL and PA are shutdown 0x2: FAST WAKEUP low power state is enabled. While entering low power state, XO and PLL are enabled. PA is shutdown. 0x3: Will revert to 0x2

}

//Write functions for Configuration Register 5
boolean MAX41460_setTSTEP(byte){ //Controls GFSK shaping. See Digital FSK Modulation section in Datasheet.

}

//Write functions for SHDN Register
boolean MAX41460_setPA_BOOST(boolean){ //Enables a boost in PA output power for frequencies above 850MHz. This requires a different PA match compared to normal operation. 0x0: PA Output power in normal operation. 0x1: PA Output power in boost mode for more output power.

}

//Write functions for PA1 Register
boolean MAX41460_setPAPWR(byte){ //Controls the PA output power by enabling parallel drivers; 0x0: Minimum, 1 driver 0x1: 2 Drivers 0x2: 3 Drivers 0x3: 4 Drivers 0x4: 5 Drivers 0x5: 6 Drivers 0x6: 7 Drivers 0x7: 8 Drivers

}

//Write functions for PA2 Register
boolean MAX41460_setPACAP(byte){ //Controls shunt capacitance on PA output in fF; 0x00: 0, 0x01: 175, 0x02: 350, 0x03: 525, 0x04: 700, 0x05: 875, 0x06: 1050, 0x07: 1225, 0x08: 1400, 0x09: 1575, 0x0A: 1750, 0x0B: 1925, 0x0C: 2100, 0x0D: 2275, 0x0E: 2450, 0x0F: 2625, 0x10: 2800, 0x11: 2975, 0x12: 3150, 0x13: 3325, 0x14: 3500, 0x15: 3675, 0x16: 3850, 0x17: 4025, 0x18: 4200, 0x19: 4375, 0x1A: 4550, 0x1B: 4725, 0x1C: 4900, 0x1D: 5075, 0x1E: 5250, 0x1F: 5425

}

//Write functions for PLL1 Register
boolean MAX41460_setCPLIN(byte){ //Sets the level of charge pump offset current for fractional N mode to improve close in phase noise. Set to 'DISABLED' for integer N mode. 0x0: No extra current, 0x1: 5% of charge pump current, 0x2: 10% of charge pump current, 0x3: 15% of charge pump current

}

boolean MAX41460_setFRACMODE(boolean){ //Sets PLL between fractional-N and integer-N mode. 0x0: Integer N Mode, 0x1: Fractional N Mode

}

boolean MAX41460_setLODIV(byte){ //0x0: Disabled, 0x1: LC VCO divided by 4, 0x2: LC VCO divided by 8, 0x3: LC VCO divided by 12

}

boolean MAX41460_setLOMODE(boolean){ //Sets LO generation. For lower power, choose LOWCURRENT. For higher performance, choose LOWNOISE. 0x0: Ring Oscillator Mode, 0x1: LC VCO Mode

}

//Write functions for PLL2 Register
boolean MAX41460_setCPVAL(byte){ //Sets Charge Pump Current, 0x0: 5µA, 0x1: 10µA, 0x2: 15µA, 0x3: 20µA

}

//Write functions for Configuration Register 6
boolean MAX41460_setSPI_TXEN1(boolean){ //Transmission enable; 0x0: Transmission disabled, 0x1: Transmission enabled.

}

boolean MAX41460_setFOURWIRE1(boolean){ //Four wire readback on CLKOUT pin mode; 0x0: Four wire readback disabled, 0x1: Four wire readback enabled.

}

//Write functions for PLL3, PLL4 and PLL5 Register (3 times 8 bit frequency value)
boolean MAX41460_setFREQ(unsigned int){ //FREQ value to PLL. LO frequency= FREQ<23:0>/2^16*fXTAL

}

//Write functions for PLL6 Register
boolean MAX41460_setDELTAF(byte){ //For FSK mode, MODMODE=1 and FSKSHAPE=0, sets the frequency deviation from the space frequency for the mark frequency. fDELTA = DELTAF[6:0] * fXTAL/ 8192

}

//Write functions for PLL7 Register
boolean MAX41460_setDELTAF_SHAPE(byte){ //For FSK mode, MODMODE = 1 and FSKSHAPE = 1, sets the frequency deviation from the space frequency for the mark frequency. fDELTA = DELTAF_SHAPE[3:0] * fXTAL / 81920

}

//Write functions for Configuration Register 7
boolean MAX41460_setSPI_TXEN2(boolean){ //0x0: Transmission disabled; 0x1: Transmission enabled.

}

boolean MAX41460_setFOURWIRE2(boolean){ //Four wire readback on CLKOUT pin mode. Aliased address for FOURWIRE1; 0x0: Four wire readback disabled, 0x1: Four wire readback enabled.

}

//Write functions for I2C Configuration Register 1 and 2 *** not available for MAX41460 ***
boolean MAX41460_setPKTLEN_MODE(boolean){ //Packet Length Mode; 0x0: PKTLEN[14:0] need not be programmed. FIFO underflow event will be treated as end of packet event. For cases where actual packet length is greater than 32767 bits, this is the only mode that will be supported, and it is expected that the µC will pad such a packet to make it an integral multiple of 8-bits 0x1: PKTLEN[14:0] will provide the length of packet. Once FIFO is read for PKTLEN[14:0] bits, or if FIFO underflow, LF21 will consider that as an end of packet event.

}

boolean MAX41460_setPKTLEN(unsigned int){ //Packet Length 15 bit of Packet length information

}

//Write functions for I2C Configuration Register 3 *** not available for MAX41460 ***
boolean MAX41460_setI2C_TX_DATA(byte){ //Transmit data to be written into FIFO for I2C mode of operation. At this address, I2C register address will not auto increment within an I2C transaction burst, and subsequent writes will keep going to FIFO

}

//Write functions for I2C Configuration Register 4 and 5 *** not available for MAX41460 ***
boolean MAX41460_setPKTCOMPLETE(boolean){ //

}

boolean MAX41460_setTX_PKTLEN(unsigned int){ //Provides status information of bits transmitted for the current packet; 15 bit of Packet length information

}

//Write functions for I2C Configuration Register 6 *** not available for MAX41460 ***
boolean MAX41460_setUFLOW(boolean){ //FIFO Underflow status

}

boolean MAX41460_setOFLOW(boolean){ //FIFO Overflow status

}

boolean MAX41460_setFIFO_EMPTY(boolean){ //FIFO Empty Status

}

boolean MAX41460_setFIFO_FULL(boolean){ //FIFO Full Status

}

boolean MAX41460_setFIFO_WORDS(byte){ //This field captures the number of locations currently filled in FIFO. Each location corresponds to 8-bit data word

}

//Write functions for Configuration Register 8
boolean MAX41460_setSOFTRESET(boolean){ //Places DUT into software reset; 0x0: Deassert the reset 0x1: Resets the entire digital, until this bit is set to 0

}

//Write functions for Configuration Register 9
//Nothing here at the moment

//Write functions for ADDL1 *** not available for MAX41460 ***
boolean MAX41460_setADDL1(byte){ // Reserved Registers for the moment

}

//Write functions for ADDL2 *** not available for MAX41460 ***
boolean MAX41460_setADDL2(byte){ // Reserved Registers for the moment

}

/////////////////////////////////////////////  old code below this line /////////////////////////////////////////  

byte MAX77650_write_register(int ADDR, int data){
  int retval = -1;   
  if (MAX77650_I2C_port == 0){  
   Wire.beginTransmission(MAX77650_ADDR);
   Wire.write(ADDR); 
   Wire.write(data); 
   Wire.endTransmission();
  }  
  if (MAX77650_I2C_port == 1){  
   Wire1.beginTransmission(MAX77650_ADDR);
   Wire1.write(ADDR); 
   Wire1.write(data); 
   Wire1.endTransmission();
  }  
  if (MAX77650_I2C_port == 2){  
   Wire2.beginTransmission(MAX77650_ADDR);
   Wire2.write(ADDR); 
   Wire2.write(data); 
   Wire2.endTransmission();
  }

    #if  MAX77650_I2C_port == 0
    Wire.beginTransmission(MAX77650_ADDR);
    Wire.write(ADDR); 
    Wire.write(data); 
    Wire.endTransmission();
	#elif MAX77650_I2C_port == 1
    Wire1.beginTransmission(MAX77650_ADDR);
    Wire1.write(ADDR); 
    Wire1.write(data); 
    Wire1.endTransmission();
	#elif MAX77650_I2C_port == 2
    Wire2.beginTransmission(MAX77650_ADDR);
    Wire2.write(ADDR); 
    Wire2.write(data); 
    Wire2.endTransmission();
	#else   
    Wire.beginTransmission(MAX77650_ADDR);
    Wire.write(ADDR); 
    Wire.write(data); 
    Wire.endTransmission();
	#endif    
}



