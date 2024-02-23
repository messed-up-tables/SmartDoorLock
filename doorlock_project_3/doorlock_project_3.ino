
#include "pins_arduino.h"
#include <Keypad.h>

#define unlock_button_pin A6
#define solenoid_pin 2
#define MAX_PASS_TIME 1000

//----------------------------------------------------------------------------Keypad
const byte rows = 4; // How many rows in keypad
const byte cols = 4; // How many columns in keypad
byte row_pins[rows] = {12, 11, 10, 9};  /*Pins for Keypad Rows*/
byte col_pins[cols] = {8, 7, 6, 5};   /*Pins for Keypad Columns*/
char Keys[rows][cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};
Keypad myKeypad = Keypad(makeKeymap(Keys), row_pins, col_pins, rows, cols); 

//--------------------------------------------------------------------------Passcode
const int passcodeLength = 4;
int master_code = 1234;
int input_code = 0; // handle corner case of 0000
int pass_input_now = 0; // how many digits have been input
int pass_timer;
int otp_num = -1; //number of otp
int otp[10];

void setup() {
  Serial.begin(9600);
  pinMode(unlock_button_pin, INPUT);
  pinMode(solenoid_pin, OUTPUT);
}

void loop() {
  
  //Serial.println(Read_button_state());
  
  if (readBtnState())
  {
    unlockDoor();
  }
  //-------------------------------------------------------------------Keypad
  else if (char Key = myKeypad.getKey())
  {
    Serial.println(Key);
    if(pass_input_now ==0) pass_timer = millis();
    else{
      if((millis()-pass_timer) > MAX_PASS_TIME)
      pass_input_now = 0;
      input_code = 0;
    }
    pass_input_now = pass_input_now + 1;
    input_code = input_code * 10 + Key - '0';
    Serial.println(input_code);
    if (pass_input_now == passcodeLength) {
      pass_input_now = 0;
      checkMasterCode();
      input_code = 0;
    }
  }
  //---------------------------------------------------------------------OTP
  else if (Serial.available())
  {
    String input = Serial.readString();
    input.trim();
    Serial.println(input);
    if(input == "otp")
    {
      randomSeed(millis());
      otp_num++;
      otp[otp_num] = randNumber(1000,9999);
      Serial.println(otp[otp_num]);
      //need to include timeout 
    }
    input = "";
  }
  
}
