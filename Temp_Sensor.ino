/* Written by Brian Sun
 *  Date: July 25, 2020
 *  This code is for a digital thermometer, displayed on a LCD1602 module
 */

int tempPin = 0;
#include <LiquidCrystal.h> 
#include <time.h>
int Contrast=75;
 LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
analogWrite(6,Contrast);
lcd.begin(16, 2);
}

void loop() {
// reads temperature and does all necessary conversions
  int tempReading = analogRead(tempPin);
  // This is OK
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  float tempC = tempK - 273.15;            // Convert Kelvin to Celcius
  float tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  
// writing the temperature on the display
  lcd.setCursor(0,0);
  lcd.print("Temp:       C");
  lcd.setCursor(6,0);
  lcd.print(tempC);
  lcd.setCursor(0,1);
  lcd.print("            F");
  lcd.setCursor(6,1);
  lcd.print(tempF);

  delay(500);
  lcd.clear();
}
