#include <Servo.h>
#define PINF       A4
#define PINB       A3
#define PINR       A1
#define PINL       A2
#define MOTION_PIN 10
#define STEER_PIN  11
const float DEADZONE = 20;


float f, b, r, l, sumX, sumY;


float motionPulse = 1500;
float steerPulse  = 1500;


Servo motionServo;
Servo steerServo;

void setup(){
  Serial.begin(9600);
  
  motionServo.attach(MOTION_PIN);
  steerServo.attach(STEER_PIN);

  Serial.print("\nArduino initialized");

  // This 5 second delay is here to allow time for the car to see the "0-pulse". 
  // If this isn't here, the car won't respond to pulses as we expect.
  motionServo.writeMicroseconds(0);
  steerServo.writeMicroseconds(0);
  delay(5000);

  
  // motionServo.writeMicroseconds(motionPulse);
  // steerServo.writeMicroseconds(steerPulse);
}

void loop(){
  
  f = analogRead(PINF);
  b = analogRead(PINB);
  r = analogRead(PINR);
  l = analogRead(PINL);

  
  sumX = r - l;  if (abs(sumX) < DEADZONE) sumX = 0;
  sumX = sumX * -1;
  sumY = f - b;  if (abs(sumY) < DEADZONE) sumY = 0;

  
  motionPulse = constrain(1550.0 + (sumY * 500.0) / 1023.0, 1525, 1570);
  steerPulse  = constrain(1500 + (sumX * 1200.0) / 1023.0, 1100, 1900);

  motionServo.writeMicroseconds(motionPulse);
  steerServo.writeMicroseconds(steerPulse);

  // 
  // Forward motion [1565 (min), 2000 (max)]
  // Steering:
  // Left [1100 (min), 1500 (idle))
  // Right (1500 (idle), 1900 (max)]
  
  // motionServo.writeMicroseconds(1565);
  // steerServo.writeMicroseconds(1500);
  
  
  Serial.print("SUMX: ");   Serial.print(sumX);
  Serial.print("  SUMY: ");   Serial.print(sumY);
  Serial.print("  MOTION: "); Serial.print(motionPulse);
  Serial.print("  STEER: ");  Serial.println(steerPulse);
  Serial.print("     F"); Serial.print(f);
  Serial.print("     B"); Serial.print(b);
  Serial.print("     R"); Serial.print(r);
  Serial.print("     L"); Serial.print(l); Serial.print("           ");

  
  //delay(50);
}
