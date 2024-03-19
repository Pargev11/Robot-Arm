#include "Arm.h"
// #include <math.h>

#define pi 3.141592653589793238463

Arm::Arm(int A,int B,int C, int h): size_A(A), size_B(B), size_C(C), size_h(h) {}

void Arm::set_servo(int pin_A, int pin_B, int pin_C, int pin_R)
{
  servoA.attach(pin_A);
  servoB.attach(pin_B);
  servoC.attach(pin_C);
  servoR.attach(pin_R);
}

void Arm::set_position_by_angle(float angle_A, float angle_B, float angle_C, float angle_R)
{
  angle_A = (angle_A + 9) * 1.05;
  angle_B = (angle_B - 11) * 1.04;
  angle_R = (180 - (angle_R-9)*1.1);
  angle_C = angle_C * 1.05;
  servoA.write(angle_A);
  servoB.write(angle_B); 
  servoC.write(angle_C); 
  servoR.write(angle_R);

}

float radian_to_degree(float num){
    num = num*180/pi;
    return num;
}
float degree_to_radian(float num){
    num = num * (pi/180);
    return num;
}
void Arm::cords_to_angle(int x, int y, int z)
{
  // Serial.print(x); Serial.print(" "); Serial.print(y); Serial.print(" "); Serial.println(z);
    z -= size_h;
  // find R servo angle
    float dist = sqrt(pow(y, 2) + pow(size_A + size_B - x, 2));
    // Serial.println(dist);
    if(dist > size_A+size_B) return;
    
    float tmp = y;
    current_R = radian_to_degree(asin(tmp/dist));
    if(x>size_A+size_B) current_R = 180 - current_R;
    Serial.println(current_R);

  // fined A and B servo angle
    y = z;
    float x_ = dist;

    if(curent_c <= 90){
        x_ = x_ - sin(degree_to_radian(curent_c)) * size_C;
        y = y + cos(degree_to_radian(curent_c)) * size_C;
    }else{
        
        x_ = x_ - cos(degree_to_radian(curent_c-90)) * size_C;
        y = y - sin(degree_to_radian(curent_c-90)) * size_C;
    }
    

    dist = sqrt(pow(x_,2) + pow(y, 2));

    // Serial.println('-');
    // Serial.println(dist);
    current_B = acos((pow(size_A,2)+pow(size_B,2)-pow(dist,2))/(2*size_A*size_B));
    

    current_A = radian_to_degree(asin(size_B*sin(current_B)/dist) + asin(y/dist));

    Serial.println(current_A);
    Serial.println(radian_to_degree(current_B));
    
  // find C servo angle
    current_C = curent_c + radian_to_degree(asin(size_B*sin(current_B)/dist) + asin(x_/dist)) - 90;
    current_B = radian_to_degree(current_B);
    Serial.println(current_C);
}

void Arm::set_default_cords(int x, int y, int z, float c){
  curent_x = x;
  curent_y = y;
  curent_z = z;
  curent_c = c;

  cords_to_angle(x,y,z);
  set_position_by_angle(current_A, current_B, current_C, current_R);
}

void Arm::go_to_cord(int x, int y, int z, float c, int m){
    int tmp_x;
    int tmp_y;
    int tmp_z;
    curent_c = c;

    int directionVector[3];
    directionVector[0] = x - curent_x;
    directionVector[1] = y - curent_y;
    directionVector[2] = z - curent_z;

    int dist = sqrt(pow(curent_x-x,2)+pow(curent_y-y,2)+pow(curent_z-z,2));
    if(dist == 0){
      cords_to_angle(x,y,z);
      set_position_by_angle(current_A, current_B, current_C, current_R);
      return;
    }
    int n = dist/m;
    
    // cout<<directionVector[0]<<" "<<directionVector[1]<<" "<<directionVector[2]<<" "<<n<<endl<<endl;

    for(int i = 0; i <= n; ++i){
        float t = (float)i / n;
        tmp_x = curent_x + directionVector[0]*t;
        tmp_y = curent_y + directionVector[1]*t;
        tmp_z = curent_z + directionVector[2]*t;

        cords_to_angle(tmp_x,tmp_y,tmp_z);
        set_position_by_angle(current_A, current_B, current_C, current_R);
        delayMicroseconds(delay_time);

        Serial.print(tmp_x); Serial.print(" "); Serial.print(tmp_y); Serial.print(" "); Serial.println(tmp_z);

    }
    curent_x = tmp_x;
    curent_y = tmp_y;
    curent_z = tmp_z;

}