#include <Servo.h>
#include <SoftwareSerial.h>                                                     

Servo myservo;
int Power = 0; 


int pos = 0;
const int CS_PIN = 7;

const int UD_PIN = 8;
const int INC_PIN = 9;
const int MOTOR_1_X = 11;
const int MOTOR_1_Y = 10;
const int MOTOR_2_X = 12;
const int MOTOR_2_Y = 13;

void setup(){
  Serial.begin(9600);
  //motor pins
  pinMode(CS_PIN, OUTPUT);
  pinMode(UD_PIN, OUTPUT);
  pinMode(INC_PIN, OUTPUT);
  
  pinMode(MOTOR_1_X, OUTPUT);
  pinMode(MOTOR_1_Y, OUTPUT);
  pinMode(MOTOR_2_X, OUTPUT);
  pinMode(MOTOR_2_Y, OUTPUT);
  digitalWrite(INC_PIN, HIGH);
  digitalWrite(CS_PIN, LOW);  
  pinMode(4, OUTPUT);
}

void loop(){
  while (Serial.available()) { // If data is available to read
      byte state = Serial.read(); // read it and store it in val
      Serial.print("State:");
      Serial.print(state);
  
    if(state == 49){
      Serial.println("F");
      GoBackward();
    } else if(state == 50) {
      Serial.println("B");
      GoForward();
    } else if(state == 51) {
      Serial.println("L");
      TurnRight();
      state = 48;
    } else if(state == 52) {
      Serial.println("R");
      TurnLeft();
      state = 48;
    } else if(state == 48) {
      Serial.println("S");
      Stop();
    }

    if (state == 53) {
       Serial.println("Slow");
       setSpeedSlow();
    } else if(state == 54){
       Serial.println("Fast");
       setSpeedFast();
    }
  }
}

void setSpeedSlow(){
   for (int i = 0; i <= 10; i++) {
    digitalWrite(UD_PIN, HIGH); delayMicroseconds(5);  // Set to increment
    digitalWrite(INC_PIN, LOW); delayMicroseconds(5);  // Pulse INC pin low
    digitalWrite(INC_PIN, HIGH);
  }
}

void setSpeedFast(){
  for (int i = 0; i <= 10; i++) {
    digitalWrite(UD_PIN, LOW); delayMicroseconds(5);   // Set to decrement
    digitalWrite(INC_PIN, LOW); delayMicroseconds(5);  // Pulse INC pin low
    digitalWrite(INC_PIN, HIGH);
  }
}


void GoForward(){
  digitalWrite(MOTOR_1_X, LOW);
  digitalWrite(MOTOR_1_Y, HIGH);
  digitalWrite(MOTOR_2_X, LOW);
  digitalWrite(MOTOR_2_Y, HIGH);
}

void GoBackward(){
  digitalWrite(MOTOR_1_X, HIGH);
  digitalWrite(MOTOR_1_Y, LOW);
  digitalWrite(MOTOR_2_X, HIGH);
  digitalWrite(MOTOR_2_Y, LOW);
}

void TurnRight(){
  myservo.attach(4);
  for (pos = 0; pos <= 10; pos += 1) {
     myservo.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);  
  }
  myservo.detach();
}

void TurnLeft(){
  myservo.attach(4);
  for (pos = 180; pos >= 170; pos -= 1) {
     myservo.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);  
  }
  myservo.detach();
}

void Stop(){
  digitalWrite(MOTOR_1_X, LOW);
  digitalWrite(MOTOR_1_Y, LOW);
  digitalWrite(MOTOR_2_X, LOW);
  digitalWrite(MOTOR_2_Y, LOW);
}
