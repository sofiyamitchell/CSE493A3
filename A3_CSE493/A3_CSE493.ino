#include <Shape.hpp>
#include <ParallaxJoystick.hpp>

// Change these depending on where you have your joystick hooked up!
const int JOYSTICK_UPDOWN_PIN = A1;
const int JOYSTICK_LEFTRIGHT_PIN = A0;
const int TRIGGER_PIN = 8;

// Change to 4095 for 12-bit ADCs like ESP32 and 1023 for 10-bit ADCs like Arduino Uno/Leonardo
const int MAX_ANALOG_VAL = 1023; 

const enum JoystickYDirection JOYSTICK_Y_DIR = RIGHT;

ParallaxJoystick _joystick(JOYSTICK_UPDOWN_PIN, JOYSTICK_LEFTRIGHT_PIN, MAX_ANALOG_VAL, JOYSTICK_Y_DIR);

void setup() {
  Serial.begin(9600);

  pinMode(JOYSTICK_LEFTRIGHT_PIN, INPUT);
  pinMode(JOYSTICK_UPDOWN_PIN, INPUT); 
  pinMode(TRIGGER_PIN, INPUT_PULLUP); 

}

void loop() {
  _joystick.read();

  int upDownVal = _joystick.getUpDownVal();
  int leftRightVal = _joystick.getLeftRightVal();

  // Translate joystick movement into amount of pixels to move
  int yMovementPixels = map(upDownVal, 0, 656, 10, -10);
  int xMovementPixels = map(leftRightVal, 367, 1023, 10, -10);

  int triggerPush = digitalRead(TRIGGER_PIN);
  if(triggerPush == LOW) {
    Serial.println((String) xMovementPixels + "," + yMovementPixels + "," + triggerPush);
    delay(50);
  } else {
    Serial.println((String) xMovementPixels + "," + yMovementPixels + "," + triggerPush);
    delay(50);
  }
}