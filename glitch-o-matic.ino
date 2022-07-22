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

struct Button {
  int pin;
  int ledPin;
  String key;
};
//const Button buttons[7] = {
//  { 3, 15, "G"},
//  { 4, 18, "L"},
//  { 5, 19, "I"},
//  { 6, 14, "T"},
//  { 8, 16, "C"},
//  { 9, 10, "H"},
//  { 7, 20, ""}
//}; // v2
const Button buttons[7] = {
  { 8, 15, "G"},
  { 6, 18, "L"},
  { 4, 19, "I"},
  { 9, 10, "T"},
  { 7, 16, "C"},
  { 5, 14, "H"},
  { 3, 20, ""}
}; // v3
const int numButtons = 7;
bool buttonStates[7] = {false, false, false, false, false, false, false};
void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  setPinModes();
  startupDance();
}
void setPinModes() {
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttons[i].ledPin, OUTPUT);
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }
}
void startupDance() {
  flashOnOff(3, 500);
  flashSequentially(200);
  flashOnOff(3, 500);
}
void flashSequentially(int delayMs) {
  digitalWrite(buttons[0].ledPin, HIGH);
  for (int i = 0; i < numButtons - 1; i++) {
    delay(delayMs);
    digitalWrite(buttons[i].ledPin, LOW);
    digitalWrite(buttons[i+1].ledPin, HIGH);
  }
  delay(delayMs);
  digitalWrite(buttons[numButtons - 1].ledPin, LOW);
}
void flashOnOff(int count, int delayMs) {
  for (int c = 0; c < count; c++) {
    for (int i = 0; i < numButtons; i++) {
      digitalWrite(buttons[i].ledPin, HIGH);
    }
    delay(delayMs);
    for (int i = 0; i < numButtons; i++) {
      digitalWrite(buttons[i].ledPin, LOW);
    }
    delay(delayMs);
  }
}
void loop() {
  for (int i = 0; i < numButtons; i++) {
    int isPressed = digitalRead(buttons[i].pin);
    if (isPressed == HIGH) {
      digitalWrite(buttons[i].ledPin, LOW);
      buttonStates[i] = false;
    } else {
      digitalWrite(buttons[i].ledPin, HIGH);
      if (buttonStates[i] == false) {
        if (buttons[i].key.length() > 0) {
          Keyboard.print(buttons[i].key);
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
