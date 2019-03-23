#include <Servo.h>

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

Servo myservo;

void setup() {
  Serial.begin(9600);

  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  myservo.attach(11);
  myservo.write(90);
}

void loop() {
  distance = getDistance();
  int distanceR = 0;
  int distanceL =  0;
  delay(40);
 
  if(distance <= 20)
  {
    brake();
    delay(100);
    moveBackward();
    delay(300);
    brake();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);

    if(distanceR >= distanceL) {
      turnRight();
      brake();
    }
    else {
      turnLeft();
      brake();
    }
  }
  else {
    moveForward();
  }
}

int lookRight() {
  myservo.write(30); 
  delay(500);
  int distance = getDistance();
  delay(100);
  myservo.write(90); 
  return distance;
}

int lookLeft() {
  myservo.write(150); 
  delay(500);
  int distance = getDistance();
  delay(100);
  myservo.write(90); 
  return distance;
  delay(100);
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
