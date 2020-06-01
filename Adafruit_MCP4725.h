/**************************************************************************/
/*! 
    @file     Adafruit_MCP4725.h
    @author   K. Townsend (Adafruit Industries)
	@license  BSD (see license.txt)
	
	This is a library for the Adafruit MCP4725 breakout board
	----> http://www.adafruit.com/products/935
	
	Adafruit invests time and resources providing this open source code, 
	please support Adafruit and open-source hardware by purchasing 
	products from Adafruit!

	@section  HISTORY

    v1.0  - First release
*/
/**************************************************************************/

#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Wire.h>

#define MCP4725_I2CADDR_DEFAULT         (0x62)  // Default i2c address
#define MCP4725_CMD_WRITEDAC            (0x40)  // Writes data to the DAC
#define MCP4725_CMD_WRITEDACEEPROM      (0x60)  // Writes data to the DAC and the EEPROM (persisting the assigned value after reset)

class Adafruit_MCP4725{
 public:
  Adafruit_MCP4725();
  bool begin(uint8_t i2c_address = MCP4725_I2CADDR_DEFAULT,
             TwoWire *wire = &Wire);
  bool setVoltage(uint16_t output, bool writeEEPROM, 
                  uint32_t dac_frequency=400000);

 private:
  Adafruit_I2CDevice *i2c_dev = NULL;
};
