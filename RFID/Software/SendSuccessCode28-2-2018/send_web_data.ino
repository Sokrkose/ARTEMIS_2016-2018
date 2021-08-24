void sendwebdata(String webPage)
{
    //int ii=0;
    // while(1)
     //{
      unsigned int l=webPage.length();
      Serial.println("AT+CIPSEND=0," + String(l));
      client.println("AT+CIPSEND=0," + String(l));
      //connect_wifi("AT+CIPSEND=0," + String(l),1);
      //Serial.println(ii);
      //Serial.println(l+2);
      //client.println(l+2);
      delay(100);
      Serial.print(webPage);
      client.print(webPage);
      delay(500);
      while(client.available())
      {
        //Serial.print(Serial.read());
        if(client.find("OK"))
        {
          Serial.println("OK    || data send");
          //ii=11;
          break;
        }
      }
      //if(ii==11)
      //break;
      delay(100);
     //}
}
