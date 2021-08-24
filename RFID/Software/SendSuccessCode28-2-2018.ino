#include<SoftwareSerial.h>
SoftwareSerial client(6,7); //RX, TX

String webpage="";
int counter=0;
int i=0,k=0;
String readString;
int x=0;

boolean No_IP=false;
String IP="192.168.0.114"; //PUT IP
char temp1='0';

String name="<p>Circuit Digest</p>";   //22
String dat="<p>Data Received Successfully.....</p>";     //21
     
void check4IP(int t1)
{
  int t2=millis();
  while(t2+t1>millis())
  {
    while(client.available()>0)
    {
      if(client.find("WIFI GOT IP"))
      {
        No_IP=true;
      }
    }
  }
}

void get_ip()
{
  IP="";
  char ch=0;
  while(1)
  {
    client.println("AT+CIFSR");
    while(client.available()>0)
    {
      if(client.find("STAIP,")) //STAIP APIP..CHECK IT
      {
        delay(1000);
        Serial.print("IP Address:");
        while(client.available()>0)
        {
          ch=client.read();
          if(ch=='+')
          break;
          IP+=ch;
        }
      }
      if(ch=='+')
      break;
    }
    if(ch=='+')
    break;
    delay(1000);
  }
  Serial.print(IP);
  Serial.print("Port:");
  Serial.println(80);
}

void connect_wifi(String cmd, int t)
{
  int temp=0,i=0;
  while(1)
  {
    Serial.println(cmd);
    client.println(cmd); 
    while(client.available())
    {
      if(client.find("OK"))
      i=8;
    }
    delay(t);
    if(i>5)
    break;
    i++;
  }
  if(i==8)
  Serial.println("OK");
  else
  Serial.println("Error");
}

void wifi_init()
{
      connect_wifi("AT",1000);
      connect_wifi("AT+CWMODE=3",1000);
      connect_wifi("AT+CWQAP",1000);  
      connect_wifi("AT+RST",5000);
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

void setup() 
{
   Serial.begin(9600);
   client.begin(115200);
   wifi_init();
   Serial.println("System Ready..");
}

void loop() 
{
//  k=0;
//  Serial.println("Please Refresh your Page");
// while(k<10000)
//  {
//   k++;
//   while(client.available())
//   {
//    if(client.find("OK"))  //kai edw mia allagh
//    {
//      Serial.println("Start Printing");
//      Send();
//      Serial.println("Done Printing");
//      delay(1000);
//    }
//  }
//  delay(1);
// }
Serial.println("Counter is:" + String(counter));
Send();
delay(2000);

}

void Send()
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
      
      webpage="GET http://155.207.26.179/test1.php?status="+String(counter)+" HTTP/1.0\r\n\r\n";
      sendwebdata(webpage);
      counter++;
    
}

