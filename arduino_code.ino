// #include <Servo.h>
#include "Arm.h"

#define SIZE_A 151
#define SIZE_B 151
#define SIZE_C 100
#define SIZE_h 70

// Servo servoA; //min 0   max 171
// Servo servoB; //min 11 max 180
// Servo servoC; //min 0  max 171
// Servo servoR; //min 0 max 180

Arm myArm(SIZE_A, SIZE_B, SIZE_C, SIZE_h);


void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5);

  myArm.set_servo(5, 6, 7, 4);


  myArm.set_default_cords(150,150,100, 90);
  // myArm.set_position_by_angle(90, 90, 90, 90);
  // delay(1000);

  

  // myArm.cords_to_angle(302, 150, 150);
}


int i = 3;

void get_cord(){
  // Serial.read();
  int x = Serial.parseInt();
  
  // Serial.read();
  int y = Serial.parseInt();
  // Serial.read();
  int z = Serial.parseInt();
  int c = Serial.parseInt();

  Serial.print(" x:");Serial.print(x);Serial.print(" y:");Serial.print(y);Serial.print(" z:");Serial.print(z);
  Serial.print(" c:");Serial.print(c);Serial.print(" interval:");
  Serial.println(i);

  myArm.go_to_cord(x,y,z,c,i);
}
void loop(){
  if(Serial.available()){
    char key = Serial.read();
    Serial.print(key);

    if(key == 'x'){
      get_cord();
    }else if(key == 'i'){
      i = Serial.parseInt();
    }
  }
  // delay(1000);
  // myArm.go_to_cord(450,150,100,90,3);

  // delay(1000);
  // myArm.go_to_cord(150,150,100,90,3);

  // delay(1000); 
  // myArm.go_to_cord(350,100,200, 0,5);

  // delay(1000);
  // myArm.go_to_cord(400,50,100, 90,5);

}

