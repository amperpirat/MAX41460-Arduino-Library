# MAX41460-Arduino-Library

This project provides an Arduino Library for the Maxim MAX41460-64 ISM-Band Transceivers.

The MAX41463/MAX41464 is a UHF sub-GHz ISM/SRD transmitter designed to transmit Frequency-Shift Keying (FSK), or Gaussian (G)FSK (or 2GFSK) data in the 286MHz to 960MHz frequency range. It integrates a fractional phaselocked-loop (PLL) so that a single, low-cost crystal can be used to generate commonly used world-wide sub-GHz frequencies. The fast response time of the PLL allows for frequency-hopping spread spectrum protocols for increased range and security. The chip also features preset modes with pin-selectable frequencies so that only one wire is required for an external microcontroller interface. The only frequency-dependent components required are for the external antenna-matching network. A buffered clock-out signal at 800kHz is also provided. Optionally, the device can be put into programmable mode and programmed using an I2C interface. The MAX41463/MAX41464 provides output power up to +13dBm into a 50Ω load while drawing < 12mA at 315MHz. The output load can be adjusted to increase power up to +16dBm, and a PA boost mode can be enabled at frequencies above 850MHz to compensate for losses. The PA output power can also be controlled using programmable register settings in I2C mode. The MAX41463/MAX41464 also features single-supply operation from +1.8V to +3.6V. The device has an autoshutdown feature to extend battery life and a fast oscillator wake-up with data activity detection. The MAX41463/MAX41464 is available in a 10-pin TSSOP package and is specified over the -40°C to +105°C extended temperature range.

MAX41460 Variants:

Version 				Modulation and Interface 			Preset Frequencies
MAX41460 		ASK/FSK with SPI 							No presets, programmable through SPI
MAX41461 		ASK (optional I2C) 						315/318/319.51/345/433.42/433.92/908/915 [MHz]
MAX41462 		ASK (optional I2C) 						315/433/433.92/434/868/868.3/868.35/868.5 [MHz]
MAX41463 		FSK (optional I2C) 						315/433.42/433.92/908/908.42/908.8/915/916 [MHz]
MAX41464 		FSK (optional I2C) 						315/433.92/868.3/868.35/868.42/868.5/868.95/869.85 [MHz]

## Getting Started

To get started just clone the project into your library folder, add the library and you can use the functions provided. See also "Installing" for further details. More ressources can be found here:

* https://www.maximintegrated.com/en/products/power/battery-management/MAX77650.html
* https://www.maximintegrated.com/en/app-notes/index.mvp/id/6428

The provided examples were writen and tested to suit the MAX32630FTHR board (https://www.maximintegrated.com/en/products/microcontrollers/MAX32630FTHR.html) but should work on any other board using the MAX41460 family.

### Prerequisites

- installed Adruino (version 1.8.5 or newer)

### Installing

Step by step installation for Arduino:

1. Clone the GitHub repo into your library-folder (usually C:\Users\<user>\Documents\Arduino\libraries for Windows systems)
2. Insert the library into your sketch using #include <MAX41460-Arduino-Library.h>
3. You're ready to use the Transmitter functions
4. For a how-to just have a look into the examples; they're small and cover only one piece of the device

## Versioning

We use [SemVer](http://semver.org/) for versioning.

## Authors

* **Ole Dreessen** - *Initial work* - [amperpirat](https://github.com/amperpirat)

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE.md](LICENSE.md) file for details
