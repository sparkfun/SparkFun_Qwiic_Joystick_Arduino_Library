/*
  This is a example written for the SparkFun Qwiic Joystick
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/15168

  Written by Wes Furuya @ SparkFun Electronics, February 5th, 2019

  The Qwiic Joystick is a I2C controlled analog joystick
  
  Example 2- Change I2C Address and Read Firmware Version:
  This program uses the Qwiic Joystick Arduino Library to change the I2C address
  for the device. You enter in the DEC value (0-127) of the I2C address
  joystick position and button state, which is then printed out in the Serial
  Monitor.

  https://github.com/sparkfun/SparkFun_Qwiic_Joystick_Arduino_Library/examples

  Development environment specifics:
  Arduino IDE 1.8.5

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Wire.h>
#include "SparkFun_Qwiic_Joystick_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_joystick
JOYSTICK joystick; //Create instance of this object

uint8_t Address = 0x20; //Start address (Default 0x20)
byte newAddress[5];

void setup() {
  Serial.begin(9600);
  Serial.println("Qwiic Joystick Example");

  if(joystick.begin(Wire, Address) == false)
  {
    Serial.println("Joystick does not appear to be connected. Please check wiring. Freezing...");
    while(1);
  }
  else
  {
    Serial.print("Address: 0x");
    Serial.print(Address, HEX);
    Serial.print(" Version: ");
    Serial.println(joystick.getVersion());
  }
}

void loop() {
    //Serial.println("I2C Range: 0-127");
    Serial.println("INPUT- New I2C Address (DEC):");
    Serial.flush(); //Clears buffer
    while (Serial.available() == 0) delay(20); //Waits for entry
    int len = Serial.readBytes(newAddress,5); //Takes entry as a stream of bytes
    
    // Serial.println(len);

    //Converts ASCII char to DEC (Address)
    if (len==1)
    {
    // Serial.println((byte)newAddress[0]-48, HEX);
    Address = (byte)newAddress[0]-48;
    }
    else if (len==2)
    {
    // Serial.println(((byte)newAddress[0]-48)*10+((byte)newAddress[1]-48), HEX);
    Address = ((byte)newAddress[0]-48)*10+((byte)newAddress[1]-48);
    }
    else if (len==3)
    {
    // Serial.println(((byte)newAddress[0]-48)*100+((byte)newAddress[1]-48)*10+((byte)newAddress[2]-48), HEX);
    Address = ((byte)newAddress[0]-48)*100+((byte)newAddress[1]-48)*10+((byte)newAddress[2]-48);
    }
    
    joystick.setI2CAddress(Address); //Sets new I2C address
      
    //Print out Firmware Version to double check address change
    Serial.print(" Firmware: v");
    Serial.println(joystick.getVersion());

}