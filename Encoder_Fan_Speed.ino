/* Written by Brian Sun
 * Date: August 2, 2020      
 * A rotary encoder that can control the speed of DC motor.  
 *  
 */

 #define encoderA 12
 #define encoderB 11
 #define sw 10
 #define motor 3

 int counter = 0; 
 int aState;
 int aLastState;  
 int speed = 0;
 
 void setup() {
  // initializing encoder pins 
   pinMode (encoderA,INPUT);
   pinMode (encoderB,INPUT);
   pinMode (sw, INPUT_PULLUP);
   pinMode (motor, OUTPUT);
    
   Serial.begin (9600);
   // Reads the initial state of the encoderA
   aLastState = digitalRead(encoderA);
      
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
       speed += 5;
     } else {
      if(counter == 0){
        counter = 40;
      }
       counter --;
       speed -= 5;
     }
     if(speed > 255){
      speed = 255;
     } else if (speed < 50 && speed != 0){
      speed = 50;
     }
     Serial.print("Position: ");
     Serial.println(counter);
     Serial.println(speed);
     analogWrite(motor, speed);
   } 
   aLastState = aState; // Updates the previous state of the encoderA with the current state
   
   // resetting the position of servo by pressing the switch
   if (digitalRead(sw) == LOW){
    Serial.println("PRESSED");
    do{
    } while(digitalRead(sw) == LOW);
    speed = 0;
    analogWrite(motor, speed);
    do{
    } while(digitalRead(sw) == HIGH);
    speed = 50;
    analogWrite(motor,speed);
    do{
    } while(digitalRead(sw) == LOW);
  }
 }
   
 
