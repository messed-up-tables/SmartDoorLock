#include "pins_arduino.h"
#include<Keypad.h>

#define unlock_button_pin A6
#define solenoid_pin 2

byte rowPins[ROWS] = {12, 11, 10, 9};  /*Pins for Keypad Rows*/
byte colPins[COLS] = {8, 7, 6, 5};   /*Pins for Keypad Columns*/
const byte ROWS = 4; // How many rows in keypad
const byte COLS = 4; // How many columns in keypad

char Keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
}; // Keymap

Keypad myKeypad = Keypad(makeKeymap(Keys), rowPins, colPins, ROWS, COLS); /*Function for Keypad*/

const int passcodeLength = 4;
int master_code = 1234;
int input_code = 0; // handle corner case of 0000
int pass_input_now = 0; // how many digits have been input

void setup() {
  Serial.begin(9600);
  pinMode(Unlock_button_pin, INPUT);
  pinMode(Solenoid_pin, OUTPUT);
}

void loop() {
  //Serial.println(Read_button_state());
  if(readBtnState()){
    unlockDoor();
    //delay(3000);
    //lockDoor();
  }
  char Key = myKeypad.getKey(); // take input
  if (Key){
    Serial.println(Key);
    pass_input_now = pass_input_now + 1;
    input_code = input_code * 10 + Key - '0';
    Serial.println(input_code);
    if(pass_input_now == passcodeLength){
      pass_input_now = 0;
      CheckMasterCode();
      input_code = 0;
    }
  }
}
