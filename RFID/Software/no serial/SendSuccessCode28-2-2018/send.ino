void Send(int mode,String variable,String value)
{
//      Serial.println("AT+CIPSTART=0,\"TCP\",\"192.168.0.114\",80");
      client.println("AT+CIPSTART=0,\"TCP\",\"192.168.0.114\",80");

      delay(1500);
      
      while(client.available())
      {
        if(client.find("OK"))  //kai edw mia allagh
        {
//          Serial.println("OK");
          break;
        }
      }
      //String send_string;
  
      if(mode==1)  
        webpage="GET http://192.168.0.114/door_update.php?" + variable + "=" + value + " HTTP/1.0\r\n\r\n";
      if(mode==2)
        webpage="GET http://192.168.0.114/active_update.php?" + variable + "=" + value + " HTTP/1.0\r\n\r\n";
        
   
      sendwebdata(webpage);
  
    
}
