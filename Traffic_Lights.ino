#define RED 3
#define YELLOW 4
#define GREEN 5

void setup() {
  // put your setup code here, to run once:
pinMode(RED, OUTPUT);
pinMode(GREEN, OUTPUT);
pinMode(YELLOW, OUTPUT);
digitalWrite(RED, LOW);
digitalWrite(GREEN, LOW);
digitalWrite(YELLOW, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(GREEN, HIGH);
delay(3000);
digitalWrite(GREEN,LOW);

digitalWrite(YELLOW, HIGH);
delay(1000);
digitalWrite(YELLOW,LOW);

digitalWrite(RED, HIGH);
delay(3000);
digitalWrite(RED,LOW);
}
