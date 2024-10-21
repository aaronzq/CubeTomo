  #include "Room.h"
  
  
  Room::Room(int n, float (*locations)[2], int rid, const unsigned short* mD){

    roomID = rid;
    n_locations = (n<10)?n:10;
    for (int i=0; i<n_locations; i++){
      available_locations[i][0] = locations[i][0];
      available_locations[i][1] = locations[i][1];
    }
    mapData = mD;

  }
  
  // Function to find the index of the closest available location to given coordinates
  int Room::findClosestLocation(float x, float y) const {
      int closestIndex = 0;
      double minDistance = sqrt(pow(available_locations[0][0] - x, 2) + 
                                      pow(available_locations[0][1] - y, 2));

      for (int i = 1; i < 4; ++i) {
          double distance = sqrt(pow(available_locations[i][0] - x, 2) + 
                                      pow(available_locations[i][1] - y, 2));
          if (distance < minDistance) {
              minDistance = distance;
              closestIndex = i; // Update the closest index
          }
      }
      
      return closestIndex; // Return the index of the closest location
  }
