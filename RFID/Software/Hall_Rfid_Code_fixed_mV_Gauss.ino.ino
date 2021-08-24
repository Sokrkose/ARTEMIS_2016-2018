    /*
    * Arduino Door Lock Access Control Project
    *                
    * by Dejan Nedelkovski, www.HowToMechatronics.com
    * 
    * Library: MFRC522, https://github.com/miguelbalboa/rfid
    */
    #include <SPI.h>
    #include <MFRC522.h>
    #include <LiquidCrystal.h>
   
    #define RST_PIN   9
    #define SS_PIN    10
    #define TAG_LIMIT 3
    
    //For the hall sennsor part
    //#define TOMILLIGAUSS 1953L  // For A1301: 2.5mV = 1Gauss, and 1024 analog steps = 5V, so 1 step = 1953mG
    #define TOMILLIGAUSS 3756L  // For A1302: 1.3mV = 1Gauss, and 1024 analog steps = 5V, so 1 step = 3756mG, exoume hall effevt 02K-->A1302K
    #define LOCKED__DOOR 100
    #define NOFIELD 505L    // Analog output with no applied field, calibrate this


    byte readCard[4];
    char* myTags[TAG_LIMIT] = {};
    int tagsCount = 0;
    String tagID = "E0 E0 5D 1A";
    boolean successRead = false;
    boolean correctTag = false;
    // Create instances
    MFRC522 mfrc522(SS_PIN, RST_PIN);
    const int rs = 2, en = 3, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
    LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
    void setup() {
      // Initiating

      Serial.begin(9600);  //For the hall sennsor part
      
      SPI.begin();        // SPI bus
      mfrc522.PCD_Init(); //  MFRC522
      lcd.begin(16, 2);   // LCD screen
      // Prints the initial message
      lcd.print("-No Master Tag!-");
      lcd.setCursor(0, 1);
      lcd.print("SCAN NOW");
      // Waits until a master card is scanned
      while (!successRead) {
        successRead = getID();
        if ( successRead == true) {
          myTags[tagsCount] = strdup(tagID.c_str()); // Sets the master tag into position 0 in the array
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Master Tag Set!");
          tagsCount++; //now tagscount=1
        }
      }
      successRead = false;
      printNormalModeMessage();
    }
    void loop() {

       
        successRead = getID();
        while (!successRead){
          successRead = getID();
          DoMeasurement();

        }
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(tagID.c_str());
        delay(1500);
        correctTag = false;
        // Checks whether the scanned tag is the master tag
        if (tagID == myTags[0]) {
          lcd.clear();
          lcd.print("Program mode:");
          lcd.setCursor(0, 1);
          lcd.print("Add/Remove Tag");
          successRead = getID();
          while (!successRead) {
            
            successRead = getID();
            if ( successRead == true) {
              for (int i = 0; i < TAG_LIMIT; i++) {
                if (tagID == myTags[i]) {
                  if(tagID == myTags[0])
                  {
                    lcd.clear();
                    lcd.print("Master Tag can't");
                    lcd.setCursor(3,1);
                    lcd.print("be removed"); 
                     //isws thelei k edw return 
                       
                  }
                  else{
                    //myTags[i] = "";
                    removeTagID(i);
                    lcd.clear();
                    lcd.setCursor(0,0);
                    lcd.print(tagsCount);
                    delay(1500);
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Tag Removed!");
                  }
                  printNormalModeMessage();
                  return;
                }
              }
            if(tagsCount<TAG_LIMIT){
                myTags[tagsCount] = strdup(tagID.c_str());
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print(tagsCount);
              delay(1500);
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print(myTags[tagsCount]);
              delay(1500);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("   Tag Added!");
              printNormalModeMessage();
              tagsCount++;
              return;
            }
            else{
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Tags list full!");
              printNormalModeMessage();
              return;
            }
            }
          }
        }
        successRead = false;
        // Checks whether the scanned tag is authorized
        if (tagID!=myTags[0])
        {
          for (int i = 0; i < TAG_LIMIT; i++) {
          if (tagID == myTags[i]) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(" Access Granted!");
            printNormalModeMessage();
            correctTag = true;
          }
        }
        if (correctTag == false /*&& tagID!=myTags[0]*/) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(" Access Denied!");
          printNormalModeMessage();
         }
        }
   }
    uint8_t getID() {
      // Getting ready for Reading PICCs
      if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
        return 0;
      }
      if ( ! mfrc522.PICC_ReadCardSerial()) {   //Since a PICC placed get Serial and continue
        return 0;
      }
      tagID = "";
      for ( uint8_t i = 0; i < 4; i++) {  // The MIFARE PICCs that we use have 4 byte UID
        readCard[i] = mfrc522.uid.uidByte[i];
        tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
      }
      tagID.toUpperCase();
      mfrc522.PICC_HaltA(); // Stop reading
      return 1;
    }
    void printNormalModeMessage() {
      delay(1500);
      lcd.clear();
      lcd.print("-Access Control-");
      lcd.setCursor(0, 1);
      lcd.print(" Scan Your Tag!");
    }
    void removeTagID(int index){
      for(int i=index;i<tagsCount;i++){
        myTags[i]=myTags[i+1];
      }
      tagsCount--;
    }

    //For hall sensor part
    
    void DoMeasurement()
    {
    // measure magnetic field
      int raw = analogRead(0);   // Range : 0..1024
    
    //  Uncomment this to get a raw reading for calibration of no-field point
    //  Serial.print("Raw reading: ");
    //  Serial.println(raw);
    
      long compensated = raw - NOFIELD;                 // adjust relative to no applied field 
      long gauss = compensated * TOMILLIGAUSS / 1000;   // adjust scale to Gauss
    
      Serial.print(gauss);
      Serial.print(" Gauss ");

    //Needs change
    
      if (gauss == 11){
          Serial.println("(South pole) Door Unlocked");
        }
      else if(gauss < 0){
        Serial.println("(North pole) Door Locked");
      }
      else{ 
        Serial.println("Door Locked");
      }  
    }
