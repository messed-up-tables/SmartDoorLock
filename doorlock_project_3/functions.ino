

void checkMasterCode(){  
  if(input_code == master_code){
    unlockDoor();
    Serial.println("Master code matched");
  }
  else{
    Serial.println("Wrong code");
  }
}

void checkOTP(){
  if(otp_num == -1) return;
  for(int i = 0; i<= otp_num; ++i)
  {
    if(input_code == otp[i];
    
  }
}
int readBtnState(){
  if(!analogRead(unlock_button_pin))
  {
    return 1;
  }else
  {
    return 0;
  }
}


void unlockDoor() //unlocks the door and then lock the door again after a certain time
{
  digitalWrite(solenoid_pin, HIGH);
  digitalWrite(13, HIGH);
  delay(2000);
  digitalWrite(solenoid_pin, LOW);
  digitalWrite(13, LOW);
}

void lockDoor(){
  digitalWrite(solenoid_pin, LOW);  
}
