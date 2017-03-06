/**************************************************************************/
/*!
    @file     powerdown.pde
    @author   Alex Mitchell (MitchellSoft Technology Ltd.)
    @license  BSD (see license.txt)

    This example shows how to put the MCP4725 into power-down mode.
    During power-down mode, the device draws about 60 nA, compared
    against 200 µA (typical) when running in normal mode.
    
    When in power-down mode, the output pin is connected to ground via
    a configurable pull-down resistance of either 1K, 100K, or 500K Ohms.
    
    To bring the device out of power-down mode, simply call setVoltage
    (it will also wake up if an I2C General Call Wake-Up Command is sent
    on the I2C bus).

    This is an example sketch for the Adafruit MCP4725 breakout board
    ----> http://www.adafruit.com/products/935

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!
*/
/**************************************************************************/
#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

void setup(void) {
  Serial.begin(9600);
  Serial.println("Hello!");

  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  dac.begin(0x62);
    
  Serial.println("Example sketch demonstrating the MCP4725 power-down mode");
}

void loop(void) {
  Serial.println("Putting MCP4725 to sleep.  Output pin connected to ground via 1K Ohm resistance.");
  dac.powerDown(MCP4725_OUTPUT_LOAD_RESISTANCE_1K, false);
  delay(5000);
  
  Serial.println("Switching sleep mode.  Output pin now connected ot ground via 100K Ohm resistance.");
  dac.powerDown(MCP4725_OUTPUT_LOAD_RESISTANCE_100K, false);
  delay(5000);
  
  Serial.println("Waking device up by setting an output voltage.");
  dac.setVoltage(1000, false);
  delay(5000);
  
  Serial.println("Putting MCP4725 to sleep again.  Output pin connected to ground via 500K Ohm resistance.");
  dac.powerDown(MCP4725_OUTPUT_LOAD_RESISTANCE_500K, false);
  delay(5000);
}