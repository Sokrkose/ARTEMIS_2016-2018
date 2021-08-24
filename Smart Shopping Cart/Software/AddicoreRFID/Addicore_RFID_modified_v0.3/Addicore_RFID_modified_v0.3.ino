// Example sketch to read the ID from an Addicore 13.56MHz RFID tag
// as found in the RFID AddiKit found at: 
// http://www.addicore.com/RFID-AddiKit-with-RC522-MIFARE-Module-RFID-Cards-p/126.htm

#include <AddicoreRFID.h>
#include <SPI.h>
#include <LiquidCrystal.h>

#define  uchar unsigned char
#define uint  unsigned int


uchar fifobytes;
uchar fifoValue;

AddicoreRFID myRFID; // create AddicoreRFID object to control the RFID module

/////////////////////////////////////////////////////////////////////
//set the pins
/////////////////////////////////////////////////////////////////////
const int chipSelectPin = 10;
const int NRSTPD = 5;

float sum = 0 ; // Purchasing' money
int flag = 0;
int mode = 0;         // ADD MODE

  uchar status;

//Maximum length of the array
#define MAX_LEN 16

void setup() {                
   Serial.begin(9600);                        // RFID reader SOUT pin connected to Serial RX pin at 9600bps 
 
  // start the SPI library:
  SPI.begin();
  
  pinMode(2, INPUT);    // Button that changes the mode (add , subs)

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);// ADD MODE
  
  pinMode(chipSelectPin,OUTPUT);              // Set digital pin 10 as OUTPUT to connect it to the RFID /ENABLE pin 
    digitalWrite(chipSelectPin, LOW);         // Activate the RFID reader
  pinMode(NRSTPD,OUTPUT);                     // Set digital pin 10 , Not Reset and Power-down
    digitalWrite(NRSTPD, HIGH);

  myRFID.AddicoreRFID_Init();  
}

void loop()
{
  if(digitalRead(2) == 1) 
    flag = flag + 1;

  if(flag%2 == 1){
    digitalWrite(13, HIGH);
    mode = 1;   // SUB MODE
  }else{
    digitalWrite(13, LOW);
    mode = 0;   // ADD MODE
  }

  int Nike=80;
  int Sampoo =10;
  int Popcorn =4;
 
    uchar i, tmp, checksum1;

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

 
  if (status == MI_OK)
  {
          checksum1 = str[0] ^ str[1] ^ str[2] ^ str[3];
          Serial.print("The tag's id is:\t");
          Serial.println(checksum1);
            
            // Should really check all pairs, but for now we'll just use the first
            if(checksum1 == 234)                      //You can change this to the first byte of your tag by finding the card's ID through the Serial Monitor
            {
                Serial.print("\n Nike:");
                Serial.println(Nike);

                if(mode == 0)
                {
                  sum = sum + Nike;  
                } 
                else
                {
                  sum = sum - Nike;  
                }

                Serial.println(sum);

                isStillHere(str);
            }
            
            else if(checksum1 == 5) 
            {
              Serial.print(str[0]);            
                Serial.print("\n Sampoo: ");
                
                Serial.println(Sampoo);

                if(mode == 0){
                  sum = sum + Sampoo;  
                }else{
                  sum = sum - Sampoo;  
                }

                Serial.println(sum);

              isStillHere(str);
            }
            else if (checksum1 == 195)
            {
              Serial.print(str[0]); 
              Serial.print("\n Popcorn: ");

              Serial.println(Popcorn);

              if(mode == 0){
                sum = sum + Popcorn;  
              }else{
                sum = sum - Popcorn;  
              }

              Serial.print(sum);
            
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
  Serial.print(str[0]); 
  while(status == MI_OK) 
  {
    delay(10);

    status = myRFID.AddicoreRFID_Anticoll(str);    
  }
}

