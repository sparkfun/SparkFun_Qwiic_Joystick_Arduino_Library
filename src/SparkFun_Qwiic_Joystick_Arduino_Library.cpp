/*
  This is a library written for the SparkFun Qwiic Joystick
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/15168

  Written by Nathan Seidle @ SparkFun Electronics, November 25th, 2018
  Modified by Wes Furuya @ SparkFun Electronics, February 5th, 2019

  The Qwiic Joystick is a I2C controlled analog joystick

  https://github.com/sparkfun/SparkFun_Qwiic_Joystick_Arduino_Library

  Development environment specifics:
  Arduino IDE 1.8.5

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "SparkFun_Qwiic_Joystick_Arduino_Library.h"
#include "Arduino.h"

//Constructor
JOYSTICK::JOYSTICK()
{

}

//Initializes the I2C connection
//Returns false if board is not detected
boolean JOYSTICK::begin(TwoWire &wirePort, uint8_t deviceAddress)
{
  _i2cPort = &wirePort;
  _i2cPort->begin(); //This resets any setClock() the user may have done

  _deviceAddress = deviceAddress;

  if (isConnected() == false) return (false); //Check for sensor presence

  return (true); //We're all setup!
}

//Returns true if I2C device ack's
boolean JOYSTICK::isConnected()
{
  _i2cPort->beginTransmission((uint8_t)_deviceAddress);
  if (_i2cPort->endTransmission() != 0)
    return (false); //Sensor did not ACK
  return (true);
}

//Change the I2C address of this address to newAddress
boolean JOYSTICK::setI2CAddress(uint8_t newAddress)
{
  if (8 <= newAddress && newAddress <= 119)
  {
    writeRegister(JOYSTICK_I2C_LOCK, 0x13);
    writeRegister(JOYSTICK_CHANGE_ADDRESS, newAddress);
    
    // #if !defined(ESP_PLATFORM) && !defined(ESP8266)
    //   _i2cPort->end();
    // #endif

    //Once the address is changed, we need to change it in the library
    _deviceAddress = newAddress;

    if (begin(Wire, newAddress) == true)
    {
      Serial.print("Address: 0x");
      if (newAddress < 16) Serial.print("0");
      Serial.print(newAddress, HEX); //Prints out new Address value in HEX
      Serial.print(" ");
      return (true);
    }
    else
    {
      Serial.println("Address Change Failure");
      return (false);
    }
  }
  else
  {
    Serial.println();
    Serial.println("ERROR: Input outside available address range (8-119)");
    return (false);
  }
  
}

//Returns the 10-bit ADC value of the joystick horizontal position
uint16_t JOYSTICK::getHorizontal()
{
  uint16_t X_MSB = readRegister(JOYSTICK_X_MSB);
  uint16_t X_LSB = readRegister(JOYSTICK_X_LSB);
  return ((X_MSB<<8) | X_LSB)>>6;
}

//Returns the 10-bit ADC value of the joystick vertical position
uint16_t JOYSTICK::getVertical()
{
  uint16_t Y_MSB = readRegister(JOYSTICK_Y_MSB);
  uint16_t Y_LSB = readRegister(JOYSTICK_Y_LSB);
  return ((Y_MSB<<8) | Y_LSB)>>6;
}

//Returns 0 button is currently being pressed
byte JOYSTICK::getButton()
{
  byte button = readRegister(JOYSTICK_BUTTON);
  //boolean pressed = status & (1<<statusButtonPressedBit);

  return(button);
}

//Returns 1 if button was pressed between reads of .getButton() or .checkButton()
//the register is then cleared after read.
byte JOYSTICK::checkButton()
{
  byte status = readRegister(JOYSTICK_STATUS);
  
  writeRegister(JOYSTICK_STATUS, 0x00); //We've read this status bit, now clear it

  return(status);
}


//Returns a string of the firmware version number
String JOYSTICK::getVersion()
{
  uint8_t Major = readRegister(JOYSTICK_VERSION1);
  uint8_t Minor = readRegister(JOYSTICK_VERSION2);

  return("v" + String(Major) + "." + String(Minor));
}


//Reads from a given location from the Joystick
uint8_t JOYSTICK::readRegister(uint8_t addr)
{
  _i2cPort->beginTransmission((uint8_t)_deviceAddress);
  _i2cPort->write(addr);
  if (_i2cPort->endTransmission() != 0)
  {
    //Serial.println("No ack!");
    return (0); //Device failed to ack
  }
  _i2cPort->requestFrom((uint8_t)_deviceAddress, (uint8_t)1);
  if (_i2cPort->available()) {
    return (_i2cPort->read());
  }
  else
  {
    //Serial.println("No ack!");
    return (0); //Device failed to respond
  }
}


//Write a byte value to a spot in the Joystick
boolean JOYSTICK::writeRegister(uint8_t addr, uint8_t val)
{
  _i2cPort->beginTransmission((uint8_t)_deviceAddress);
  _i2cPort->write(addr);
  _i2cPort->write(val);
  if (_i2cPort->endTransmission() != 0)
  {
    //Serial.println("No write ack!");
    return (false); //Device failed to ack
  }

  delay(30); // allow EPROM time to store value

  return (true);
}