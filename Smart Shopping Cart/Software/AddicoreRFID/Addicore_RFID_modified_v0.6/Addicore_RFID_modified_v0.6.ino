#include <AddicoreRFID.h>
#include <SPI.h>
#include <LiquidCrystal.h>

#define  uchar unsigned char
#define uint  unsigned int

uchar fifobytes;
uchar fifoValue;

LiquidCrystal lcd(9, 8, 6, 4, 3, 2);

AddicoreRFID myRFID; // create AddicoreRFID object to control the RFID module
const int chipSelectPin = 10;
const int NRSTPD = 5;

float sum = 0 ; // Purchasing' money
int flag = 0;
int mode = 0;         // ADD MODE

uchar checksum1 = '\0';

uchar status;

//Maximum length of the array
#define MAX_LEN 16

void setup() {                
  Serial.begin(9600);                        // RFID reader SOUT pin connected to Serial RX pin at 9600bps 
  SPI.begin();
  
  pinMode(chipSelectPin,OUTPUT);              // Set digital pin 10 as OUTPUT to connect it to the RFID /ENABLE pin 
    digitalWrite(chipSelectPin, LOW);         // Activate the RFID reader
  pinMode(NRSTPD,OUTPUT);                     // Set digital pin 10 , Not Reset and Power-down
    digitalWrite(NRSTPD, HIGH);

  myRFID.AddicoreRFID_Init();  
  
  lcd.begin(16, 2);

}

void loop()
{
  if(digitalRead(7) == 1) 
    flag = flag + 1;

  if(flag%2 == 1){
    // digitalWrite(13, HIGH);
    mode = 1;   // SUB MODE
    LCD(mode, sum, checksum1);
  }else{
    // digitalWrite(13, LOW);
    mode = 0;   // ADD MODE
    LCD(mode, sum, checksum1);
  }

  int Nike=80;
  int Sampoo =10;
  int Popcorn =4;
 
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
          checksum1 = str[0] ^ str[1] ^ str[2] ^ str[3];
          Serial.print("The tag's id is:\t");
          Serial.println(checksum1);
            
            // Should really check all pairs, but for now we'll just use the first
            if(checksum1 == 234)                      //You can change this to the first byte of your tag by finding the card's ID through the Serial Monitor
            {
                Serial.print("\n Nike:");
                Serial.println(Nike);
                
                if(mode == 0){
                  sum = sum + Nike;  
                }else{
                  sum = sum - Nike;  
                }

                Serial.println(sum);

                LCD(mode, sum, checksum1);

                isStillHere(str);
            }
            
            else if(checksum1 == 5) 
            {            
                Serial.print("\n Sampoo: ");
                Serial.println(Sampoo);

                if(mode == 0){
                  sum = sum + Sampoo;  
                }else{
                  sum = sum - Sampoo;  
                }

                Serial.print(sum);
                
                LCD(mode, sum, checksum1);
                
                isStillHere(str);
            }
            else if (checksum1 == 195)
            {
                Serial.print("\n Popcorn: ");
                Serial.println(Popcorn);

                if(mode == 0){
                  sum = sum + Popcorn;  
                }else{
                  sum = sum - Popcorn;  
                }

                Serial.print(sum);

                LCD(mode, sum, checksum1);
            
                isStillHere(str);
            }

            
  /*
            if(sum >= 100) 
            {
              digitalWrite( 4 , HIGH ) ;
        
            }

  */
            
            Serial.println();
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

void LCD(int mode,float  sum,uchar checksum1)
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
  if(checksum1 == 234){
    lcd.print("Nike");
  }else if(checksum1 == 5){
    lcd.print("Sampoo");
  }else if(checksum1 == 195){
    lcd.print("Popcorn");  
  }
}

