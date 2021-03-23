#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int k = 54;
int pos_x = 0;
int thetha_r;
int thetha_l;

void setup() {
  // put your setup code here, to run once
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);
  
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(90);
}

void loop() {
  // put your main code here, to run repeatedly
  while(k<=162)
  {
    arm_mechanism();
  }
  k=54;
  for(pos_x=162;pos_x>=0;pos_x--)
  {
    servo1.write(pos_x);
    delay(10);
    servo3.write(pos_x);
    delay(10);
  }
  for(thetha_r=90,thetha_l=0;(thetha_r>=0)&(thetha_l<=90);thetha_r--,thetha_l++)
  {
    servo2.write(thetha_r);
    delay(10);
    servo4.write(thetha_l);
    delay(10);
  }
}
void arm_mechanism(){
    for(;pos_x<=k;pos_x++)
    {
      servo1.write(pos_x);
      delay(50);
      servo3.write(pos_x);
      delay(50);
    }
    if(k == 54 | k == 162)
    {
      for(thetha_r=0,thetha_l=90;(thetha_r<=90)&(thetha_l>=0);thetha_r++,thetha_l--)
      {
        servo2.write(thetha_r);
        delay(50);
        servo4.write(thetha_l);
        delay(50);
      }
    }

    else 
    {
      for(thetha_r=90,thetha_l=0;(thetha_r>=0)&(thetha_l<=90);thetha_r--,thetha_l++)
      {
        servo2.write(thetha_r);
        delay(50);
        servo4.write(thetha_l);
        delay(50);
      }
    }
    pos_x=k;
    k=k+54;
  }
