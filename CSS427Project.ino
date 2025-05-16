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
const int DEADZONE = 20;
int f, b, r, l;
enum {
  MOTION_STOPPED,
  MOTION_FORWARD,
  MOTION_BACKWARD
} motion = MOTION_STOPPED;
enum {
  STEER_STRAIGHT,
  STEER_LEFT,
  STEER_RIGHT
} steer;

/*
struct for current and desired directions
typedef struct{
  
}
*/

void setDirection(){
  int sumX = r - l;
  int sumY = f - b;
  if(abs(sumX) < DEADZONE){
    sumX = 0;
  }
  if(abs(sumY) < DEADZONE){
    sumY = 0;
  }

  //Set the direction based on sums
    if(sumX > 0){
    steer = STEER_RIGHT;
  }
  else if(sumX < 0){
    steer = STEER_LEFT;
  }
  else{
    steer = STEER_STRAIGHT;
  }

  if(sumY > 0){
    motion = MOTION_FORWARD;
  }
  else if(sumY < 0){
    motion = MOTION_BACKWARD;
  }
  else{
    motion = MOTION_STOPPED;
  }
}

void setup() {
  fl = 0;
  fr = 0;
  bl = 0
  br = 0;
  steer = STEER_STRAIGHT;
  motion = MOTION_STOPPED;
}

void loop() {

}
