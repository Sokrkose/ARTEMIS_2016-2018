void Send(int mode,String variable,String value)
{
      //connect_wifi("AT+CIPSTART=0,\"TCP\",\"192.168.0.114\",80",1000);
      Serial.println("AT+CIPSTART=0,\"TCP\",\"192.168.0.114\",80");
      client.println("AT+CIPSTART=0,\"TCP\",\"192.168.0.114\",80");
      while(client.available())
     {
       if(client.find("OK"))  //kai edw mia allagh
       {
          Serial.println("OK");
          break;
      }
    }
    if(mode==1)  
      webpage="GET http://155.207.26.179/test1.php?" + variable + "=" + value + " HTTP/1.0\r\n\r\n";
    
    
    sendwebdata(webpage);
      
    
}
