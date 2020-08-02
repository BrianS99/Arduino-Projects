/* Written by Brian Sun
 *  Date: August 1, 2020
 *  An obstacle detecting robot that produces sound 
 */
 
#include <NewPing.h>   // include the NewPing library for this program
#include <Servo.h>

Servo myservo; //create servo object to control a servo

#define VCC_PIN 13
#define TRIGGER_PIN 12 // sonar trigger pin will be attached to Arduino pin 12
#define ECHO_PIN 11 // sonar echo pint will be attached to Arduino pin 11
#define GROUND_PIN 10

#define buzzer 5

#define MAX_DISTANCE 200 // maximum distance set to 200 cm

#define threshold 12 //distance set for object detection in cm

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // initialize NewPing

void detectObject(void);

void setup(){
  Serial.begin(9600);  // set data transmission rate to communicate with computer
  pinMode(ECHO_PIN, INPUT) ;  
  pinMode(TRIGGER_PIN, OUTPUT) ;
  pinMode(GROUND_PIN, OUTPUT);  // tell pin 10 it is going to be an output
  pinMode(VCC_PIN, OUTPUT);  // tell pin 13 it is going to be an output
  pinMode(buzzer, OUTPUT);

  digitalWrite(GROUND_PIN,LOW); // tell pin 10 to output LOW (OV, or ground)
  digitalWrite(VCC_PIN, HIGH) ; // tell pin 13 to output HIGH (+5V)

  pinMode(8,INPUT_PULLUP); //pin 8 forced to HIGH when there is no external input

  myservo.attach(9); //attaches the servo on pin 9 to the servo object

  myservo.write(0); //tells servo to go to 0 degree position
  
}

void loop(){
  int pos;
  int num;
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    myservo.write(pos);
    detectObject(); 
    
  }

  for (pos = 180; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
    myservo.write(pos);
    detectObject();
    
  }

}

void detectObject(void){ //senses for objects within threshold distance
  int DISTANCE_IN_CM = sonar.ping_cm();
  printMes(DISTANCE_IN_CM);
  
  if(DISTANCE_IN_CM <= threshold && DISTANCE_IN_CM != 0){ // makes sound
    digitalWrite(buzzer, HIGH);
  } else{
    delay(20);
    digitalWrite(buzzer,LOW);
  }
}
