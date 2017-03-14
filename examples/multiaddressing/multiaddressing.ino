/**************************************************************************/
/*!
    @file     multiaddressing.ino
    @author   Alex Mitchell (MitchellSoft Technology Ltd.)
    @license  BSD (see license.txt)

    This example shows how to address multiple MCP4725s on the same I2C bus.
    
    One Arduino pin is required per MCP4725, which is used like a chip-select
    pin.  For this reason, it only makes sense to address MCP4725s in this
    way if you need more than two DACs in your project and they all have the
    same address.  Otherwise, you will be using up Arduino pins needlessly.
    
    This is an example sketch for the Adafruit MCP4725 breakout board
    ----> http://www.adafruit.com/products/935

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!
*/
/**************************************************************************/
#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac1(2); // ADDR pin of MCP4725 connected to Arduino pin 2
Adafruit_MCP4725 dac2(3); // ADDR pin of MCP4725 connected to Arduino pin 3
Adafruit_MCP4725 dac3(4); // ADDR pin of MCP4725 connected to Arduino pin 4

void setup(void) {
  Serial.begin(9600);
  Serial.println("Hello!");

  // The begin method must be called with the address of the MCP4725 when ADDR pin is tied to VCC
  // For Adafruit MCP4725A1 this is 0x63
  // For MCP4725A0 this is 0x61
  // For MCP4725A2 this is 0x65
  dac1.begin(0x63);
  dac2.begin(0x63);
  dac3.begin(0x63);
    
  Serial.println("Example sketch demonstrating addressing multiple MCP4725s");
}

void loop(void) {
  Serial.println("Setting 3 different lower voltage outputs");
  dac1.setVoltage(100, false);
  dac2.setVoltage(200, false);
  dac3.setVoltage(300, false);

  delay(5000);

  Serial.println("Setting 3 different higer voltage outputs");
  dac1.setVoltage(1000, false);
  dac2.setVoltage(2000, false);
  dac3.setVoltage(3000, false);

  delay(5000);
}