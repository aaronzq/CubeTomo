#ifndef MPU_H
#define MPU_H


#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>


#define rad2deg 180/3.1415926
#define windowSize 15
// #define actionThreshold 5.0
// #define releaseThreshold 5.0
// #define pauseWindow 10
// // #define pauseWindow 10
// #define actionResetWindow 15
// #define numCalibration 25

enum class MenuAction {
  Left,
  Right,
  Up,
  Down,
  None
};

void mpuInit(Adafruit_MPU6050& mpu_);
void mpuCalib(float *ax0, float *ay0, float *az0, float *gx0, float *gy0, float *gz0);
void mpuTest(Adafruit_MPU6050& mpu_);
void W_add_element(float arr[], int *size, float new_element);
float W_sum(float arr[], int *size);
void mpuRead(Adafruit_MPU6050& mpu_, float *ax, float *ay, float *az);
void MPU6050_test(Adafruit_MPU6050& mpu_);

#endif