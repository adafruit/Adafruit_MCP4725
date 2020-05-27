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
Adafruit_MCP4725::Adafruit_MCP4725(uint8_t addressPin) {
  _addressPin = addressPin;

  if(_addressPin != MCP4725_ADDRESS_PIN_DISABLED) {
    pinMode(_addressPin, OUTPUT);
  }
}

/**************************************************************************/
/*! 
    @brief  Setups the HW
*/
/**************************************************************************/
void Adafruit_MCP4725::begin(uint8_t addr) {
  _i2caddr = addr;
  Wire.begin();
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
void Adafruit_MCP4725::setVoltage(uint16_t output, bool writeEEPROM) {
  uint8_t controlBits = writeEEPROM ? MCP4726_CMD_WRITEDACEEPROM : MCP4726_CMD_WRITEDAC;
  writeI2cPacket(controlBits, output);
}

void Adafruit_MCP4725::setAddressPin(bool enable) {
  if(_addressPin != MCP4725_ADDRESS_PIN_DISABLED) {
    digitalWrite(_addressPin, enable);
  }
}

void Adafruit_MCP4725::writeI2cPacket(uint8_t controlBits, uint16_t dataBits) {
setAddressPin(true);

#ifdef TWBR
  uint8_t twbrback = TWBR;
  TWBR = ((F_CPU / 400000L) - 16) / 2; // Set I2C frequency to 400kHz
#endif
  Wire.beginTransmission(_i2caddr);
  Wire.write(controlBits);
  Wire.write(dataBits / 16);        // Upper data bits (D11.D10.D9.D8.D7.D6.D5.D4)
  Wire.write((dataBits % 16) << 4); // Lower data bits (D3.D2.D1.D0.x.x.x.x)
  Wire.endTransmission();
#ifdef TWBR
  TWBR = twbrback;
#endif

  setAddressPin(false);
}

float Adafruit_MCP4725::setNearestActualVoltage(uint16_t desiredOutputMilliVolts, uint16_t vrefMilliVolts, bool writeEEPROM) {
  float dacStepsPerMillivolt = 4095.0 / vrefMilliVolts;
  uint16_t nearestDacInputCodeForVoltage = round(dacStepsPerMillivolt * desiredOutputMilliVolts);

  float nearestVoltage = (vrefMilliVolts / 4095.0) * nearestDacInputCodeForVoltage;

  setVoltage(nearestDacInputCodeForVoltage, writeEEPROM);
  return nearestVoltage;
}

void Adafruit_MCP4725::powerDown(uint8_t loadResistance, bool writeEEPROM) {
  uint8_t controlBits = writeEEPROM ? MCP4726_CMD_WRITEDACEEPROM : MCP4726_CMD_WRITEDAC;

  switch (loadResistance) {
    case MCP4725_OUTPUT_LOAD_RESISTANCE_1K:
      controlBits |= 0x2;
      break;
    case MCP4725_OUTPUT_LOAD_RESISTANCE_100K:
      controlBits |= 0x4;
      break;
    case MCP4725_OUTPUT_LOAD_RESISTANCE_500K:
    default:
      controlBits |= 0x6;
      break;
  }

  writeI2cPacket(controlBits, 0x0);
}
