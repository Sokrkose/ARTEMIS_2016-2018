#include<SPI.h>
//#include<nRF24L01.h>
#include<RF24.h>

#define m1o1 5
#define m1o2 6
#define m2o1 A3
#define m2o2 A2

const uint64_t pipe[1]= {0xF0F0F0F0E1LL};
RF24 radio(7,8);

typedef struct
{
  int X;
  int Y;
}positions;

positions pos;

//int ack[1] = {990};
void setup()
{
  //---------------------Serial & NRF //
  Serial.begin(9600);
  radio.begin();
  delay(100);
  radio.setAutoAck(true);
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.openReadingPipe(1,pipe[0]);
  radio.startListening();
  radio.setRetries(15,15);
  
  //--------------------Motors //

  setPwmFrequency(m1o1,256);
  setPwmFrequency(m1o2,256);
}
void loop()
{
      for(int i=0;i<1023;i++){
      pos.X=i;
      pos.Y=i;
      setMotors();
      delay(10);
      }
      for(int i=1024;i>0;i--){
      pos.X=i;
      pos.Y=i;
      setMotors();
      delay(10);
      }
        
}

boolean getPack(){
  if(radio.available())
    {
      radio.read(&pos,sizeof(pos));
      radio.writeAckPayload(1,&pos,sizeof(pos));
      //Serial.println("X = "+String(pos.X)  +  "  Y = "+String(pos.Y));
      return 1;
    }
    return 0;
}

void setMotors(){
  int vx, vy,mA,mB;
  vx=pos.X-512;
  vy=pos.Y-512;
  mA=vy;
  mB=vx;
  if(mA>=0){
    analogWrite(m1o1,0);
    analogWrite(m1o2,mA);
  }else{
    analogWrite(m1o1,0-mA);
    analogWrite(m1o2,0);
  }
  if(mB>=0){
    analogWrite(m2o1,0);
    analogWrite(m2o2,mB);
  }else{
    analogWrite(m2o1,0-mB);
    analogWrite(m2o2,0);
  }
}

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
