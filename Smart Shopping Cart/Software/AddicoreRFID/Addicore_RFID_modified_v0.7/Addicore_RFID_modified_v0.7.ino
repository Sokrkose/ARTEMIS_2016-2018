#include <AddicoreRFID.h>
#include <SPI.h>
#include <LiquidCrystal.h>

#define  uchar unsigned char
#define uint  unsigned int

uchar fifobytes;
uchar fifoValue;

const int chipSelectPin = 10; // Slave Select pin
const int NRSTPD = 6; // RESET RFID pin

float sum = 0 ; // Purchasing' money
int flag = 0;
int mode = 0;   // ADD MODE

int buttonReadPin = 7;

int RSpin = 9; 
int ENpin = 8;
int d7pin = 2;
int d6pin = 3;
int d5pin = 4;
int d4pin = 5;

LiquidCrystal lcd(RSpin, ENpin, d4pin, d5pin, d6pin, d7pin);

AddicoreRFID myRFID; // create AddicoreRFID object to control the RFID module

uchar ID = '\0';

uchar status;

//Maximum length of the array
#define MAX_LEN 16

  int Nike = 80;
  int Sampoo = 10;
  int Popcorn = 4;
 
void setup() {                
  Serial.begin(9600);                        // RFID reader SOUT pin connected to Serial RX pin at 9600bps 
  SPI.begin();
  
  pinMode(chipSelectPin,OUTPUT);              // Set digital pin 10 as OUTPUT to connect it to the RFID /ENABLE pin 
    digitalWrite(chipSelectPin, LOW);         // Activate the RFID reader
  pinMode(NRSTPD,OUTPUT);                     // Set digital pin 10 , Not Reset and Power-down
    digitalWrite(NRSTPD, HIGH);

  myRFID.AddicoreRFID_Init();  
  
  lcd.begin(16, 2);                           // Determine the size of LCD 

}

void loop()
{
  if(digitalRead(buttonReadPin) == 1)  flag++;

  if(flag%2 == 1){
    // digitalWrite(13, HIGH);
    mode = 1;   // SUB MODE
    LCD(mode, sum, ID);
  }else{
    // digitalWrite(13, LOW);
    mode = 0;   // ADD MODE
    LCD(mode, sum, ID);
  }

  uchar i, tmp;

  uchar str[MAX_LEN];
  uchar RC_size;
  uchar blockAddr;  //Selection operation block address 0 to 63
  String mynum = "";

  str[1] = 0x4400;
  //Find tags, return tag type
  status = myRFID.AddicoreRFID_Request(PICC_REQIDL, str); 
  if (status == MI_OK)
  {
          Serial.println("RFID tag detected");
         // Serial.print("Tag Type:\t\t");
          uint tagType = str[0] << 8;
          tagType = tagType + str[1];
          
  }

  //Anti-collision, return tag serial number 4 bytes
  status = myRFID.AddicoreRFID_Anticoll(str);

 
  if(status == MI_OK)
  {
          ID = str[0] ^ str[1] ^ str[2] ^ str[3];
          Serial.print("The tag's id is:\t");
          Serial.println(ID);
            
            // Should really check all pairs, but for now we'll just use the first
            if(ID == 234)                      //You can change this to the first byte of your tag by finding the card's ID through the Serial Monitor
            {
                Serial.print("\n Nike:");
                Serial.println(Nike);
                
                if(mode == 0){
                  sum = sum + Nike;  
                }else{
                  sum = sum - Nike;
                  if(sum < 0) sum = 0;
                }

                LCD(mode, sum, ID);

                isStillHere(str);
            }
            
            else if(ID == 5) 
            {            
                Serial.print("\n Sampoo: ");
                Serial.println(Sampoo);

                if(mode == 0){
                  sum = sum + Sampoo;  
                }else{
                  sum = sum - Sampoo;
                  if(sum < 0) sum = 0;  
                }
               
                LCD(mode, sum, ID);
                
                isStillHere(str);
            }
            else if (ID == 195)
            {
                Serial.print("\n Popcorn: ");
                Serial.println(Popcorn);

                if(mode == 0){
                  sum = sum + Popcorn;  
                }else{
                  sum = sum - Popcorn;
                  if(sum < 0) sum = 0;  
                }

                LCD(mode, sum, ID);
            
                isStillHere(str);
            }
                        
            delay(10);
  }
    
        myRFID.AddicoreRFID_Halt();      //Command tag into hibernation              

}


void isStillHere(uchar str[MAX_LEN])
{
  status = myRFID.AddicoreRFID_Anticoll(str);
   
  while(status == MI_OK) 
  {
    delay(500);

    status = myRFID.AddicoreRFID_Anticoll(str);    
  }
}

void LCD(int mode,float  sum,uchar ID)
{
  lcd.clear();
  lcd.setCursor(0,0);
  if(mode == 0){
    lcd.print("ADD");
  }else{ 
    lcd.print("SUB");
  }
  
  lcd.setCursor(9,0);
  lcd.print(sum);
  
  lcd.setCursor(0,1);
  if(ID == 234){
    lcd.print("Nike");
  }else if(ID == 5){
    lcd.print("Sampoo");
  }else if(ID == 195){
    lcd.print("Popcorn");  
  }
}

