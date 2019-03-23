#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial SerialBLE(10, 11); // RX, TX

int pad_x, pad_y; // Control pad values sent from Andorid device
char bluetoothData; // Received data

// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;

const int echoPin = 2;
const int pingPin = 3;
long duration, distance;

int val = 0;  // Current value of pad

void setup() {
  Serial.begin(9600);

  SerialBLE.begin(9600);  // Initialize Bluetooth commuication
  
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  if (SerialBLE.available()){
    bluetoothData=SerialBLE.read();
    
    ///////// Control Pad on Left /////////
    if(bluetoothData == '1') { // Forward
      val = 1;
      Serial.println('1');
    }
    if(bluetoothData == '3') { // Backward
      val = 3;
      Serial.println('3');
    }
    if(bluetoothData == '4') { // Left
      val = 4;
      Serial.println('4');
    }
    if(bluetoothData == '2') { // Right
      val = 2;
      Serial.println('2');
    }
    if(bluetoothData == '0') { // Do nothing
      val = 0;
      Serial.println('0');  
    }
  }
  
  if (val == 1) {
    moveForward();  
  }
  if (val == 3) {
    moveBackward();
  }
  if (val == 4) {
    turnLeft();
  }
  if (val == 2) {
    turnRight();  
  }
}


void moveForward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  analogWrite(enA, 255);
  analogWrite(enB, 255);
}

void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 

  analogWrite(enA, 255);
  analogWrite(enB, 0);
}

void turnRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 

  analogWrite(enA, 0);
  analogWrite(enB, 255);
}

void brake() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void moveBackward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); 

  analogWrite(enA, 255);
  analogWrite(enB, 255);
}

int getDistance() {
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  delay(100);
  return microsecondsToCentimeters(duration);
}


long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
