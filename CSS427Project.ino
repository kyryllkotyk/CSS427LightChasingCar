// Ints for light sensors:
// Front, Back, Right, Left
// Each one is pointed in one direction, signaling how strong the light is in that direction

// If front & back are similar, stop
// If left & right are similar, stop
// If left/right & back/forward are similar, both forward and side can happen at once  || vector sums
// since the steering doesn't auto center, we must choose when to center the car again
// maybe a checker that verifies whether the given direction state is currently true?

// current state tracker that tells you where you're going now.
// desired direction tracker that tells you where the car wants to go
// check whether current state == desired direction

// Smaller priority but still should be done by the end:
// add deadzones to ignore small light difference
// add smoothing that would make sure the input is stable
// reset if stuck in state for a while
// speed adjustment based on turn vs straight line
#define PINF A1
#define PINB A2
#define PINR A3
#define PINL A4
#define MOTION_PIN 10
#define STEER_PIN 11
const int DEADZONE = 20;
int f, b, r, l, sumX, sumY, motionPulse, steerPulse;
unsigned long now, lastPulseSteer, lastPulseMotion;

//Sets the direction of the car based on readings from sensors
void setSums(){
  sumX = r - l;
  sumY = f - b;
  // if(abs(sumX) < DEADZONE){
  //   sumX = 0;
  // }
  // if(abs(sumY) < DEADZONE){
  //   sumY = 0;
  // }
}

void calculatePulse(){
  //sum can be between -1023 to 1023
  //pulse must be 1000 - 2000.
   
  motionPulse = 1500 + (sumY * 500) / 1023;
  steerPulse = 1500 + (sumX * 500) / 1023;
  motionPulse = constrain(motionPulse, 1000, 2000);
  steerPulse = constrain(steerPulse, 1000, 2000);
  
  Serial.print("MOTION PULSE: ");
  Serial.println(motionPulse);
  
  Serial.print("STEER PULSE: ");
  Serial.println(steerPulse);
  delay(1000);
}

void readSensors(){
  f = analogRead(PINF);
  b = analogRead(PINB);
  r = analogRead(PINR);
  l = analogRead(PINL);
  Serial.print(f);
  Serial.print("\t");
  Serial.print(b);
  Serial.print("\t");
  Serial.print(r);
  Serial.print("\t");
  Serial.println(l);
  delay(500);
}

void setup() {
  pinMode(MOTION_PIN, OUTPUT);
  pinMode(STEER_PIN, OUTPUT);
  f = 0;
  b = 0;
  r = 0;
  l = 0;
  motionPulse = 1500;
  steerPulse = 1500;
  lastPulseSteer = 0;
  lastPulseMotion = 0;
  Serial.begin(9600);
}

void loop() {
  // Get light reading
  readSensors();
  // Set sums from the readings
  setSums();

  // Checks whether the car is stuck, if not, calculates pulse
  //if(!isStuck()){
    // Calculates the pulse width
    calculatePulse();
  //}

  now = micros();

  if (now - lastPulseMotion >= 20000) {
    lastPulseMotion += 20000;
    digitalWrite(MOTION_PIN, HIGH);
    delayMicroseconds(motionPulse);
    digitalWrite(MOTION_PIN, LOW);
  }

  if (now - lastPulseSteer >= 20000) {
    lastPulseSteer += 20000;
    digitalWrite(STEER_PIN, HIGH);
    delayMicroseconds(steerPulse);
    digitalWrite(STEER_PIN, LOW);
  }

  // Check whether it's a similar sum as before
  //    IF TRUE: Get timer in seconds
  //    IF TRUE: Check whether the new timer is >1 minute over the previous
  //          IF TRUE: Reset State to default values
  //          IF TRUE: Reset Timer to 0
  
  //else{
  //    ELSE: setSpeed
  //    ELSE: Reset timer to 0
 // }
  
}
