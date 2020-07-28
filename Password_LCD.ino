/* Written by Brian Sun
 *  Date: July 22 2020
 *  This is a password security system, meant for the LCD1602 Module with keypad, buzzer
 *  NOTE: if you wish to display a * instead of the actual password (like in real life), simply change
 *  when the output to '*' instead of 'key'. Displaying the values is for demo purposes.
 */

#define width 16
#define buzzer 5

#include <Keypad.h>
#include <LiquidCrystal.h> 
#include <time.h>
int Contrast=75;
 LiquidCrystal lcd(12, 11, 7, 8, 9, 10);


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {A7,A6,A5,A4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A3,A2,A1,A0}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char password[16] = "1234";
int passLen[] = {4};
char response[16];
int responseLen;
int result;

void getPass(char[],int[]); //gets new password from user
int messageLen(char[]); //gets length of message
void clearln(int); //clears specified row
void resetString(char[]); // resets the string

void setup() {
  // put your setup code here, to run once:
  analogWrite(6,Contrast);
  lcd.begin(16, 2);
  pinMode(buzzer, OUTPUT);
}

void loop(){
  bool match = true;
  bool displayed = false;
  char key;

    /* prompts user to enter the simple password */
    do{
      resetString(response);
      match = true;
      displayed = false;
      
      responseLen = 0; 
      lcd.setCursor(0,0);
      lcd.clear();
      lcd.print("Password: ");

      while(true){ // receives input from user one character at a time
        do{
          key = keypad.getKey();
        }while(key == false);
    
        if (key == '#'){ // # is used as an enter button
          if(responseLen < 4){
            match = false;
          }
          lcd.clear();
          playSound();
          break;
        }
        playSound();
        response[responseLen] = key;
        lcd.setCursor(responseLen,1);
        lcd.print(key);
        responseLen++;

     }
     //checks the password compared to the entered response
     for(int index = 0; index < responseLen; index++){
      if(password[index] != response[index]){
        match = false;
        displayed = true;
        lcd.setCursor(0,0);
        lcd.print("Access Denied.");
        resetString(response);
        delay(1500);
        lcd.clear();
        break;
     }
    }
    if(match ==true){
      if(responseLen != passLen[0]){
        match = false;
      }
    }
    if(match == true){
      lcd.setCursor(0,0);
      lcd.print("Access Granted.");
      resetString(response);
      delay(1500);
      break;
    }
    if(displayed == false){
      lcd.setCursor(0,0);
      lcd.print("Access Denied.");
      resetString(response);
      delay(1500);
      lcd.clear();
    }
  }while(match == false);

  delay(500);
  lcd.clear();
  lcd.print("A -> change PW");
  lcd.setCursor(0,1);
  lcd.print("Any key-> logout");

  do{
    key = keypad.getKey();
  }while(key == false);

  if(key == 'A'){ // 'A' to change password
    lcd.clear();
    playSound();
    getPass(password,passLen);  
  } else { // Any other key to log out
    lcd.clear();
    playSound();
    lcd.setCursor(0,0);
    lcd.print("Logged out!");
    delay(1500);  
  }
}

// prompts user for new password and asks for confirmation
void getPass(char password[], int passLen[]){
  char key;
  int confirmLen;
  char confirm[16];
  bool match = true;
  bool displayed = false;
  
  /*prompts user for the password, inputed on keypad*/
  do{
    passLen[0] = 0;
    lcd.clear();  
    lcd.print("New password: ");
  
    while(true){
     do{
      key = keypad.getKey();
     }while(key == false);
    
     if (key == '#'){ //# is used as an enter button
      lcd.clear();
      playSound();
      break;
     }
     password[passLen[0]] = key;
     playSound();
     lcd.setCursor(passLen[0], 1);
     lcd.print(key);
     passLen[0] += 1;
    }

    //enforces password length rules
    if(passLen[0] < 4){
      lcd.clear();
      lcd.print("Too short!");
      delay(1500);     
     } else if(passLen[0] > 12){
      lcd.clear();
      lcd.print("Too long!");
      delay(1500); 
     } else {
      lcd.clear();
      lcd.print("Good password!");
      delay(1500);
     }
  }while(passLen[0] < 4 || passLen[0] > 12);

  /*prompts user for the confirmation*/
  do{
    match = true;
    confirmLen = 0; 
    lcd.clear();
    displayed = false;
    lcd.print("Please confirm:");
  
    while(true){
     do{
      key = keypad.getKey();
     }while(key == false);
    
     if (key == '#'){
      lcd.clear();
      playSound();
      break;
     }
     confirm[confirmLen] = key;
     playSound();
     lcd.setCursor(confirmLen, 1);
     lcd.print(key);
     confirmLen++;

     }
     // checks confimation code with first code
     for(int index = 0; index < passLen[0]; index++){
      if(password[index] != confirm[index]){
        match = false;
        lcd.clear();
        lcd.print("They don't match");
        lcd.setCursor(0,1);
        lcd.print("Please re-enter");
        resetString(confirm);
        displayed = true;
        delay(2200);
        break;
     }
    }
    if(confirmLen != passLen[0]){
      if(displayed == false){
        match = false;
        lcd.clear();
        lcd.print("They don't match");
        lcd.setCursor(0,1);
        lcd.print("Please re-enter");
        resetString(confirm);
        delay(2200);
      }
    }
    if(match == true){
      break;
    }
  }while(match == false);

  lcd.clear();
  lcd.print("Password changed");
  lcd.setCursor(0,1);
  lcd.print("successfully!");
  resetString(confirm);
  delay(2000);
}

// counts the amounts of characters of each message
 int messageLen(char message[]){
  int count;
  for(count = 0; message[count] != '\0'; count++);
  return count;
 }

 //clears specified row
 void clearln(int row){
  lcd.setCursor(0,row);
  lcd.print("                ");
 }

//plays beeping noise
 void playSound(void){
  digitalWrite(buzzer, HIGH);
  delay(20);
  digitalWrite(buzzer, LOW);
}

// resets the user response string
void resetString(char response[]){
  for(int index = 0; index<16; index++){
    response[index] = '.';
  }
}
