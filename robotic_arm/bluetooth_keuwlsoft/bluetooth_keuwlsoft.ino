#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial SerialBLE(10, 11); // RX, TX

int pad_x, pad_y; // Control pad values sent from Andorid device
char bluetoothData; // Received data

Servo base;
Servo left;
Servo right;
Servo claw;

// Initial (center) positions of servos
int b = 90;
int l = 90;
int r = 90;
int c = 50;

// Current value of pad
int val = 0;

void setup() {
  Serial.begin(9600);

  SerialBLE.begin(9600);  // Initialize Bluetooth commuication

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
  // Check Bluetooth for new Instructions
  if (SerialBLE.available()){
    bluetoothData=SerialBLE.read();
    
    ///////// Control Pad on Left /////////
    if(bluetoothData == '1') { // Claw open
      val = 1;
      Serial.println('1');
    }
    if(bluetoothData == '3') { // Claw close
      val = 3;
      Serial.println('3');
    }
    if(bluetoothData == '4') { // Base left
      val = 4;
      Serial.println('4');
    }
    if(bluetoothData == '2') { // Base right
      val = 2;
      Serial.println('2');
    }
    
    ///////// Control Pad on Right /////////
    if(bluetoothData == '5') { // Right forward
      val = 5;
      Serial.println('5');
    }
    if(bluetoothData == '7') { // Right backward
      val = 7;
      Serial.println('7');
    }
    if(bluetoothData == '8') { // Left backward
      val = 8;
      Serial.println('8');
    }
    if(bluetoothData == '6') { // Left forward
      val = 6;
      Serial.println('6');
    }
    
    if(bluetoothData == '0') { // Release
      val = 0;
      Serial.println('0');  
    }
  }
  
  if (val == 1) {
    if (c + 1 > 85) {} 
    else{ 
      claw.write(++c); 
      delay(15); 
    }  
  }
  if (val == 3) {
    if (c - 1 < 20) {} 
    else{ 
      claw.write(--c); 
      delay(15); 
    }  
  }
  if (val == 4) {
    if (b + 1 > 170) {} 
    else{ 
      base.write(++b); 
      delay(15); 
    }  
  }
  if (val == 2) {
    if (b - 1 < 10) {} 
    else{ 
      base.write(--b); 
      delay(15); 
    }  
  }
  
  if (val == 5) {
    if (r + 1 > 170) {} 
    else{ 
      right.write(++r); 
      delay(15); 
    }  
  }
  if (val == 7) {
    if (r - 1 < 10) {} 
    else{ 
      right.write(--r); 
      delay(15); 
    }  
  }
  if (val == 6) {
    if (l + 1 > 170) {} 
    else{ 
      left.write(++l); 
      delay(15); 
    }  
  }
  if (val == 8) {
    if (l - 1 < 10) {} 
    else{ 
      left.write(--l); 
      delay(15); 
    }  
  }
}
