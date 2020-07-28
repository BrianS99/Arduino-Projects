/* Written by Brian Sun
 *  Date: July 27 2020
 *  This is a digital stopwatch program for the LCD1602 display, using two buttons
 */

// button and other constants
#define width 16
#define start 3
#define reset 4

#include <LiquidCrystal.h> 
int Contrast=75;
 LiquidCrystal lcd(12, 11, 7, 8, 9, 10);

bool resetWatch = false;

void setup() {
  // put your setup code here, to run once:
  analogWrite(6,Contrast);
  lcd.begin(16, 2);
  pinMode(start, INPUT);
  digitalWrite(start, HIGH);
  pinMode(reset, INPUT);
  digitalWrite(reset, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  //initialize all time variables
 int centiSecs = 0;
 int deciSecs = 0;
 int secs = 0;
 int decaSecs = 0;
 int mins = 0;
 int decaMins = 0;
 
  lcd.setCursor(0,0);
  lcd.print("00:00.00");
  lcd.setCursor(0,1);
  lcd.print("PRESS START");
  resetWatch = false;

  do{
  }while(digitalRead(start) == HIGH);
  lcd.setCursor(0,1);
  lcd.print("           ");
  do{
  }while(digitalRead(start) == LOW);
  
  while(resetWatch == false){ // run the stopwatch code as long as no reset was requested
  while(digitalRead(start) == HIGH){ // increments time by 10 millisecond intervals
    
    delay(10);
    centiSecs++;

    if(centiSecs == 10){
      centiSecs = 0;
      deciSecs++;
      }
    if(deciSecs == 10){
      deciSecs = 0;
      secs++;
      }
    if(secs == 10){
      secs = 0;
      decaSecs++;
      }
     if(decaSecs == 6){
      decaSecs = 0;
      mins++; 
     }
     if(mins == 10){
      mins = 0;
      decaMins++;
     }

    // updating the display at each time increment   
    lcd.setCursor(7,0);
    lcd.print(centiSecs);
    lcd.setCursor(6,0);
    lcd.print(deciSecs);
    lcd.setCursor(4,0);
    lcd.print(secs);
    lcd.setCursor(3,0);
    lcd.print(decaSecs);
    lcd.setCursor(1,0);
    lcd.print(mins);
    lcd.setCursor(0,0);
    lcd.print(decaMins);

  }

   // Pausing the stopwatch
  if(digitalRead(start) == LOW){ 
    lcd.setCursor(0,1);
    lcd.print("PAUSED");
    do{
    }while(digitalRead(start) == LOW);
    do{
      if(digitalRead(reset) == LOW){
        resetWatch = true;
        break;
      }
    }while(digitalRead(start) == HIGH);
    do{
      // if reset was pushed, then the loop will break
      if(resetWatch == true){ 
        break;
      }
    }while(digitalRead(start) == LOW);
    
    lcd.setCursor(0,1);
    lcd.print("      ");
  }
  if(resetWatch == true){
      break;
    }
  }
  
}
