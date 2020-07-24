#define width 16

#include <LiquidCrystal.h> 
#include <time.h>
int Contrast=75;
 LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
  
void slide(char[], int);
void slideR(char[], int);
int messageLen(char[]);

char message[] = {"This is a test! :)"};
char message2[] = {"Sample text      "};
int length = messageLen(message);
int length2 = messageLen(message2);

 void setup(){
    analogWrite(6,Contrast);
     lcd.begin(16, 2);
  } 
 void loop(){
  while(int e = 1){
   slide(message, length);
   delay (200);
   slideR(message2, length2);
   delay(200);
   }
 }
   
 void slide(char message[], int length){
  char temp;
  lcd.setCursor(0,0);
  temp = message[0];
  for(int index = 1; index < length; index++){
    message[index-1] = message[index];
  }
  message[length-1] = temp;
  lcd.print(message);
 }

 void slideR(char message[], int length){
  char temp;
  lcd.setCursor(0,1);
  temp = message[length-1];
  for(int index = length-1; index > 0; index-=1){
    message[index] = message[index-1];
  }
  message[0] = temp;
  lcd.print(message);
 }

 int messageLen(char message[]){
  int count;
  for(count = 0; message[count] != '\0'; count++);
  return count;
 }
