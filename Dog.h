#ifndef DOG_H
#define DOG_H

#include <string>
#include <stdio.h>
#include "Room.h"

#define ADAY 300

class Dog {
public:
    // Enum for dog's status
    enum class Status {
        Walk,
        Rest,
        None
    };

    struct Conditions {
      int hunger;      // Hunger level (0 to 100)
      int cleanliness; // Cleanliness level (0 to 100)
      int happiness;   // Happiness level (0 to 100)
      int age;         // Age in days

      void var2string(char *conditionstring){
        sprintf(conditionstring, "%d,%d,%d,%d", hunger, cleanliness, happiness, age);
      }
      void string2var(char *conditionstring){
        sscanf(conditionstring, "%d,%d,%d,%d", &hunger, &cleanliness, &happiness, &age);
      }

    };

private:
    float current_position[2];  // Array representing the Dog's current position (x, y)
    float target_position[2];   // Array representing the Dog's target position (x, y)
    Status status;                // Status of the Dog
    bool ongoing;                 // in an ongoing action
    unsigned int rest_timer;
    int gestures_frames[2];
    int gestures_idx;
    int frames_idx;
    Conditions conditions;
    int time_counter;

public:
    bool saving_flag;    

public:
    // Constructor
    Dog(float curr_pos[2], float targ_pos[2], int gests[2], int hun, int clean, int happy, int ag, Status stat = Status::None, bool ongo = false);

    // Setters for positions
    void setCurrentPosition(const float pos[2]);
    void setTargetPosition(const float pos[2]);

    // Getters for positions
    const float* getCurrentPosition() const;
    const float* getTargetPosition() const;

    // Setter for status
    void setStatus(Status stat);

    // Getter for status
    Status getStatus() const;

    // Convert status enum to string
    std::string statusToString() const;

    // Getter for ongoing
    bool getOngoing() const;
    
    int getFrameIdx() const;

    void getConditions(char *conditionstring);
    void setConditions(char *conditionstring);
    int getHunger();
    void setHunger(int hun);
    int getCleanliness();
    void setCleanliness(int clean);
    int getHappiness();
    void setHappiness(int happy);
    int getAge();
    void setAge(int ag);

    void step();
    void selfDecide(Room currentRoom);
};

#endif
