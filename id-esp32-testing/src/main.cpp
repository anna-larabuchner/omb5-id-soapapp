#include <Arduino.h>

#include <ezButton.h>

#include <BleKeyboard.h>

/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-joystick
 */


#define LED 2

#define VRX_PIN  36 // ESP32 pin GPIO36 (ADC0) connected to VRX pin
#define VRY_PIN  39 // ESP32 pin GPIO39 (ADC0) connected to VRY pin

#define LEFT_THRESHOLD  1000
#define RIGHT_THRESHOLD 3000
#define UP_THRESHOLD    1000
#define DOWN_THRESHOLD  3000

#define COMMAND_NO     0x00
#define COMMAND_LEFT   0x01
#define COMMAND_RIGHT  0x02
#define COMMAND_UP     0x04
#define COMMAND_DOWN   0x08

int valueX = 0 ; // to store the X-axis value
int valueY = 0 ; // to store the Y-axis value
int command = COMMAND_NO;

ezButton button(17); // create ezButton object that attach to pin G17;

BleKeyboard bleKeyboard;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // LED Code
  pinMode(LED, OUTPUT);

  // JOYSTICK Code
  button.setDebounceTime(50); // set debounce time to 50 milliseconds


  // BLE Keyboard Code
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
}


void loop() {
  // put your main code here, to run repeatedly:

  // LED Code
  digitalWrite(LED, HIGH);
  // Serial.println("LED is on");
  // delay(1000);
  digitalWrite(LED, LOW);
  // Serial.println("LED is off");
  // delay(1000);

  Serial.println(bleKeyboard.isConnected());

  // JOYSTICK Code
  if(bleKeyboard.isConnected()) {
    bleKeyboard.print("---------- In if");
    button.loop(); // MUST call the loop() function first

    /* Serial.println("Sending 'Hello world'...");
    bleKeyboard.print("Hello world");

    delay(1000); */


    /* int btnState = button.getState();
    Serial.println(btnState); */

    if(button.isPressed())
      Serial.println("Sending Enter key...");
      bleKeyboard.write(KEY_RETURN);
      bleKeyboard.print("KEY_RETURN");

    if(button.isReleased())
      Serial.println("The button is released");

    // read X and Y analog values
    valueX = analogRead(VRX_PIN);
    valueY = analogRead(VRY_PIN);

    // converts the analog value to commands
    // reset commands
    command = COMMAND_NO;

    // check left/right commands
    if (valueX < LEFT_THRESHOLD)
      command = command | COMMAND_LEFT;
    else if (valueX > RIGHT_THRESHOLD)
      command = command | COMMAND_RIGHT;

    // check up/down commands
    if (valueY < UP_THRESHOLD)
      command = command | COMMAND_UP;
    else if (valueY > DOWN_THRESHOLD)
      command = command | COMMAND_DOWN;

    // NOTE: AT A TIME, THERE MAY BE NO COMMAND, ONE COMMAND OR TWO COMMANDS

    // print command to serial and process command
    if (command & COMMAND_LEFT) {
      Serial.println("COMMAND LEFT");
      // TODO: add your task here
      bleKeyboard.write(KEY_LEFT_ARROW);
      bleKeyboard.print("KEY_LEFT_ARROW");
    }

    if (command & COMMAND_RIGHT) {
      Serial.println("COMMAND RIGHT");
      // TODO: add your task here
      bleKeyboard.write(KEY_RIGHT_ARROW);
      bleKeyboard.print("KEY_RIGHT_ARROW");
    }

    if (command & COMMAND_UP) {
      Serial.println("COMMAND UP");
      // TODO: add your task here
      bleKeyboard.write(KEY_UP_ARROW);
      bleKeyboard.print("KEY_UP_ARROW");
    }

    if (command & COMMAND_DOWN) {
      Serial.println("COMMAND DOWN");
      // TODO: add your task here
      bleKeyboard.write(KEY_DOWN_ARROW);
      bleKeyboard.print("KEY_DOWN_ARROW");
    }
  }

}
