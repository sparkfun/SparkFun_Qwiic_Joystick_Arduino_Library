/*
  This is example is for the SparkFun Qwiic Joystick SparkFun sells these at 
  its website: www.sparkfun.com

   
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/15168

  Qwiic Joystick Example 3 -I2C_Scanner:
  This sketch communicates with the Qwiic Joystick to find the
  current address of the Joystick. It uses the I2C Scanner  
  Example from https://playground.arduino.cc/Main/I2cScanner

  The factory default address is 0x20.
  // --------------------------------------
  // i2c_scanner
  //
  // Version 1
  //    This program (or code that looks like it)
  //    can be found in many places.
  //    For example on the Arduino.cc forum.
  //    The original author is not know.
  // Version 2, Juni 2012, Using Arduino 1.0.1
  //     Adapted to be as simple as possible by Arduino.cc user Krodal
  // Version 3, Feb 26  2013
  //    V3 by louarnold
  // Version 4, March 3, 2013, Using Arduino 1.0.3
  //    by Arduino.cc user Krodal.
  //    Changes by louarnold removed.
  //    Scanning addresses changed from 0...127 to 1...119,
  //    according to the i2c scanner by Nick Gammon
  //    http://www.gammon.com.au/forum/?id=10896
  // Version 5, March 28, 2013
  //    As version 4, but address scans now to 127.
  //    A sensor seems to use address 120.
  // Version 6, November 27, 2015.
  //    Added waiting for the Leonardo serial communication.
  //
  //
  // This sketch tests the standard 7-bit addresses
  // Devices with higher bit address might not be seen properly.
  //

  https://github.com/sparkfun/SparkFun_Qwiic_Joystick_Arduino_Library/examples
  
  Development environment specifics:
  Arduino IDE 1.8.5

*/


#include <Wire.h>

void setup()
{
  Wire.begin();

  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}


void loop()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);           // wait 5 seconds for next scan
}