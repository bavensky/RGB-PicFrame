#include <Ultrasonic.h>

Ultrasonic ultrasonic(2, 3);

#define RED 9
#define GREEN 10
#define BLUE 11

byte state = 0;
boolean detect = false;
boolean firstDetect = false;
unsigned long previousMillis = 0;

//byte ledSet[3][3] = {
//  {255, 0, 0},
//  {0, 255, 0},
//  {0, 0, 255}
//};

void setup() {
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

void loop() {
  unsigned long currentMillis = millis();

  while (state == 0) {
    analogWrite(RED, 0);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);

    if (ultrasonic.distanceRead() <= 50) {
      previousMillis = currentMillis;
      firstDetect = true;
      detect = true;
      state = 1;
    }
  }

  if (currentMillis - previousMillis >= 5000 && firstDetect == true ) {
    previousMillis = currentMillis;
    if (ultrasonic.distanceRead() <= 50) {
      detect = true;
    } else {
      firstDetect = false;
      detect = false;
      state = 0;
    }
  }

  if (detect == true && state == 1) {
    analogWrite(RED, random(0, 255));
    analogWrite(GREEN, random(0, 255));
    analogWrite(BLUE, random(0, 255));
    state = 2;
  }

  //  Serial.print("Distance : ");
  //  Serial.print(ultrasonic.distanceRead());
  //  Serial.print("  ");
  //  Serial.print(state);
  //  Serial.print("  ");
  //  Serial.println(firstDetect);
  //  delay(100);

}
