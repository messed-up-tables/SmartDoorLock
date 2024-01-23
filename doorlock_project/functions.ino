

void CheckMasterCode(){  
  if(input_code == master_code){
    unlockDoor();
    Serial.println("Master code mathced");
  }
  else{
    Serial.println("Wrong code");
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


void unlockDoor(){
  digitalWrite(solenoid_pin, HIGH);
  delay(3000);
  digitalWrite(solenoid_pin, LOW);
}

void lockDoor(){
  digitalWrite(solenoid_pin, LOW);  
}
