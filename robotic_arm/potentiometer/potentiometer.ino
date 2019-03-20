#include <Servo.h>

Servo base;
Servo left;
Servo right;
Servo claw;

int pot1 = A0;
int pot2 = A1;
int pot3 = A2;
int pot4 = A3;

// Initial (center) positions for servos
int b = 90, l = 90, r = 90, c = 50;

void setup() 
{
  Serial.begin(9600);
  
  base.attach(2);
  left.attach(3);
  right.attach(4);
  claw.attach(5);

  base.write(b);
  left.write(l);
  right.write(r);
  claw.write(c);

  pinMode(pot1,INPUT);
  pinMode(pot2,INPUT);
  pinMode(pot3,INPUT);
  pinMode(pot4,INPUT);

  delay(500);
}

void loop() 
{
  b = analogRead(pot1);
  l = analogRead(pot2);
  r = analogRead(pot3);
  c = analogRead(pot4);
  
  b = map(b, 0, 1023, 10, 170); // maps to base range
  l = map(l, 0, 1023, 10, 170); // maps to left range
  r = map(r, 0, 1023, 10, 170); // maps to right range
  c = map(c, 0, 1023, 20, 95);  // maps to claw range
 
  base.write(b);
  left.write(l);
  right.write(r);
  claw.write(c);
  
  Serial.print(b);
  Serial.print(" : ");
  Serial.print(l);
  Serial.print(" : ");
  Serial.print(r);
  Serial.print(" : ");
  Serial.println(c);
}
