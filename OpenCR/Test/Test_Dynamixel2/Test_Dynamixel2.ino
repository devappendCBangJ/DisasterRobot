#include "DynamixelMotor.h"

//motor id 초기값
const uint8_t id1 = 6;

//속도 초기값(0 ~ 1023)
int16_t speed=512;

//통신 baudrate 초기값
const long unsigned int baudrate = 115200;

//hardware serial without tristate buffer
//see blink_led example, and adapt to your configuration
//통신 종류 설정
HardwareDynamixelInterface interface(Serial1);

//모터 통신 설정
DynamixelMotor motor1(interface, id1);

void setup(){
  //통신 시작
  Serial.begin(9600);
  
  interface.begin(baudrate);
  delay(100);

  //check if we can communicate with the motor
  //if not, we turn the led on and stop here
  //모터 시작
  uint8_t status=motor1.init();
  if(status!=DYN_STATUS_OK){
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println(status);
    Serial.println(DYN_STATUS_OK);
    while(1);
  }

  digitalWrite(LED_BUILTIN, LOW);

  //모터 토크 enable
  motor1.enableTorque();

  //set to joint mode, with a 180° angle range
  //see robotis doc to compute angle values
  //모터 설정
  motor1.jointMode(204, 820);
  motor1.speed(speed);
}

void loop(){
  //go to middle position
  motor1.goalPosition(512);
  delay(500);

  //move 45° CCW
  motor1.goalPosition(666);
  delay(500);

  //go to middle position
  motor1.goalPosition(512);
  delay(500);

  //move 45° CW
  motor1.goalPosition(358);
  delay(500);
}
