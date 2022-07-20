#include <Keyboard.h>
/* ----- USB -----
 * 1          RAW *
 * 0          GND *
 * GND        RST *
 * GND        VCC *
 * 2          21  *
 * 3          20  *
 * 4          19  *
 * 5          18  *
 * 6          15  *
 * 7          14  *
 * 8          16  *
 * 9          10  *
 */
const int numButtons = 7;
const int leds[7] = {10, 16, 14, 15, 18, 19, 20};
const int buttons[7] = {9, 8, 7, 6, 5, 4, 3};
const String buttonKeys[7] = {"G", "L", "I", "T", "C", "H", ""};
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
        if (buttonKeys[i].length() > 0) {
          Keyboard.print(buttonKeys[i]);
        }
      }
      buttonStates[i] = true;
    }
  }
  Serial.println(buttonStatesAsString());
}

String buttonStatesAsString() {
  String states = "";
  for (int i = 0; i < numButtons; i++) {
    states += buttonStates[i] ? "1" : "0";
  }
  return states;
}
