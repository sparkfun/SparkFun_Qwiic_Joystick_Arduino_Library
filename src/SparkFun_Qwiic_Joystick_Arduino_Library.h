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

#ifndef _SPARKFUN_QWIIC_JOYSTICK_ARDUINO_LIBRARY_H
#define _SPARKFUN_QWIIC_JOYSTICK_ARDUINO_LIBRARY_H
#include "Arduino.h"
#include "Wire.h"

#define QWIIC_JOYSTICK_ADDR 0x20 //7-bit unshifted default I2C Address

//Map to the various registers on the Joystick
enum joystickRegisters {
  JOYSTICK_ID = 0x00,
  JOYSTICK_VERSION1, // 0x01
  JOYSTICK_VERSION2, // 0x02
  JOYSTICK_X_MSB, // 0x03
  JOYSTICK_X_LSB, // 0x04
  JOYSTICK_Y_MSB, // 0x05
  JOYSTICK_Y_LSB, // 0x06
  JOYSTICK_BUTTON, // 0x07
  JOYSTICK_STATUS, // 0x08 //1 - button clicked
  JOYSTICK_I2C_LOCK, // 0x09
  JOYSTICK_CHANGE_ADDRESS, // 0x0A
};

class JOYSTICK {
  public:
    JOYSTICK();

    boolean begin(TwoWire &wirePort = Wire, uint8_t deviceAddress = QWIIC_JOYSTICK_ADDR);
    boolean isConnected(); //Checks if sensor ack's the I2C request
	
	uint16_t getHorizontal(); //Returns the number of indents the user has turned the knob
  uint16_t getVertical(); //Returns the number of indents the user has turned the knob
		
	byte getButton(); //Returns true if knob has been twisted
	byte checkButton(); //Return true if button is currently pressed.
	
	String getVersion(); //Returns a two byte Major/Minor version number
	
	boolean setI2CAddress(uint8_t newAddress); //Change the I2C address to newAddress (Prints new address over serial)
	
  private:
    TwoWire *_i2cPort;
	uint8_t _deviceAddress;

    uint8_t readRegister(uint8_t addr);

    boolean writeRegister(uint8_t addr, uint8_t val);
};

#endif
