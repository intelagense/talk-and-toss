#include <Arduino.h>

//      Feather Huzzah with Modified Header pins
//                   +-----+
//      +------------| USB |------------+
//      |            +-----+            |
//      | [ ]RST                        |
//      | [X]3.3V                       |
//      | [ ]NC                         |
//      | [X]GND                        |
//      | [ ]ADC                 BAT[ ] |
//      | [ ]GND                  EN[X] | PWR Switch
//      | [X]GND                 USB[ ] |
//      | [X]GND                  14[X] | Belly Button
//      | [X]GND                  12[X] | Motor
//      | [X]GND                  13[X] | Speaker
//      | [ ]                     15[X] | LED
//      | [ ]                      0[ ] |
//      | [ ]                     16[ ] |
//      | [ ]                      2[ ] |
//      | [ ]                      5[ ] |
//      | [ ]                      4[ ] |
//      |                               |
//      +-------------------------------+


const int bellyButton = 14;
const int blinker = 15;
const int motor = 12;
const int speaker = 13;
const int countdown = 45000; 

bool timerRunning = false;
unsigned long startTime;
unsigned long previousMillis;
const unsigned long interval = 2000;
bool ledState = LOW;

void alarm();
void silentAlarm();
void wakeUpChirp();
void startUpSound();
void startTimer();

void setup() {  
  pinMode(bellyButton, INPUT_PULLUP);
  pinMode(blinker, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(speaker, OUTPUT);

  wakeUpChirp();
  delay(1000);
}

void loop() {
  int buttonState = digitalRead(bellyButton);

  if (buttonState == LOW) {
    startUpSound();
    startTimer();
    delay(50);
  }

  if (timerRunning) {
    unsigned long currentTime = millis();
    
    if (currentTime - startTime <= countdown) { 
      // Pulse the LED
      if (currentTime - previousMillis >= interval) {
        previousMillis = currentTime;
        ledState = !ledState; 
        digitalWrite(blinker, ledState);
      }
    } else {
      timerRunning = false;
      digitalWrite(blinker, LOW);
      for (int i = 0; i < 5; i++) {
        silentAlarm();
        delay(200);
      }
    }
  } else {
    digitalWrite(blinker, LOW);
  }
}

void startTimer() {
  timerRunning = true;
  startTime = millis();
}

void wakeUpChirp() {
  for (int i = 0; i < 5; i++) {
    int randomFrequency = random(800, 2000);
    int randomDuration = random(100, 400);
    tone(speaker, randomFrequency, randomDuration);
    delay(random(50, 200));
  }
  delay(200);
  startUpSound();
}

void alarm() {
  tone(speaker, 1000, 200);
  digitalWrite(motor, HIGH);
  delay(300);
  digitalWrite(motor, LOW);
  tone(speaker, 1500, 400);
  delay(600);
}

void startUpSound() {
  tone(speaker, 1500, 100);
  delay(200);
  tone(speaker, 1700, 100);
  delay(200);
  tone(speaker, 1500, 100);
  delay(200);
  tone(speaker, 1900, 300);
  delay(400);
}

void silentAlarm() {
  for (int i = 0; i < 3; i++) { 
    digitalWrite(motor, HIGH);
    delay(50);
    digitalWrite(motor, LOW);
    delay(50);
    digitalWrite(motor, HIGH);
    delay(50);
    digitalWrite(motor, LOW);
    delay(50);
  }
}