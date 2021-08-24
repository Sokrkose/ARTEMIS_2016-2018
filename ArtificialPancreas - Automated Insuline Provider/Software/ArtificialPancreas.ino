
/*
  pin 8   ->  in-A
  pin 9   ->  in-B
  pin 10  ->  in-C
  pin 11  ->  in-D
  
  pin 13 led output
*/
/*yellow --> vcc
 * red --> data
 * white --> gnd
 */
int sensorPin = A0;
int byteread;

//get data from sensor
//send to Bluetooth module
//read data from Bluetooth
//send to stepper motor

void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {

  int sensorVal = analogRead(sensorPin);

  float voltage = (sensorVal / 1024.0) * 5.0;
  float temperature = (voltage - .5) * 100;

  Serial.print("T,");
  Serial.print(temperature);
  Serial.print(",");
  

  if( Serial.available() > 0){
    byteread = Serial.read();
  }
  
  
  
  if (byteread == 1){
    for(int j=0;j<10;j++){//10 revolutions right
       oneRightHighTorque();
    }
    digitalWrite(13, HIGH);
    
  }
  else if(byteread == -1){
    for(int j=0;j<10;j++){//10 revolutions left
      oneLeftHighTorque();
    }
    digitalWrite(13, HIGH);
    
  }
  digitalWrite(13, LOW);
  delay(200);

}





 void oneRightHighTorque(){
    for(int i=0;i<=512;i++){
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      delay(3);
      digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
      delay(3);
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      delay(3);
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
      delay(3);
      }
  }

  void oneLeftHighTorque(){
    for(int i=0;i<=512;i++){
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      delay(3);
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
      delay(3);
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      delay(3);
      digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
      delay(3);
      }
  }
