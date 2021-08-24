void wifi_init()
{
      connect_wifi("AT",1000);
      dump_data();
  
      connect_wifi("AT+CWMODE=3",1000);
      dump_data();

      connect_wifi("AT+CWQAP",1000);
      dump_data();

      connect_wifi("AT+RST",5000);
      dump_data();
    
      delay(500);
      connect_wifi("AT+CWJAP=\"elab\",\"artemis2015\"",7000);         //provide your WiFi username and password here

      delay(1000);
//      Serial.println("SERVER IP Address:" +IP);
      connect_wifi("AT+CIPMODE=0",100);
      connect_wifi("AT+CIPMUX=1",100);
}
