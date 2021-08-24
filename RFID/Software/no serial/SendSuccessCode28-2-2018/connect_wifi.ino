void connect_wifi(String cmd, int t)
{
  int temp=0,i=0;
  while(1)
  {
//    Serial.println(cmd);
    client.println(cmd); 
    while(client.available())
    {
      if(client.find("OK"))
      i=8;
    }
    delay(t);
    if(i == 5) {
      lcd.clear();
      lcd.print("WIFI problem");
      delay(2000);
      break;
    }
    else if(i == 8) {
      break;  
    }
    
    i++;
  }
//  if(i==8)
//  Serial.println("OK");
//  else
//  Serial.println("Error");
}
