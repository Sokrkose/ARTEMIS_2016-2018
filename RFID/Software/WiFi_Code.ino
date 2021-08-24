


#include "SoftwareSerial.h"
//Data comes in pin 0, Rx

String ssid ="elab";

String password="4!Ti4?Ti_posa?";
String com;

SoftwareSerial esp(6, 7);// RX, TX


void setup() {
  esp.begin(115200);
  
  Serial.begin(115200);
  
  reset();
  //connectWifi();
  setserver();
}

//reset the esp8266 module

void reset() {  
  esp.println("AT+RST");  
  delay(1000);  
  
  if (esp.find("OK")) Serial.println("Module Reset");
  else Serial.println("Module not found");
}


//connect to your wifi network

void connectWifi() {

  String cmd = "AT+CWJAP=\"" +ssid+"\",\"" + password + "\"";
  
  esp.println(cmd);
 
  delay(4000);
  
  if(esp.find("OK")) {
    Serial.println("Connected!");
  } 
  else {
    Serial.println("Cannot connect to wifi");
    connectWifi(); 
    }
    
 }

 void setserver(){
     do {
      esp.println("AT+CIPMUX=1");
      delay(1000);
     } while(!esp.find("OK"));

     do {
      esp.println("AT+CIPSERVER=1,80");
      delay(1000);
     } while(!esp.find("OK"));
 }


void autoasto(){
     do {
      esp.println("AT+CIPSTATUS");
      while(esp.available()){
         Serial.println((esp.readString()));
      }
      delay(1000);
     } while(!esp.find("OK"));
}

void take_data(){
  //if (Serial.available()) esp.

  
}
void loop() {
  autoasto();


}
