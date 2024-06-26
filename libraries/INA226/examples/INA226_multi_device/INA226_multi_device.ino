//
//    FILE: INA226_multi_device.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo two INA226's
//     URL: https://github.com/RobTillaart/INA226
//
//  not tested with HW yet

#include "INA226.h"


INA226 INA0(0x40);
INA226 INA1(0x41);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("INA226_LIB_VERSION: ");
  Serial.println(INA226_LIB_VERSION);

  Wire.begin();
  if (!INA0.begin() )
  {
    Serial.println("INA0 could not connect. Fix and Reboot");
  }
  if (!INA1.begin() )
  {
    Serial.println("INA1 could not connect. Fix and Reboot");
  }

  INA0.setMaxCurrentShunt(1, 0.002);
  INA1.setMaxCurrentShunt(1, 0.002);
}


void loop()
{
  Serial.println("\nBUS\tSHUNT\tCURRENT\tPOWER\t\tBUS\tSHUNT\tCURRENT\tPOWER");
  for (int i = 0; i < 20; i++)
  {
    Serial.print(INA0.getBusVoltage(), 3);
    Serial.print("\t");
    Serial.print(INA0.getShuntVoltage_mV(), 3);
    Serial.print("\t");
    Serial.print(INA0.getCurrent_mA(), 3);
    Serial.print("\t");
    Serial.print(INA0.getPower_mW(), 3);
    Serial.print("\t");
    Serial.print("\t");
    Serial.print(INA1.getBusVoltage(), 3);
    Serial.print("\t");
    Serial.print(INA1.getShuntVoltage_mV(), 3);
    Serial.print("\t");
    Serial.print(INA1.getCurrent_mA(), 3);
    Serial.print("\t");
    Serial.print(INA1.getPower_mW(), 3);
    Serial.println();
    delay(1000);
  }
}


//  -- END OF FILE --
