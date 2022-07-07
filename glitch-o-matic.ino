#include <Keyboard.h>
const int numButtons = 7;
const int leds[7] = {3, 7, 6, 14, 16, 10, 8};
const int buttons[7] = {2, 20, 21, 19, 18, 15, 9};
const String buttonKeys[7] = {"G", "L", "I", "T", "C", "H", "\n"};
bool buttonStates[7] = {false, false, false, false, false, false, false};
void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  setPinModes();
  startupDance();
}
void setPinModes() {
  for (int i = 0; i < numButtons; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(buttons[i], INPUT_PULLUP);
  }
}
void startupDance() {
  flashOnOff(3, 500);
  flashSequentially(200);
  flashOnOff(3, 500);
}
void flashSequentially(int delayMs) {
  digitalWrite(leds[0], HIGH);
  for (int i = 0; i < numButtons - 1; i++) {
    delay(delayMs);
    digitalWrite(leds[i], LOW);
    digitalWrite(leds[i+1], HIGH);
  }
  delay(delayMs);
  digitalWrite(leds[numButtons - 1], LOW);
}
void flashOnOff(int count, int delayMs) {
  for (int c = 0; c < count; c++) {
    for (int i = 0; i < numButtons; i++) {
      digitalWrite(leds[i], HIGH);
    }
    delay(delayMs);
    for (int i = 0; i < numButtons; i++) {
      digitalWrite(leds[i], LOW);
    }
    delay(delayMs);
  }
}
void loop() {
  for (int i = 0; i < numButtons; i++) {
    int isPressed = digitalRead(buttons[i]);
    if (isPressed == HIGH) {
      digitalWrite(leds[i], LOW);
      buttonStates[i] = false;
    } else {
      digitalWrite(leds[i], HIGH);
      if (buttonStates[i] == false) {
        Keyboard.print(buttonKeys[i]);
        delay(100);
      }
      buttonStates[i] = true;
    }
  }
}
