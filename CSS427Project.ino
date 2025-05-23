#include <Servo.h>
#define PINF       A1
#define PINB       A2
#define PINR       A3
#define PINL       A4
#define MOTION_PIN 10
#define STEER_PIN  11
const int DEADZONE = 20;


int f, b, r, l, sumX, sumY;


int motionPulse = 1500;
int steerPulse  = 1500;


Servo motionServo;
Servo steerServo;

void setup(){
  Serial.begin(9600);
  
  motionServo.attach(MOTION_PIN);
  steerServo.attach(STEER_PIN);

  
  motionServo.writeMicroseconds(motionPulse);
  steerServo.writeMicroseconds(steerPulse);
}

void loop(){
  
  f = analogRead(PINF);
  b = analogRead(PINB);
  r = analogRead(PINR);
  l = analogRead(PINL);

  
  sumX = r - l;  if (abs(sumX) < DEADZONE) sumX = 0;
  sumY = f - b;  if (abs(sumY) < DEADZONE) sumY = 0;

  
  motionPulse = constrain(1500 + (sumY * 500.0) / 1023.0, 1000, 2000);
  steerPulse  = constrain(1500 + (sumX * 500.0) / 1023.0, 1000, 2000);

  
  motionServo.writeMicroseconds(motionPulse);
  steerServo.writeMicroseconds(steerPulse);

  
  Serial.print("SUMX: ");   Serial.print(sumX);
  Serial.print("  MOTION: "); Serial.print(motionPulse);
  Serial.print("  STEER: ");  Serial.println(steerPulse);

  
  //delay(50);
}
