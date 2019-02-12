/*
  This is a example written for the SparkFun Qwiic Joystick
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/15168

  Written by Wes Furuya @ SparkFun Electronics, February 5th, 2019

  The Qwiic Joystick is a I2C controlled analog joystick
  
  Example 1- Basic Readings:
  This program uses the Qwiic Joystick Arduino Library to read the current
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

void setup() {
  Serial.begin(9600);
  Serial.println("Qwiic Joystick Example");

  if(joystick.begin() == false)
  {
    Serial.println("Joystick does not appear to be connected. Please check wiring. Freezing...");
    while(1);
  }
}

void loop() {
  Serial.print("X: ");
  Serial.print(joystick.getHorizontal());

  Serial.print(" Y: ");
  Serial.print(joystick.getVertical());
  
  Serial.print(" Button: ");
  Serial.println(joystick.getButton());

  delay(200);
}
