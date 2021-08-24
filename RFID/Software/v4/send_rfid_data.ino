void send_rfid_data() {
  // Select one of the cards
  if (mfrc522.PICC_ReadCardSerial()) 
  {
    Serial.print("UID tag :");
    String content= "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
       Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       Serial.print(mfrc522.uid.uidByte[i], HEX);
       content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
       content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }

    Serial.println();

    Send(2,"tag",content.substring(1));

    
    //check the we send data successfully
    if(string_search(esp_buffer, "SUCCESS", count-1, 7))
    {
      Serial.println("Tag added");
      lcd.clear();
      lcd.print("Tag added");
    }
    else if(string_search(esp_buffer, "DELETED", count-1, 7))
    {
      Serial.println("Tag deleted");
      lcd.clear();
      lcd.print("Tag deleted");
    }
    else if(string_search(esp_buffer, "not found", count-1, 9))
    {
      Serial.println("Tag not found");
      lcd.clear();
      lcd.print("Tag not found");
    }
    else
    {
      Serial.println("Send failed");
      lcd.clear();
      lcd.print("Send failed");
    }
  }
  
}
