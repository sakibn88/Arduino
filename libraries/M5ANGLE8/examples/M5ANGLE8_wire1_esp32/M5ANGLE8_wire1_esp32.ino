//
//    FILE: M5ANGLE8_wire1_esp32.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo (works well with build in plotter)
//     URL: https://github.com/RobTillaart/M5ANGLE8
//
//  ESP32

#include "m5angle8.h"


M5ANGLE8 MM(M5ANGLE8_DEFAULT_ADDRESS, &Wire1);  //  0x43


void setup()
{
  Serial.begin(115200);
  Serial.print("M5ANGLE8_LIB_VERSION: ");
  Serial.println(M5ANGLE8_LIB_VERSION);
  delay(100);

  Wire1.begin(22, 23);  //  adjust pins 

  MM.begin();
}


void loop()
{
  for (int ch = 0; ch < 8; ch++)
  {
    Serial.print(MM.analogRead(ch));
    Serial.print("\t");
    delay(1);
  }
  Serial.print(MM.inputSwitch());
  Serial.print("\n");
  delay(10);
}


//  -- END OF FILE --