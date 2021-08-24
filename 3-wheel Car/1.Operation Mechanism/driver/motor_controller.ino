/*
 * voltage supply 6 v
 * 3 - 6 
 * 50 -100
 */      

int analogInPin =A0;

float sensorValue = 0;
float outputValue = 0;
float Volt = 0; 

//Testing the DC Motors with
// L293D
//Define Pins
//Motor A
int enableA = 2;
int MotorA1 = 3;
int MotorA2 = 5;

//not used
//Motor B
//int enableB = 3;
//int MotorB1 =6;
//int MotorB2 =7;


int switchpin= 10;

bool reverse;

bool pressed3;

int button;





void setup() 
{
  Serial.begin (9600); //configure pin modes
 // pinMode (button, INPUT);
  pinMode (switchpin, INPUT); 
 // pinMode (button2, INPUT);
  pinMode (enableA, OUTPUT);
  pinMode (MotorA1, OUTPUT);
  pinMode (MotorA2, OUTPUT);
 //pinMode (enableB, OUTPUT);
 // pinMode (MotorB1, OUTPUT);
 // pinMode (MotorB2, OUTPUT); 
  digitalWrite(enableA,HIGH);
 
  pressed3= false;
  reverse =true;
}
void loop()
{

   sensorValue = analogRead(analogInPin);
   outputValue = map(sensorValue, 0, 1023, 0, 255);

   button = digitalRead(switchpin);
   
   if(button == HIGH && !pressed3)
   {
   reverse = !reverse;
   pressed3 = true;
   }
   else if(button == LOW)
   { 
    pressed3 = false;
   }
   
  SetMotorA(outputValue,reverse) ;
 
  
    Volt = (5*outputValue)/255; //The Voltage value
    
    Serial.print("\t Duty Cycle= ");
    Serial.println(outputValue);
    Serial.print("Approximate Voltage Value = ");
    Serial.print(Volt);
    Serial.print("\t Rotation = ");
    
    if(reverse)Serial.print("right");
    else Serial.print("left");
    
  
}

void SetMotorA(float speed, boolean reverse)  
{
  if(reverse)
  {
    digitalWrite(MotorA2, LOW);
    analogWrite(MotorA1,speed);
  }
  else
  {
    digitalWrite(MotorA1, LOW);
    analogWrite(MotorA2,speed);
  }
}
