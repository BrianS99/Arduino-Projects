#include <IRremote.h> //include the library
#define Button_1 0xFF30CF
#define Button_2 0xFF18E7
#define Button_3 0xFF7A85
#define Button_4 0xFF10EF
#define Button_5 0xFF38C7
#define Button_6 0xFF5AA5
#define Button_P 0xFFA25D

#define receiver 13
#define BLUE 12
#define GREEN 11
#define RED 10

uint32_t Previous; 
IRrecv irrecv(receiver); //create a new instance of receiver
decode_results results;

int greenVal = 0;
int blueVal = 0;
int redVal = 0;

void setup() {
  // put your setup code here, to run once:
 irrecv.enableIRIn(); //start the receiver
pinMode(BLUE, OUTPUT);
pinMode(GREEN, OUTPUT);
pinMode(RED, OUTPUT);

analogWrite(BLUE, 0);
analogWrite(GREEN, 0);
analogWrite(RED, 0);

Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 if (irrecv.decode(&results)) { //if we have received an IR signal
  if (results.value==0xFFFFFFFF) { 
      results.value=Previous;
      }

    switch(results.value) {
           case Button_1 : digitalWrite(RED, HIGH); break;
           case Button_4 : digitalWrite(RED, LOW); break;
           case Button_2 : digitalWrite(GREEN, HIGH); break;
           case Button_5 : digitalWrite(GREEN, LOW); break;
           case Button_3 : digitalWrite(BLUE, HIGH); break;
           case Button_6 : digitalWrite(BLUE, LOW); break;
           case Button_P : digitalWrite(BLUE, LOW); digitalWrite(GREEN, LOW); digitalWrite(RED, LOW); break; 
           
      } 
 Serial.println (results.value, HEX); //display HEX results 
 irrecv.resume(); //next value
 }
 Previous=results.value;
 }
