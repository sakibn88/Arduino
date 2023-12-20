//    FILE: I2C_LCD_demo_spectrum_column.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_LCD library
//     URL: https://github.com/RobTillaart/I2C_LCD

//  WARNING: do not overfeed your display with too much data
//           too fast as it may not be able to handle
//           (mine got corrupted)


#include "Arduino.h"
#include "Wire.h"

#include "I2C_LCD.h"

//  test 20x4 + 16x2
#define BACKLIGHT_PIN   3
#define En_pin          2
#define Rw_pin          1
#define Rs_pin          0
#define D4_pin          4
#define D5_pin          5
#define D6_pin          6
#define D7_pin          7


I2C_LCD lcd(39);

uint8_t colblock[8][8] =
{
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F },
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F },
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F },
  { 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F },
  { 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
  { 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
  { 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
  { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
};


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("I2C_LCD_LIB_VERSION: ");
  Serial.println(I2C_LCD_LIB_VERSION);
  Serial.println();

  lcd.config(39, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin, BACKLIGHT_PIN, POSITIVE);

  Wire.begin();
  Wire.setClock(100000);
  lcd.begin(20, 4);

  lcd.display();
  lcd.clear();
  lcd.setCursor(0, 0);

  for (int i = 0; i < 8; i++)
  {
    lcd.createChar(i, colblock[i]);
  }

  lcd.clear();
  //  for (int i = 0; i < 8; i++)
  //  {
  //    lcd.special(i);
  //  }
  //  delay(1000);

}


void loop()
{
  for (int i = 0; i < 20; i++)
  {
    spectrumColumn(i, random(32));
  }
  delay(1000);
}


//  this is not the most efficient algorithm as all
//  data is written over and over.
//  optimization only write the delta which could be zero
//
void spectrumColumn(uint8_t col, int value)
{
  for (uint8_t row = 0; row < 4; row++)
  {
    lcd.setCursor(col, 3 - row);
    if (value <= 0)      lcd.print(' ');
    else if (value >= 8) lcd.special(7);
    else                 lcd.special(value - 1);
    value -= 8;
  }
  delay(10);  //  give time to settle.
}


//  -- END OF FILE --