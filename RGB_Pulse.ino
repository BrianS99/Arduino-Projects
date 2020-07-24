  #define BLUE 3
#define GREEN 5
#define RED 6

void goViolet(void);
void goBlue(void);
void goTurquoise(void);
void goGreen(void);
void goYellow(void);
void goOrange(void);
void goRed(void);

void setup() {
  // put your setup code here, to run once:
pinMode(RED, OUTPUT);
pinMode(GREEN, OUTPUT);
pinMode(BLUE, OUTPUT);
digitalWrite(RED, LOW);
digitalWrite(GREEN, LOW);
digitalWrite(BLUE, LOW);
}

// define variables
int redValue;
int greenValue;
int blueValue;

int lightValue;

void loop() {
  // put your main code here, to run repeatedly:
goViolet();
delay(1000);
goBlue();
delay(1000);
goTurquoise();
delay(1000);
goGreen();
delay(1000);
goYellow();
delay(1000);
goOrange();
delay(1000);
goRed();
delay(1000);
}

void goViolet(void){
  analogWrite(RED, 10);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 10);
}

void goBlue(void){
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 10);
}

void goTurquoise(void){
  analogWrite(RED, 0);
  analogWrite(GREEN, 10);
  analogWrite(BLUE, 10);
}

void goGreen(void){
  analogWrite(RED, 0);
  analogWrite(GREEN, 10);
  analogWrite(BLUE, 0);
}

void goYellow(void){
  analogWrite(RED, 10);
  analogWrite(GREEN, 10);
  analogWrite(BLUE, 0);
}

void goOrange(void){
  analogWrite(RED, 10);
  analogWrite(GREEN, 2);
  analogWrite(BLUE, 0);
}

void goRed(void){
  analogWrite(RED, 10);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
}
