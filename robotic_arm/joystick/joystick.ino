#include <Servo.h>

Servo base;
Servo left;
Servo right;
Servo claw;

int joy1_x = A0;
int joy1_y = A1;
int joy2_x = A2;
int joy2_y = A3;

// Initial (center) positions of servos
int b = 90;
int l = 90;
int r = 90;
int c = 50;

// Joystick readings
int x1, y1, x2, y2;

void setup() {
  Serial.begin(9600);

  pinMode(joy1_x,INPUT);
  pinMode(joy1_y,INPUT);
  pinMode(joy2_x,INPUT);
  pinMode(joy2_y,INPUT);
  
  left.attach(3);
  right.attach(4);
  base.attach(2);
  claw.attach(5);

  // Center the servos
  left.write(l);
  right.write(r);
  base.write(b);
  claw.write(c);
}

void loop() {
  /////////////// Left /////////////////
  int x1 = analogRead(joy1_x);                      

  if (x1 < 200){
    if (l < 170) {
      left.write(++l);
      delay (15) ;
    }
  }
  
  if (x1 > 800){
    if (l > 10) {
      left.write(--l);
      delay(15); 
    } 
  }
  
  /////////////// Right /////////////////
  int y1 = analogRead(joy1_y);                      

  if (y1 < 200){
    if (r > 10) {
      right.write(--r); 
      delay(15); 
    }
  }
  
  if (y1 > 800){
    if (r < 170) {
      right.write(++r);
      delay (15) ;
    } 
  }

  /////////////// Base /////////////////
  int y2 = analogRead(joy2_y);                      

  if (y2 < 200){
    if (b > 10) {
      base.write(--b);
      delay(15); 
    }
  }
  
  if (y2 > 800){
    if (b < 170) {
      base.write(++b);
      delay (15) ;
    }
  }

  /////////////// Claw /////////////////
  int x2 = analogRead(joy2_x);                 

  if (x2 < 200){
    if (c < 90) {
      claw.write(++c);
      delay (15) ;
    } 
  }
  
  if (x2 > 800){
    if (c > 20) {
      claw.write(--c);
      delay(15); 
    }
  }
  
//  Serial.print(b);
//  Serial.print(" : ");
//  Serial.print(l);
//  Serial.print(" : ");
//  Serial.print(r);
//  Serial.print(" : ");
//  Serial.println(c);
}
