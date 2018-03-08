#include <AFMotor.h>
//#include <Servo.h>
//#include <Encoder.h>
#include "RollingAverage.cpp";
#include "PID.cpp";

struct EncVals {
  int pinA; int pinB;
  volatile long pos;
};
EncVals makeEnc(int pinA, int pinB){
  EncVals vals;
  vals.pinA = pinA;
  vals.pinB = pinB;
  vals.pos = 0;
  return vals;
}
//
//const float kP = 1;
//const float kI = 0;
//const float kD = 0;



EncVals enc_l = makeEnc(2,19);

AF_DCMotor motor_r (4);
AF_DCMotor motor_l (3);
//RollingAverage enc_r_avg(3);
//RollingAverage enc_l_avg(3);
//PID enc_PID(kP, kI, kD);

void setup() {
  Serial.begin(9600);
//  delay(100);
  motor_l.setSpeed(200);
//  motor_r.setSpeed(200);
  motor_l.run(RELEASE);
  
  pinMode(enc_l.pinA, INPUT);
  pinMode(enc_l.pinB, INPUT);
  
  Serial.println("swag");
//  motor_r.run(RELEASE);
  attachInterrupt(digitalPinToInterrupt(enc_l.pinA), doLeftEnc, CHANGE);
  
}
int c = 0;
float pid = 0;
void loop() {
  Serial.println(enc_l.pos);
//  enc_l_avg.add(getLeftDistance());
//  enc_r_avg.add(getRightDistance());
//  pid = enc_PID.get(enc_l_avg.median(), 10);
//  
//  Serial.print("Left: ");
//  Serial.print(enc_l_avg.median());
////  Serial.print(" Values: ");
////  for(int i = 0; i < 3; i++){
////    Serial.print(enc_l_avg.getNum(i));
////    Serial.print(", ");
////  }
//  Serial.print("Power: ");
//  Serial.print(pid);
//  Serial.println();
  setLeftSpeed(200);
  
}

void setRightSpeed(int s){
  if(s < 0){
    motor_r.run(FORWARD);
    motor_r.setSpeed(s * -1);
  } else if (s > 0) {
    motor_r.run(BACKWARD);
    motor_r.setSpeed(s);
  } else  {
    motor_r.setSpeed(0);
  }
}

void setLeftSpeed(int s){
    if(s < 0){
    motor_l.run(FORWARD);
    motor_l.setSpeed(s * -1);
    
  } else if (s > 0) {
    motor_l.run(BACKWARD);
    motor_l.setSpeed(s);
  } else  {
    motor_l.setSpeed(0);
  }
  
  Serial.println("Running");
}

//int getRightTicks() {
//  return -enc_l.read();
//}

void doLeftEnc(){
  if (digitalRead(enc_l.pinA) == digitalRead(enc_l.pinB)){
    enc_l.pos++;
  } else{
    enc_l.pos--;
  }
}
//int getLeftTicks() {
//  return enc_l.pos;
//}

//double getRightDistance(){
//  return 7 * 3.14159265358979323846 * getRightTicks() / 720.0;
//}

//double getLeftDistance(){
//  return 7 * 3.14159265358979323846 * getLeftTicks() / 720.0;
//}

//void resetLeftEnc(){
//  enc_l.pos = 0;
//}



//void resetRightEnc(){
//  enc_r.write(0);
//}

