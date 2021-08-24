/*  Code by Xenios
 *   slight changes by Stratis
 *   
 *   3/3/2018
 *   Artemis - OmniWheel_project
 *   
 *   Software for: RemoteController side
 * 
 */

#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

#define X_PIN A0
#define Y_PIN A1

#define AcceptableTime 200

int msg[1] = {1};
int rec[1] = {5};
bool stat = true;
RF24 radio(7,8);
unsigned long time;
const uint64_t pipe[1] = {0xF0F0F0F0E1LL};

typedef struct {
  int x;
  int y;
} positions;

positions TxPos;
positions RxPos;
positions lastPos;
  
void setup() {
  Serial.begin(9600);
  radio.begin();
  delay(1000);
  
  radio.setAutoAck(true);
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.openWritingPipe(pipe[0]);
  radio.setRetries(15,15);
  
  TxPos.x=analogRead(X_PIN);
  TxPos.y=analogRead(Y_PIN);
  lastPos = TxPos;
}

void loop() {
  if(stat)
  {
    radio.stopListening();
    time=millis();
    
    if( radio.write(&TxPos,sizeof(positions) ) ){
      //Serial.println("Sent >");
      if(radio.isAckPayloadAvailable()){
       radio.read(&RxPos,sizeof(positions));
      }
    }
    else {
        Serial.println("failed tx...");
    }
      
    time=millis()-time;
    if (time > AcceptableTime){
      Serial.println("DELAYED TRANSMISSION || time: "+ String(time) +"ms");
    }
  }
  
  TxPos.x=analogRead(X_PIN);
  TxPos.y=analogRead(Y_PIN);
  if(lastPos.x == TxPos.x && lastPos.y == TxPos.y) stat=false;
  else stat=true;
  
  delay(1);
}
