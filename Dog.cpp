#include "Dog.h"
#include "math.h"
#include <Arduino.h>

// Constructor
Dog::Dog(float curr_pos[2], float targ_pos[2], int gests[2], int hun, int clean, int happy, int ag, Status stat, bool ongo) : status(stat), ongoing(ongo) {
    setCurrentPosition(curr_pos);
    setTargetPosition(targ_pos);
    gestures_frames[0] = gests[0];
    gestures_frames[1] = gests[1];
    conditions.hunger = hun;
    conditions.cleanliness = clean;
    conditions.happiness = happy;
    conditions.age = ag;

    time_counter = 0;
    rest_timer = 0;
    frames_idx=0;
    gestures_idx=frames_idx;
    saving_flag = false;
}

// Setter for current position
void Dog::setCurrentPosition(const float pos[2]) {
    current_position[0] = pos[0];
    current_position[1] = pos[1];
}

// Setter for target position
void Dog::setTargetPosition(const float pos[2]) {
    target_position[0] = pos[0];
    target_position[1] = pos[1];
}

// Getter for current position
const float* Dog::getCurrentPosition() const {
    return current_position;
}

// Getter for target position
const float* Dog::getTargetPosition() const {
    return target_position;
}

// Setter for status
void Dog::setStatus(Status stat) {
    status = stat;
}

// Getter for status
Dog::Status Dog::getStatus() const {
    return status;
}

// Convert status enum to string
std::string Dog::statusToString() const {
    switch (status) {
        case Status::Walk: return "walking";
        case Status::Rest: return "resting";
        case Status::None: return "nothing";
        default:           return "unknown";
    }
}

bool Dog::getOngoing() const {
  return ongoing;
}

int Dog::getFrameIdx() const {
  return frames_idx;
}

void Dog::getConditions(char *conditionstring){
  conditions.var2string(conditionstring);
}

void Dog::setConditions(char *conditionstring){
  conditions.string2var(conditionstring);
}

int Dog::getHunger(){
  return conditions.hunger;
}

void Dog::setHunger(int hun){
  conditions.hunger = hun;
}

int Dog::getCleanliness(){
  return conditions.cleanliness;
}

void Dog::setCleanliness(int clean){
  conditions.cleanliness = clean;
}

int Dog::getHappiness(){
  return conditions.happiness;
}

void Dog::setHappiness(int happy){
  conditions.happiness = happy;
}

int Dog::getAge(){
  return conditions.age;
}

void Dog::setAge(int ag){
  conditions.age = ag;
}

void Dog::step(){
  gestures_idx++;
  if (time_counter<ADAY-1){
    time_counter++;
  }else{
    time_counter=0;
    saving_flag = true;
    conditions.hunger--;
    conditions.cleanliness--;
    conditions.happiness--;
    conditions.age++;
  }
  float dx = target_position[0]-current_position[0];
  float dy = target_position[1]-current_position[1];
  float l = sqrt(dx*dx+dy*dy);
  float nDist = round(l);
  switch (status){
    case Status::Walk:
      // Serial.printf("I am here \n");
      if (l<=1){
        setCurrentPosition(getTargetPosition());
        ongoing = false;
        setStatus(Status::None);
      }else{
        // Serial.printf("I am here here: %f \n",current_position[0]+dx/nDist);
        float temp[2] = {current_position[0]+dx/nDist, current_position[1]+dy/nDist};
        setCurrentPosition(temp);
        ongoing = true;
      }
      if(gestures_idx>=gestures_frames[0]){
        gestures_idx=0;
      }
      frames_idx = gestures_idx;
      break;
    case Status::Rest:
        if (rest_timer>0){
          rest_timer--;
          ongoing = true;
        }else{
          ongoing = false;
          setStatus(Status::None);
        }
        current_position[0] = current_position[0];
        current_position[1] = current_position[1];      
      if(gestures_idx>=gestures_frames[1]){
        gestures_idx=0;
      }
      frames_idx = gestures_frames[0] + gestures_idx;
      // Serial.printf("%d \n",gestures_idx);
      break;
    default:

      break;

  }
  
}

void Dog::selfDecide(Room currentRoom){
  if(!ongoing){
    int decision_rand = random(5);
    if (decision_rand<1){
        // start resting
        rest_timer = random(3,5)*30;
        setStatus(Status::Rest);
        
      }else{
      
        // start walking
        int current_index = currentRoom.findClosestLocation(current_position[0], current_position[1]);
        int temp_rand = random(2)*2-1;
        float pos[2];
        if(current_index==0){
          pos[0] = currentRoom.available_locations[1][0];
          pos[1] = currentRoom.available_locations[1][1];
        }else if(current_index < currentRoom.n_locations-1){
          pos[0] = currentRoom.available_locations[current_index+temp_rand][0];
          pos[1] = currentRoom.available_locations[current_index+temp_rand][1];
        }else{
          pos[0] = currentRoom.available_locations[currentRoom.n_locations-2][0];
          pos[1] = currentRoom.available_locations[currentRoom.n_locations-2][1];
        }
        setTargetPosition(pos);
        setStatus(Status::Walk);
    }
    gestures_idx=0;
    ongoing = true;

  }else{

  }

}

