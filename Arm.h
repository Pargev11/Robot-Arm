#ifndef ARM_H
#define ARM_H

#include <Arduino.h>
#include <Servo.h>
// #include <math.h>

class Arm{
  private:
    long size_A;
    long size_B;
    long size_C;
    long size_h;

    Servo servoA;
    Servo servoB;
    Servo servoR;
    Servo servoC;

  // current angles
    float current_A;
    float current_B;
    float current_C;
    float current_R;

  // current cordinates
    int curent_x;
    int curent_y;
    int curent_z;
    int curent_c;

    int delay_time = 2;

  public:
    Arm(int A,int B, int C, int h);
    void set_servo(int pin_A, int pin_B,int pin_C, int pin_R);
    void set_position_by_angle(float angle_A, float angle_B, float angle_C, float angle_R);
    void set_default_cords(int x, int y, int z, float c);
    void go_to_cord(int x, int y, int z, float c, int interval);
    

  private:
    void cords_to_angle(int x, int y, int z);
};


#endif