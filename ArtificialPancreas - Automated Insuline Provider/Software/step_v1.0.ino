/*
  pin 8   ->  in-A
  pin 9   ->  in-B
  pin 10  ->  in-C
  pin 11  ->  in-D
  
  pin 13 led output
*/

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  for(int j=0;j<10;j++){//10 revolutions right
    oneRightHighTorque();
  }
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  for(int j=0;j<10;j++){//10 revolutions left
    oneLeftHighTorque();
  }
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
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