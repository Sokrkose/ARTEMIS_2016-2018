
// map motor poles to Arduino pins
#define motor1out1 5 
#define motor1out2 4
#define motor2out1 7
#define motor2out2 8
#define motor3out1 2
#define motor3out2 3

// map L293d motor enable pins to Arduino pins
#define enable1 9
#define enable2 11
#define enable3 10

#define M1_MAX_SPEED 100
#define M2_MAX_SPEED 100

void setup() {
     Serial.begin(9600);
   // set mapped L293D motor1 and motor 2 enable pins on Arduino to output (to turn on/off motor1 and motor2 via L293D)
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
  pinMode(enable3, OUTPUT);


  // set mapped motor poles to Arduino pins (via L293D)
  pinMode( motor1out1 , OUTPUT);
  pinMode( motor1out2, OUTPUT);
  pinMode( motor2out1, OUTPUT);
  pinMode( motor2out2 , OUTPUT);
  pinMode( motor3out1, OUTPUT);
  pinMode( motor3out2 , OUTPUT);
  motorspeed(0, 0,0);
}

int mspeed = 100;

void loop() {
  motorspeed(255, 255,255);
 
// spin both motors in one direction
  Serial.print("BOTH MOTORS FORWARD @ SPEED: ");
  Serial.println(mspeed);


  motorclock(1);
  motorclock(2);
  motorclock(3);
  delay(2000);

// stop both motors
  Serial.println("BOTH MOTORS STOP FOR 2 SEC."); 
  motorstop(1);
  motorstop(2);
  motorstop(3);
  delay(2000);

  motoranticlock(1);
  motoranticlock(2);
  motoranticlock(3);
 
  delay(2000);

  motorstop(1);
  motorstop(2);
  motorstop(3);

  delay(2000);

  //motoranticlock(1);
  //motorclock(2);
 // motorstop(3);
  
  //delay(2000);

    
  }

// Stop motor
// motor Digital Pin
void motorstop(int motor){
  if(motor == 1){
    digitalWrite(motor1out1,LOW);
    digitalWrite(motor1out2,LOW);  
  }
  else if (motor == 2){
    digitalWrite(motor2out1,LOW);
    digitalWrite(motor2out2,LOW);  
  }
  else if (motor == 3){
    digitalWrite(motor3out1,LOW);
    digitalWrite(motor3out2,LOW);
  }

}

void motorclock(int motor){
  if(motor == 1){
    digitalWrite(motor1out1,HIGH);
    digitalWrite(motor1out2,LOW);  
  }
  else if (motor == 2){
      digitalWrite(motor2out1,HIGH);
    digitalWrite(motor2out2,LOW);  
  }
  else if (motor == 3){
    digitalWrite(motor3out1,HIGH);
    digitalWrite(motor3out2,LOW);
  }
}

void motoranticlock(int motor){
  if(motor == 1){
    digitalWrite(motor1out1,LOW);
    digitalWrite(motor1out2,HIGH);  
  }
  else if (motor == 2){
      digitalWrite(motor2out1,LOW);
    digitalWrite(motor2out2,HIGH);  
  }
  else if (motor == 3){
    digitalWrite(motor3out1,LOW);
    digitalWrite(motor3out2,HIGH);
  }
}

void motorspeed(int m1speed, int m2speed,int m3speed){
  analogWrite(enable1,m1speed);
  analogWrite(enable2,m2speed);
  analogWrite(enable3,m3speed);
}


  
