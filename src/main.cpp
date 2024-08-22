#include <Arduino.h>

const int button = 14;
const int blinker = 0;

void setup() {  
  pinMode(button, INPUT_PULLUP);
  pinMode(blinker, OUTPUT);
  digitalWrite(blinker, HIGH);
}

void loop() {
  int buttonState = digitalRead(button);

  if (buttonState == LOW) {
    digitalWrite(blinker, LOW);
  } else {
    digitalWrite(blinker, HIGH);
  }

  // debounce
  delay(50);
}