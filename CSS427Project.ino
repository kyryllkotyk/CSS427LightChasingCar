#include <Servo.h>
// Used pin definitions
const int PINF = A1;
const int PINB = A2;
const int PINR = A3;
const int PINL = A4;
const int MOTION_PIN = 10;
const int STEER_PIN = 11;

/*
* Deadzone measures if there's enough of a difference 
* in light from opposing directions to justify moving the car
*/
const int DEADZONE = 20;
// Servo timing definitions
const int MIN = 1000;
const int NEUTRAL = 1500;
const int MAX = 2000;
// Used to translate sensor values into servo pulse timing
const float SCALING = 500.0 / 1023.0;

/*
* Smoothing factor, set between 0 (maximum smoothing) and 1 (no smoothing)
* set number is the percentage (/100) that the new reading contributes 
* to the new value calculation.
* 0.2 = 20% new value 80% history
*/
const float ALPHA = 0.2;

// Forward, Backward, Right, Left, Sum on x-axis, Sum on y-axis
int f, b, r, l, sumX, sumY;
// sumX and sumY after smoothing has been applied
float filteredSumX;
float filteredSumY;

// Pulse timers
float motionPulse = NEUTRAL;
float steerPulse  = NEUTRAL;

/*
* Two separate servos, one used to move the car forward and backwards
* the other moves it right and left. Both act the same, but one uses degrees
*/
Servo motionServo;
Servo steerServo;



void setup(){  
  // Attaches pins to the corresponding servos
  motionServo.attach(MOTION_PIN);
  steerServo.attach(STEER_PIN);
  
  motionServo.writeMicroseconds((int)motionPulse);
  steerServo.writeMicroseconds((int)steerPulse);
}

void loop(){
  // Reads their respective timers
  f = analogRead(PINF);
  b = analogRead(PINB);
  r = analogRead(PINR);
  l = analogRead(PINL);

  // X-axis sum is the right light sensor's reading minus left's reading 
  sumX = r - l;  
  // If the sum is smaller than deadzone, the car should move straight
  if (abs(sumX) < DEADZONE) {
    sumX = 0;
  }
  
  // Y-axis sum is the forward light sensor's reading minus backward's reaidng
  sumY = f - b;
  // If the sum is smaller than deadzone, the car should be stopped
  if (abs(sumY) < DEADZONE) {
    sumY = 0;
  }
  
  // Calculates the new filtered sum based on weight of new and old readings
  filteredX = ALPHA * sumX + (1 - ALPHA) * filteredX;
  filteredY = ALPHA * sumY + (1 - ALPHA) * filteredY;

  /*
  * Convert the readings into pulse timing
  * Constrains to the set minimum and maximum value
  * to guarantee the pulse is always in scope of the car.
  */
  motionPulse = constrain(NEUTRAL + filteredY * SCALING, MIN, MAX);
  steerPulse  = constrain(NEUTRAL + filteredX * SCALING, MIN, MAX);

  // Writes the calculated pulse timing to the respective servo
  motionServo.writeMicroseconds((int)motionPulse);
  steerServo.writeMicroseconds((int)expasteerPulse);
}
