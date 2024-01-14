#include "Keyboard.h"

const int numButtons = 13;
const int buttonPins[numButtons] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int keyMap[numButtons] = {KEY_F3, KEY_F4, KEY_F5, KEY_F8, 'R', 'P', 'S', KEY_RIGHT_ARROW, KEY_LEFT_ARROW, KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_PAGE_UP, KEY_PAGE_DOWN};

bool buttonPressed[numButtons] = {false};  // Track button press state

void setup() {
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  delay(2000);
}

void loop() {
  for (int i = 0; i < numButtons; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      if (!buttonPressed[i]) {  // Check if the button was not previously pressed
        // Send corresponding keystroke
        if (keyMap[i] < 256) {
          Keyboard.write((char)keyMap[i]);
        } else {
          Keyboard.press(keyMap[i]);
          delay(100); // Adjust this delay based on your needs
          Keyboard.release(keyMap[i]);
        }
        
        // Set the flag to indicate that the button is pressed
        buttonPressed[i] = true;
      }
    } else {
      // Reset the flag when the button is released
      buttonPressed[i] = false;
    }
  }

  // Add a suitable delay to avoid constant checking and improve performance
  delay(50);
}
