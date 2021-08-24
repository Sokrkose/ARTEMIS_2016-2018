#include<SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
SoftwareSerial client(6,7); //RX, TX

const int hall_pin=0;

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

     
//functions
void check4IP(int t1);
void connect_wifi(String cmd, int t);
void dump_data();
void get_ip();
void wifi_init();
void Send(int mode,String variable,String value);
void sendwebdata(String webPage);
void send_rfid_data();

//end of funtions

///////////////////////////////////////////////////////
////////////////////// SETUP //////////////////////////
///////////////////////////////////////////////////////
void setup() 
{
   pinMode(hall_pin, INPUT);

   //esp setup
   Serial.begin(9600);
   client.begin(115200);
   wifi_init();

   //rfid setup
   SPI.begin();      // Initiate  SPI bus
   mfrc522.PCD_Init();   // Initiate MFRC522
   
   Serial.println("System Ready..");
}


///////////////////////////////////////////////////////
////////////////////// LOOP ///////////////////////////
///////////////////////////////////////////////////////
void loop() 
{
  Serial.println("Counter is:" + String(counter));
  Send(1,"status",String(analogRead(hall_pin)));
  dump_data();
  delay(2000);

  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent()) 
  {
    Serial.println("________________");
    send_rfid_data();
  }
  counter++;
}


