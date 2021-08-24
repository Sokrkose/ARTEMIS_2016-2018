#include<SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define threshold 800

const int rs = 2, en = 3, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
//SoftwareSerial client(6,7); //RX, TX
SoftwareSerial client(A1,A2); //RX, TX
const int hall_pin=0;


char esp_buffer[400];
int count;
String webpage="";
int i=0,k=0;
int x=0;
int state,prev_state;

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
bool string_search(char* text,char* c_to_search,int len_text ,int len_search);

//end of funtions

///////////////////////////////////////////////////////
////////////////////// SETUP //////////////////////////
///////////////////////////////////////////////////////
void setup() 
{
   pinMode(hall_pin, INPUT);

   //lcd setup
   lcd.begin(16,2);
   lcd.clear();
   lcd.print("Setting up");
   lcd.setCursor(0,1);
   lcd.print("system...");

   //esp setup
   Serial.begin(9600);
   client.begin(9600);
   //client.begin(115200);
   wifi_init();

   //rfid setup
   SPI.begin();      // Initiate  SPI bus
   mfrc522.PCD_Init();   // Initiate MFRC522

   prev_state = (analogRead(hall_pin)>threshold?1:0);

   Send(1,"status",String(prev_state));
   
   Serial.println("System Ready..");
   lcd.clear();
   lcd.print("System ready");
   
}


///////////////////////////////////////////////////////
////////////////////// LOOP ///////////////////////////
///////////////////////////////////////////////////////
void loop() 
{
  
  state = (analogRead(hall_pin)>threshold?1:0);

  if(state != prev_state) {
    prev_state = state;

    lcd.clear();
    lcd.print("Updating door");
    lcd.setCursor(0,1);
    lcd.print("status...");
    
    Send(1,"status",String(state));
    
    if(string_search(esp_buffer, "SUCCESS", count-1, 7))
    {
      Serial.println("Door status updated");
      lcd.clear();
      lcd.print("Door status");
      lcd.setCursor(0,1);
      lcd.print("updated");
    }
    else
    {
      Serial.println("Update failed");
      lcd.clear();
      lcd.print("Update failed");
    }

    delay(1000);
  }

  lcd.clear();
  lcd.print("Ready for scan");
  
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent()) 
  {
    lcd.clear();
    lcd.print("Identifying tag");
    lcd.setCursor(0,1);
    lcd.print("...");
      
    send_rfid_data();

    delay(2000);
  }
  
  
}


