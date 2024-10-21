#ifndef ROOM_H
#define ROOM_H

#include "math.h"
#include <string>

class Room {

private:


public:

  Room(int n, float (*locations)[2], int rid, const unsigned short* mD);

  int n_locations;
  float available_locations[10][2];
  int roomID;
  const unsigned short* mapData;

  int findClosestLocation(float x, float y) const;

};

#endif