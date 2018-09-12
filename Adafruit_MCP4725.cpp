/**************************************************************************/
/*! 
    @file     Adafruit_MCP4725.cpp
    @author   K.Townsend (Adafruit Industries)
	@license  BSD (see license.txt)
	
	I2C Driver for Microchip's MCP4725 I2C DAC

	This is a library for the Adafruit MCP4725 breakout
	----> http://www.adafruit.com/products/935
		
	Adafruit invests time and resources providing this open source code, 
	please support Adafruit and open-source hardware by purchasing 
	products from Adafruit!

	@section  HISTORY

    v1.0 - First release
*/
/**************************************************************************/
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

#include "Adafruit_MCP4725.h"

/**************************************************************************/
/*! 
    @brief  Instantiates a new MCP4725 class
*/
/**************************************************************************/
Adafruit_MCP4725::Adafruit_MCP4725() {
}

/**************************************************************************/
/*! 
    @brief  Setups the HW
*/
/**************************************************************************/
void Adafruit_MCP4725::begin(uint8_t addr) {
  _i2c = &Wire;
  _i2caddr = addr;

  _i2c->begin();
}
 
void Adafruit_MCP4725::begin(TwoWire *theWire, uint8_t addr) {
  _i2c = theWire;
  _i2caddr = addr;

  _i2c->begin();
}
 
/**************************************************************************/
/*! 
    @brief  Sets the output voltage to a fraction of source vref.  (Value
            can be 0..4095)

    @param[in]  output
                The 12-bit value representing the relationship between
                the DAC's input voltage and its output voltage.
    @param[in]  writeEEPROM
                If this value is true, 'output' will also be written
                to the MCP4725's internal non-volatile memory, meaning
                that the DAC will retain the current voltage output
                after power-down or reset.
*/
/**************************************************************************/
void Adafruit_MCP4725::setVoltage( uint16_t output, bool writeEEPROM )
{
#ifdef TWBR
  uint8_t twbrback = TWBR;
  TWBR = ((F_CPU / 400000L) - 16) / 2; // Set I2C frequency to 400kHz
#endif
  _i2c->beginTransmission(_i2caddr);
  if (writeEEPROM)
  {
    _i2c->write(MCP4726_CMD_WRITEDACEEPROM);
  }
  else
  {
    _i2c->write(MCP4726_CMD_WRITEDAC);
  }
  _i2c->write(output / 16);                   // Upper data bits          (D11.D10.D9.D8.D7.D6.D5.D4)
  _i2c->write((output % 16) << 4);            // Lower data bits          (D3.D2.D1.D0.x.x.x.x)
  _i2c->endTransmission();
#ifdef TWBR
  TWBR = twbrback;
#endif
}
