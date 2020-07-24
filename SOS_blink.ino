/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
#define delFast 250
#define delSlow 750
#define repeatNum 3

void Sblink(void);
void Oblink(void);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  Sblink();
  Oblink();
  Sblink();
  delay(1000);
}

void Sblink(void){
  int count;
  
  for(count = 0; count<repeatNum; count++){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(delFast);
    digitalWrite(LED_BUILTIN, LOW);  
    delay(delFast);   
   }
}

void Oblink(void){
  int count;

  for(count = 0; count<repeatNum; count++){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(delSlow);
    digitalWrite(LED_BUILTIN, LOW);  
    delay(delSlow);   
   }
}
