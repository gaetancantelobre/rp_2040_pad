#include <Arduino.h>
#include <Keyboard.h>

#define Key_Volume_Up 0xE9
#define Key_Volume_Down 0xEA
// Define the encoder pins.
const int encoder1PinA = 2;
const int encoder1PinB = 3;
const int encoder2PinA = 0;
const int encoder2PinB = 1;

// Define switch matrix pins.
const int rowPins[] = {4, 5, 6};
const int colPins[] = {7, 8, 9};
const int numRows = 3;
const int numCols = 3;

// Variables for encoders.
int counter1 = 0;
int encoder1PreviousState = LOW;
int counter2 = 0;
int encoder2PreviousState = LOW;

// Variables for switch matrix.
bool switchStates[numRows][numCols] = {false};

void setup() {
  Serial.begin(115200);

  // Set encoder pins as inputs with pull-up resistors.
  pinMode(encoder1PinA, INPUT_PULLUP);
  pinMode(encoder1PinB, INPUT_PULLUP);
  pinMode(encoder2PinA, INPUT_PULLUP);
  pinMode(encoder2PinB, INPUT_PULLUP);

  // Set switch matrix row pins as outputs.
  for (int i = 0; i < numRows; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH); // Initialize rows HIGH.
  }

  // Set switch matrix column pins as inputs with pull-up resistors.
  for (int i = 0; i < numCols; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }

  // Initialize Keyboard library
  Keyboard.begin(); 
}

void loop() {
  // Handle Encoder 1.
  int encoder1CurrentState = digitalRead(encoder1PinA);
  if (encoder1CurrentState != encoder1PreviousState) {
    if (digitalRead(encoder1PinB) == encoder1CurrentState) {
      // Increase volume
      Keyboard.print(0xE0,0x32); 
      delay(10); // Small delay
      Keyboard.releaseAll();
    } else {
      // Decrease volume
      Keyboard.press(Key_Volume_Down); 
      delay(10); // Small delay
      Keyboard.releaseAll();
    }
    Serial.print("Counter 1: ");
    Serial.print(counter1);
    Serial.print("  ");
  }
  encoder1PreviousState = encoder1CurrentState;

  // Handle Encoder 2.
  int encoder2CurrentState = digitalRead(encoder2PinA);
  if (encoder2CurrentState != encoder2PreviousState) {
    if (digitalRead(encoder2PinB) == encoder2CurrentState) {
      counter2++;
    } else {
      counter2--;
    }
    Serial.print("Counter 2: ");
    Serial.println(counter2);
  }
  encoder2PreviousState = encoder2CurrentState;

  // Scan the switch matrix.
  for (int row = 0; row < numRows; row++) {
    digitalWrite(rowPins[row], LOW);

    for (int col = 0; col < numCols; col++) {
      if (digitalRead(colPins[col]) == LOW) {
        if (!switchStates[row][col]) {
          Serial.print("Switch at (");
          Serial.print(row + 1); // Row and column are 1-indexed.
          Serial.print(", ");
          Serial.print(col + 1);
          Serial.println(") pressed.");
          switchStates[row][col] = true;
        }
      } else {
        switchStates[row][col] = false;
      }
    }
    digitalWrite(rowPins[row], HIGH);
  }
}