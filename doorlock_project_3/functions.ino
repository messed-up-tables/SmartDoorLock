byte actualRFID[] = {0xC3, 0x56, 0x89, 0x15};


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
    if(input_code == otp[i]);
    
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

void ReadRFID(){

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }



   
    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    Serial.print(F("In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();

    if (actualRFID[0] == nuidPICC[0] && 
    actualRFID[1] == nuidPICC[1] && 
    actualRFID[2] == nuidPICC[2] && 
    actualRFID[3] == nuidPICC[3] ) {
    Serial.println(F("Door Open"));
    unlockDoor();
    }
    else{
    Serial.println(F("Wrong RFID"));
    }
  


  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}
