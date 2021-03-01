/*
  VolumeControl
*/

// How the volume-up and volume-down button output looks on my test-remote
// volmin: Protocol=NEC Address=0xBF00 Command=0x9 Raw-Data=0xF609BF00 (32 bits) LSB first (1 decoded)
// volplus: Protocol=NEC Address=0xBF00 Command=0x1 Raw-Data=0xFE01BF00 (32 bits) LSB first (9 decoded

// Including IRremote library
#include <IRremote.h>

// Setting a max value in ms to decide when to run the button-up (release) code
#define MAX_TIME 150

// Defining the volume up pins
#define UP_PIN_1 2
#define UP_PIN_2 3
#define UP_PIN_3 4
#define UP_PIN_4 5
#define UP_PIN_5 6

// Defining the volume down pins
#define DOWN_PIN_1 7
#define DOWN_PIN_2 8
#define DOWN_PIN_3 9
#define DOWN_PIN_4 10
#define DOWN_PIN_5 11

// Defining the IR receive pin
int IR_RECEIVE_PIN = 12;

// Defining some other variables needed for the project
long lastPressTime = 0;
int state = LOW;


// Defining the motor-off function
void motorOff() {
  digitalWrite(UP_PIN_1, LOW);
  digitalWrite(UP_PIN_2, LOW);
  digitalWrite(UP_PIN_3, LOW);
  digitalWrite(UP_PIN_4, LOW);
  digitalWrite(UP_PIN_5, LOW);

  digitalWrite(DOWN_PIN_1, LOW);
  digitalWrite(DOWN_PIN_2, LOW);
  digitalWrite(DOWN_PIN_3, LOW);
  digitalWrite(DOWN_PIN_4, LOW);
  digitalWrite(DOWN_PIN_5, LOW);
}

// Defining the motor-up function
void motorUp() {
  digitalWrite(UP_PIN_1, HIGH);
  digitalWrite(UP_PIN_2, HIGH);
  digitalWrite(UP_PIN_3, HIGH);
  digitalWrite(UP_PIN_4, HIGH);
  digitalWrite(UP_PIN_5, HIGH);

  digitalWrite(DOWN_PIN_1, LOW);
  digitalWrite(DOWN_PIN_2, LOW);
  digitalWrite(DOWN_PIN_3, LOW);
  digitalWrite(DOWN_PIN_4, LOW);
  digitalWrite(DOWN_PIN_5, LOW);
}

// Defining the motor-down function
void motorDown() {
  digitalWrite(UP_PIN_1, LOW);
  digitalWrite(UP_PIN_2, LOW);
  digitalWrite(UP_PIN_3, LOW);
  digitalWrite(UP_PIN_4, LOW);
  digitalWrite(UP_PIN_5, LOW);

  digitalWrite(DOWN_PIN_1, HIGH);
  digitalWrite(DOWN_PIN_2, HIGH);
  digitalWrite(DOWN_PIN_3, HIGH);
  digitalWrite(DOWN_PIN_4, HIGH);
  digitalWrite(DOWN_PIN_5, HIGH);
}


// the setup function runs once when you press reset or power the board
void setup() {
  // Enabling serial use
  // Serial.begin(9600);
  
  // Start the receiver, enable feedback LED, take LED feedback pin from the internal boards definition
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); 
  
  // Setting pinMode for UP-pins
  pinMode(UP_PIN_1, OUTPUT);
  pinMode(UP_PIN_2, OUTPUT);
  pinMode(UP_PIN_3, OUTPUT);
  pinMode(UP_PIN_4, OUTPUT);
  pinMode(UP_PIN_5, OUTPUT);

  // Setting pinMode for DOWN-pins
  pinMode(DOWN_PIN_1, OUTPUT);
  pinMode(DOWN_PIN_2, OUTPUT);
  pinMode(DOWN_PIN_3, OUTPUT);
  pinMode(DOWN_PIN_4, OUTPUT);
  pinMode(DOWN_PIN_5, OUTPUT);  
}


// the loop function runs over and over again forever
void loop() {
  if (IrReceiver.decode()) {
    // The commented-out code below can be enabled to analyze the remote commands when setting up for the first time
    //IrReceiver.printIRResultShort(&Serial); //Print IR command string to Serial
    //Serial.print(IrReceiver.decodedIRData.command); //Print decoded IR command to Serial
    
    // Do stuff while volume up remains pressed
    if (IrReceiver.decodedIRData.command == 1) {
      if (state == LOW) { 
        state = HIGH;  // Button pressed, so set state to HIGH
        motorUp();
      }
      lastPressTime = millis();
    }
    
    // Do stuff while volume down remains pressed
    if (IrReceiver.decodedIRData.command == 9) {
      if (state == LOW) { 
        state = HIGH;  // Button pressed, so set state to HIGH
        motorDown();
      }
      lastPressTime = millis();
    }
    
    IrReceiver.resume(); // Receive the next value
  }
  
  // Do stuff when button isn't pressed anymore
  if (state == HIGH && millis() - lastPressTime > MAX_TIME) {
    state = LOW; // Haven't heard from the button for a while, so not pressed
    motorOff();
  }
}
