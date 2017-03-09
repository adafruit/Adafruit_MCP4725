#ifndef adafruit_mcp4725_h
#define adafruit_mcp4725_h

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

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

#define MCP4726_CMD_WRITEDAC                0x40  // Writes data to the DAC
#define MCP4726_CMD_WRITEDACEEPROM          0x60  // Writes data to the DAC and the EEPROM (persisting the assigned value after reset)
#define MCP4725_OUTPUT_LOAD_RESISTANCE_1K   0
#define MCP4725_OUTPUT_LOAD_RESISTANCE_100K 1
#define MCP4725_OUTPUT_LOAD_RESISTANCE_500K 2
#define MCP4725_ADDRESS_PIN_DISABLED        255

class Adafruit_MCP4725{
 public:
  Adafruit_MCP4725(uint8_t addressPin = MCP4725_ADDRESS_PIN_DISABLED);
  void begin(uint8_t a);  
  void setVoltage(uint16_t output, bool writeEEPROM);
  float setNearestActualVoltage(uint16_t desiredOutputMilliVolts, uint16_t vrefMilliVolts, bool writeEEPROM);
  void powerDown(uint8_t loadResistance, bool writeEEPROM);

 private:
  uint8_t _i2caddr;
  uint8_t _addressPin;

  void writeI2cPacket(uint8_t controlBits, uint16_t data);
  void setAddressPin(bool enable);
};

#endif
