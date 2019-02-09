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

  Serial.print("Y: ");
  Serial.print(joystick.getVertical());
  
  Serial.print("Button: ");
  Serial.print(joystick.getButton());

  Serial.print("Ver: ");
  Serial.println(joystick.getVersion());

  delay(200);
}
