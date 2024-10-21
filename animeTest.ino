#include "mpu.h"
#include <TFT_eSPI.h>
#include <math.h>
#include "livingroom.h"
#include "luca.h"
#include "Dog.h"
#include "Room.h"
#include "files.h"




#define frameTime 33

Adafruit_MPU6050 mpu;
float WX[windowSize];
float WY[windowSize];
int WXSize, WYSize;
MenuAction action;

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite bgSprite = TFT_eSprite(&tft);
TFT_eSprite dogSprite = TFT_eSprite(&tft);
TFT_eSprite txtSprite = TFT_eSprite(&tft);
int32_t jumpAniY;



// create the dog
float curr_pos[2] = { 60, 130 };
float targ_pos[2] = { 70, 140 };
int gestures_frames_n[2] = {7, 3};
char condition_string[BUFFER_SIZE];
Dog luca_the_dog(curr_pos, targ_pos, gestures_frames_n, 100, 100, 100, 0);

// create living room
float living_room_locations[4][2] = {
  { 60, 130 },
  { 70, 140 },
  { 145, 105 },
  { 140, 80 }
};
Room livingRoom(4, living_room_locations, 0, living240);


void draw(int32_t x, int32_t y, uint16_t frame, const uint16_t dog[][3600], const uint16_t *bg) {
  // tft.pushImage(0,0,240,240,living240);
  bgSprite.pushImage(0, 0, 240, 240, bg);
  dogSprite.pushImage(0, 0, 60, 60, dog[frame]);
  // dogSprite.pushSprite(60+x,130,TFT_BLACK);
  dogSprite.pushToSprite(&bgSprite, x, y, TFT_BLACK);
  bgSprite.pushSprite(0, 0);
}

void drawConditionMenu(){

  bgSprite.fillSprite(TFT_BLACK);

  txtSprite.fillSprite(TFT_BLACK);
  txtSprite.setCursor(0, 0, 4); 
  txtSprite.printf("Hunger:\n\rClean:\n\rHappy:\n\rAge:");
  txtSprite.pushToSprite(&bgSprite, 50, 70, TFT_BLACK);

  txtSprite.fillSprite(TFT_BLACK);
  txtSprite.setCursor(0, 0, 4); 
  txtSprite.printf("%d\n%d\n%d\n%d", luca_the_dog.getHunger(), luca_the_dog.getCleanliness(), luca_the_dog.getHappiness(), luca_the_dog.getAge());;
  txtSprite.pushToSprite(&bgSprite, 160, jumpAniY, TFT_BLACK);

  bgSprite.pushSprite(0,0);

  jumpAniY--;
  if(jumpAniY<67){
    jumpAniY=70;
  }
}

void setup() {

  Serial.begin(115200);  
  randomSeed(42);

  mpuInit(mpu);
  WXSize = 0;
  WYSize = 0;
  action = MenuAction::None;

 
  FSsetup();
  bool fileexists = LittleFS.exists("/data.txt");
  Serial.println(fileexists);
  if(!fileexists) {
    Serial.println("File does not exist");  
    Serial.println("Creating file...");
    // Create File and add header
    luca_the_dog.getConditions(condition_string);
    writeFile(LittleFS, "/data.txt", condition_string);
  }
  else {
    Serial.println("File already exists");

    // sprintf(condition_string, "%d,%d,%d,%d", 100, 100, 100, 0);
    // writeFile(LittleFS, "/data.txt", condition_string);

    readFile(LittleFS, "/data.txt", condition_string);
    luca_the_dog.setConditions(condition_string);
  }

  // Serial.println("Now we are here.");
  // luca_the_dog.getConditions(condition_string);
  // Serial.println(condition_string);


  tft.init();
  tft.setRotation(0);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);

  // tft.pushImage(0,0,240,240,living240);
  bgSprite.createSprite(240, 240);
  bgSprite.setSwapBytes(true);
  dogSprite.createSprite(60, 60);
  dogSprite.setSwapBytes(false);
  txtSprite.createSprite(240, 240);
  txtSprite.setTextColor(TFT_WHITE, TFT_BLACK);
  jumpAniY = 70;

  draw(60, 130, 0, luca, livingRoom.mapData);

}

void loop() {

  float ax, ay, az;
  mpuRead(mpu, &ax, &ay, &az);
  W_add_element(WX, &WXSize, ax);
  W_add_element(WY, &WYSize, ay);

  Serial.print("Acc: X: ");
  Serial.print(W_sum(WX, &WXSize));
  Serial.print(", Y: ");
  Serial.print(W_sum(WY, &WYSize));
  Serial.print(" ");
  
  if (W_sum(WX, &WXSize)>40){
    // action = MenuAction::Right;
    Serial.print("Right");
    WXSize=0;
  }
  if (W_sum(WX, &WXSize)<-40){
    // action = MenuAction::Left;
    Serial.print("Left");
    WXSize=0;
  }
  if (W_sum(WY, &WYSize)<-50){
    action = MenuAction::Up;
    Serial.print("Up");
    WYSize=0;
  }
  if (W_sum(WY, &WYSize)>70){
    if (action==MenuAction::Up){
      action = MenuAction::Down;
      Serial.print("Down");
      WYSize=0;
    }
  }
  Serial.print(" ");
  // mpuTest(mpu);


  const float* temp1 = luca_the_dog.getCurrentPosition();
  const float* temp2 = luca_the_dog.getTargetPosition();
  std::string temp3 = luca_the_dog.statusToString();
  bool temp4 = luca_the_dog.getOngoing();
  int temp5 = luca_the_dog.getFrameIdx();
  luca_the_dog.getConditions(condition_string);

  switch (action) {
    case MenuAction::None:
      Serial.printf(" %f, %f, %f, %f, %s, %d, %d, %s ", temp1[0],temp1[1],temp2[0],temp2[1],temp3.c_str(), temp4, temp5, condition_string);
      draw(int32_t(temp1[0]), int32_t(temp1[1]), int16_t(temp5), luca, livingRoom.mapData);
      luca_the_dog.selfDecide(livingRoom);
      luca_the_dog.step();
      break;
    case MenuAction::Up:
      drawConditionMenu();
      break;
    case MenuAction::Down:
      action = MenuAction::None;
      break;
    default:
      break;
  }
  Serial.println("");

  if(luca_the_dog.saving_flag){
    luca_the_dog.getConditions(condition_string);
    writeFile(LittleFS, "/data.txt", condition_string);
    luca_the_dog.saving_flag = false;
  }

  delay(frameTime);

}
