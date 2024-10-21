#include "mpu.h"
#include <Wire.h>

void mpuInit(Adafruit_MPU6050& mpu_){
  Wire.begin(6,1,400000);
  if (!mpu_.begin()) {
    Serial.print("Failed to find MPU6050 chip.");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu_.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu_.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu_.setGyroRange(MPU6050_RANGE_2000_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu_.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu_.setFilterBandwidth(MPU6050_BAND_44_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu_.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }
  Serial.println("");
  delay(100);
}

void mpuCalib(float *ax0, float *ay0, float *az0, float *gx0, float *gy0, float *gz0){

}

void mpuTest(Adafruit_MPU6050& mpu_){

  float ax,ay,az;


  sensors_event_t a, g, temp;
  mpu_.getEvent(&a, &g, &temp);

  ax = a.acceleration.x; ay = a.acceleration.y; az = a.acceleration.z;
  Serial.print("加速度 X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.println("");

}

void W_add_element(float arr[], int *size, float new_element)
{
  if (*size<windowSize){
    arr[*size] = new_element;
    (*size)++;
  }else{
    for (int i=1;i<windowSize;i++){
      arr[i-1]=arr[i];
    }
    arr[windowSize-1] = new_element;
  }
}

float W_sum(float arr[], int *size){
  if (*size==0){
    return 0.f;
  }else{
    float sum=0;
    for (int i=0;i<(*size);i++){
        sum+=arr[i];
    }
    return sum;
  }

}

void mpuRead(Adafruit_MPU6050& mpu_, float *ax, float *ay, float *az){
  sensors_event_t a, g, temp;
  mpu_.getEvent(&a, &g, &temp);
  *ax = a.acceleration.x; *ay = a.acceleration.y; *az = a.acceleration.z;
}


void MPU6050_test(Adafruit_MPU6050& mpu_)
{
  bool flag = 1;
  sensors_event_t a, g, temp;
  mpu_.getEvent(&a, &g, &temp);
  /* 打印出值 */
  Serial.print("加速度 X: ");
  Serial.print(a.acceleration.x);
  if(a.acceleration.x>=4.3 && flag == 0)
  {
    delay(50);
    if(a.acceleration.x>=4.3 && flag == 0)
    // active = TURN_RIGHT; //TURN_LEFT
    flag = 1;
  }
  else if(a.acceleration.x<=-2.2 && flag == 0)
  {
    delay(50);
    if(a.acceleration.x<=-2.2 && flag == 0)
    // active = TURN_LEFT; //TURN_RIGHT
    flag = 1;
  }
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  if(a.acceleration.y>=2.4 && flag == 0)
  {
    delay(50);
    if(a.acceleration.y>=2.4 && flag == 0)
    // active = DOWN;//DOWN
    flag = 1;
  }
  else if(a.acceleration.y<=-3.1 && flag == 0)
  {
    delay(50);
    if(a.acceleration.y<=-3.1 && flag == 0)
    // active = UP;//UP
    flag = 1;
  }
  // else if(!(a.acceleration.y<=-3.1 || a.acceleration.x>=4.3 ||a.acceleration.x<=-2.2 || a.acceleration.y>=2.4))
  // {
  //   delay(50);
  //   if(!(a.acceleration.y<=-3.1 || a.acceleration.x>=4.3 ||a.acceleration.x<=-2.2 || a.acceleration.y>=2.4))
  //   {
  //   flag = 0;
  //   active = UNKNOWN;
  //   }
  // }
  // Serial.print(", Z: ");
  // Serial.print(a.acceleration.z);
  
  // Serial.println(" m/s^2");
 
  // Serial.print("角度 X: ");
  // Serial.print(g.gyro.x);
  // Serial.print(", Y: ");
  // Serial.print(g.gyro.y);
  // Serial.print(", Z: ");
  // Serial.print(g.gyro.z);
  // Serial.println(" rad/s");
 
  // Serial.print("温度: ");
  // Serial.print(temp.temperature);
  // Serial.println(" degC");
 
  Serial.println("");
  delay(200);
}