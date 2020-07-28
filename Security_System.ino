/* Written by Brian Sun
 *  Date: July 26. 2020
 *  This is a security password system, which prompts user for password until it is correct
 */

#include <Keypad.h>

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
int passLen = 4;
char response[16];
int responseLen;
int result;

void getPass(char[]);

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  bool match = true;
  char key;

    /* prompts user to enter the simple password */
    do{
      match = true;
      responseLen = 0; 
      Serial.println("Enter password, press # when done: ");
  
      while(true){
        do{
          key = keypad.getKey();
        }while(key == false);
    
        if (key == '#'){
          Serial.println();
          break;
        }
        response[responseLen] = key;
        Serial.print(key);
        responseLen++;

     }
     //checks the password compared to the entered response
     for(int index = 0; index < responseLen; index++){
      if(password[index] != response[index]){
        match = false;
        Serial.println("Access Denied.");
        break;
     }
    }
    if(match == true){
      Serial.println("Access Granted.");
      break;
    }
  }while(match == false);

  delay(500);
  Serial.println("You may now choose to change your password, or simply logout.");
  Serial.println("Press A to change password, press any other key to logout");

  do{
    key = keypad.getKey();
  }while(key == false);

  if(key == 'A'){
    getPass(password);  
  } else {
    Serial.println("Logged out successfully.");  
  }
}

void getPass(char password[]){
  char key;
  int passLen;
  int confirmLen;
  char confirm[16];
  bool match = true;
  
  /*prompts user for the password, inputed on keypad*/
  do{
    passLen = 0;  
    Serial.println("Please enter the new password, press # when done: ");
  
    while(true){
     do{
      key = keypad.getKey();
     }while(key == false);
    
     if (key == '#'){
      Serial.println();
      break;
     }
     password[passLen] = key;
     Serial.print(key);
     passLen++;
    }
    if(passLen < 4){
       Serial.println("Password too short, please re-enter.");     
     } else if(passLen > 12){
      Serial.println("Password too long, please re-enter.");
     } else {
      Serial.println("Good password!");
     }
  }while(passLen < 4 || passLen > 12);

  /*prompts user for the confirmation*/
  do{
    match = true;
    confirmLen = 0; 
    Serial.println("Please confirm this password, press # when done: ");
  
    while(true){
     do{
      key = keypad.getKey();
     }while(key == false);
    
     if (key == '#'){
      Serial.println();
      break;
     }
     confirm[confirmLen] = key;
     Serial.print(key);
     confirmLen++;

     }
     for(int index = 0; index < passLen; index++){
      if(password[index] != confirm[index]){
        match = false;
        Serial.println("Passwords do not match, please re-enter.");
        break;
     }
    }
    if(match == true){
      break;
    }
  }while(match == false);
  
  Serial.println("Thank you! Your password was successfully changed. You are logged out now.");

return;
}
