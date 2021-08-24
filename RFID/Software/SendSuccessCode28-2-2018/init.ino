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
      
      check4IP(5000);
      if(!No_IP)
      {
        Serial.println("Connecting Wifi....");
        delay(500);
        connect_wifi("AT+CWJAP=\"elab\",\"artemis2015\"",7000);         //provide your WiFi username and password here
     // connect_wifi("AT+CWJAP=\"vpn address\",\"wireless network\"",7000);
      }
      else
        {
        }
      Serial.println("Wifi Connected"); 
      //get_ip();
      delay(1000);
      Serial.println("SERVER IP Address:" +IP);
      connect_wifi("AT+CIPMODE=0",100);
      connect_wifi("AT+CIPMUX=1",100);
      //connect_wifi("AT+CIPSTART=1,80",100);
}
