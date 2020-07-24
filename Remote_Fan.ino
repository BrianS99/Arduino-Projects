#include <Servo.h>

#define button1 5
#define button2 2
#define motor 3
#define button3 6

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int Speed[] = {0,150};
int num;

void buttonPress(int[], int);
void changeSpeed(int);

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(motor, OUTPUT);
}

void loop() {
  int index = 0;
  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    myservo.write(pos);
    if(digitalRead(button1) == LOW){
      buttonPress(Speed, index);
    }
    if(digitalRead(button3) == LOW){
      if(index<1){
        index++;
      }
      else{
        index = 0;
      }
      analogWrite(motor, Speed[index]);
    }
    for(num = 0; num < 4; num++){
    if(digitalRead(button1) == LOW){
      buttonPress(Speed, index);
    }
      if(digitalRead(button3) == LOW){
      if(index<1){
        index++;
      }
      else{
        index = 0;
      }
      analogWrite(motor, Speed[index]);
    }
      delay(5);
    }
  }
  for(num = 0; num < 500; num++){
    if(digitalRead(button1) == LOW){
      buttonPress(Speed, index);
    }
      if(digitalRead(button3) == LOW){
      if(index<1){
        index++;
      }
      else{
        index = 0;
      }
      analogWrite(motor, Speed[index]);
    }
      delay(1);
    }
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);
    if(digitalRead(button1) == LOW){
      buttonPress(Speed, index);
    }
    if(digitalRead(button3) == LOW){
      if(index<1){
        index++;
      }
      else{
        index = 0;
      }
      analogWrite(motor, Speed[index]);
    }
    for(num = 0; num < 4; num++){
    if(digitalRead(button1) == LOW){
      buttonPress(Speed, index);
    }
      if(digitalRead(button3) == LOW){
      if(index<1){
        index++;
      }
      else{
        index = 0;
      }
      analogWrite(motor, Speed[index]);
    }
      delay(5);
    }
  }
  for(num = 0; num < 500; num++){
      if(digitalRead(button3) == LOW){
      if(index<1){
        index++;
      }
      else{
        index = 0;
      }
      analogWrite(motor, Speed[index]);
    }
      delay(1);
  }
}

void buttonPress(int Speed[], int index){
  int result;
      do{
        result = digitalRead(button1);
        if(digitalRead(button3) == LOW){
      if(index<1){
        index++;
      }
      else{
        index = 0;
      }
      analogWrite(motor, Speed[index]);
    }
      }while(result == LOW);
      delay(10);
      do{
        result = digitalRead(button2);
        if(digitalRead(button3) == LOW){
      if(index<1){
        index++;
      }
      else{
        index = 0;
      }
      analogWrite(motor, Speed[index]);
    }
      }while(result == HIGH);
}

void changeSpeed(int Speed){
  
}
 
