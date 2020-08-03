/* Written by Brian Sun
 * Date: August 2, 2020      
 * A rotary encoder that can control a servo motor.  
 *  
 */
 #include <Servo.h>

 #define encoderA 12
 #define encoderB 11
 #define sw 10
 #define servo 9

 Servo myservo;
 int counter = 0; 
 int aState;
 int aLastState;  
 int servoPos = 0;
 
 void setup() {
  // initializing encoder pins 
   pinMode (encoderA,INPUT);
   pinMode (encoderB,INPUT);
   pinMode (sw, INPUT_PULLUP);
   myservo.attach(servo);
    
   Serial.begin (9600);
   // Reads the initial state of the encoderA
   aLastState = digitalRead(encoderA);
   myservo.write(0);   
 } 
 
 void loop() { 
   aState = digitalRead(encoderA); // Reads the "current" state of the encoderA
      
   // If the previous and the current state of the encoderA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the encoderB state is different to the encoderA state, that means the encoder is rotating clockwise
     if (digitalRead(encoderB) != aState) {
      if(counter == 40){
        counter = 0; 
      }
       counter ++;
       servoPos += 5;
     } else {
      if(counter == 0){
        counter = 40;
      }
       counter --;
       servoPos -= 5;
     }
     if(servoPos > 180){
      servoPos = 180;
     } else if (servoPos < 0){
      servoPos = 0;
     }
     Serial.print("Position: ");
     Serial.println(counter);
     myservo.write(servoPos);
   } 
   aLastState = aState; // Updates the previous state of the encoderA with the current state
   
   // resetting the position of servo by pressing the switch
   if (digitalRead(sw) == LOW){
    Serial.println("Reset!");
    servoPos = 0;
    myservo.write(servoPos);
    delay(500);
   }
 }
   
 
