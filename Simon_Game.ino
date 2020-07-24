#include <time.h>
#include <NewPing.h>

#define green 2
#define red 3
#define yellow 4
#define blue 5

#define Gbutton 7
#define Rbutton 8
#define Ybutton 9
#define Bbutton 10

#define buzzer 11

#define intMax 5
#define intMin 2
#define length 5

#define FALSE 0
#define TRUE 1

#define ONE_SEC 1000

void generateSequence(int[]);
void playSound(void);
void onLED(int);
void turnOffLED(void);
void userLost(void);
void userWon(void);

int lightNum = 0;
int level = 0;
int index;
int wrongAnswer = FALSE;

  //button pressing variables
int greenPress;
int redPress;
int bluePress;
int yellowPress;

void setup() {
  // put your setup code here, to run once:

  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(Gbutton, INPUT_PULLUP);
  pinMode(Rbutton, INPUT_PULLUP);
  pinMode(Ybutton, INPUT_PULLUP);
  pinMode(Bbutton, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
}

void loop() {
  // put your main code here, to run repeatedly:
    int data[length];
    int answer[length];
  
  generateSequence(data);
  delay(2000);

  while (level < length && wrongAnswer == FALSE) {

     //lights up the LEDs one at a time following the generated sequence
      for (lightNum = 0; lightNum <= level; lightNum++) {
        onLED(data[lightNum]);
      }
      //reads the switches one at a time to and collects response in array
      //using INPUT_PULLUP so HIGH and LOW are reversed for digital read
      for (lightNum = 0; lightNum <= level; lightNum++) {
        do {
          greenPress = digitalRead(Gbutton);
          redPress = digitalRead(Rbutton);
          yellowPress = digitalRead(Ybutton);
          bluePress = digitalRead(Bbutton);
        } while (greenPress == HIGH && redPress == HIGH && bluePress == HIGH && yellowPress == HIGH);

        playSound();
        
        //assigns the response to an answer array
        if (greenPress == LOW) {
          answer[lightNum] = green;
          digitalWrite(green, HIGH);
        }
        else if (redPress == LOW) {
          answer[lightNum] = red;
          digitalWrite(red, HIGH);
        }
        else if (yellowPress == LOW) {
          answer[lightNum] = yellow;
          digitalWrite(yellow, HIGH);
        }
        else {
          answer[lightNum] = blue;
          digitalWrite(blue, HIGH);
        }
        //keeps reading the switches until user lets go
        do{
          greenPress = digitalRead(Gbutton);
          redPress = digitalRead(Rbutton);
          yellowPress = digitalRead(Ybutton);
          bluePress = digitalRead(Bbutton);
        } while (greenPress == LOW || redPress == LOW || bluePress == LOW || yellowPress == LOW);

        turnOffLED();
        delay(ONE_SEC / 3);
      }
      //compares the user's response with the sequence
      for (index = 0; index <= level && wrongAnswer == FALSE; index++) {
        if (data[index] != answer[index]) {
          wrongAnswer = TRUE;
        }
      }
      delay(ONE_SEC / 2);
      level++;
    }
    //flashes the winning lights or losing lights, resets the game
    if (wrongAnswer == TRUE) {
      userLost();
      level = 0;
      wrongAnswer = FALSE;
    }
    else {
      userWon();
      level = 0;
    }
  }

void generateSequence(int data[]){
  int index;
 
  for (index = 0; index < length; index++) {
    data[index] = random(intMin, intMax+1);
    Serial.print(data[index]);
  }
}

void playSound(void){
  digitalWrite(buzzer, HIGH);
  delay(50);
  digitalWrite(buzzer, LOW);
}

void onLED(int led) {

  digitalWrite(led, HIGH);
  delay(800);
  digitalWrite(led, LOW);
  delay(500);
}

void turnOffLED(void) {

  digitalWrite(green, LOW);
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(blue, LOW);
}

void userLost(void) {
  int num = 0;
  digitalWrite(buzzer, HIGH);
  
  while (num < 3) {
    digitalWrite(red, HIGH);
    delay(ONE_SEC / 8);
    digitalWrite(red, LOW);
    delay(ONE_SEC / 8);
    num++;
  }
  digitalWrite(buzzer, LOW);
}

void userWon(void) {
  int num = 0;

  while (num < 3) {
    digitalWrite(green, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(ONE_SEC/8);
    digitalWrite(green, LOW);
    digitalWrite(buzzer, LOW);
    delay(ONE_SEC/8);
    num++;
  }
}
