#include "DynamixelMotor.h"
#include <Servo.h>

Servo myservo;
Servo myservo2;

int servoPin = 12;
int servoPin2 = 11;
int pos = 0;

// id of the motor
const uint8_t id1 = 1;
const uint8_t id2 = 2;
const uint8_t id3 = 3;
const uint8_t id4 = 4;
const uint8_t id5 = 5;
const uint8_t id6 = 6;

// motor speed
int16_t speed = 128;
int16_t speed2 = 64;

// communication baudrate
const long unsigned int baudrate = 1000000;

// hardware serial without tristate buffer
HardwareDynamixelInterface interface(Serial2);
HardwareDynamixelInterface interface1(Serial3);

DynamixelMotor motor1(interface1, id1);
DynamixelMotor motor2(interface, id2);
DynamixelMotor motor3(interface, id3);
DynamixelMotor motor4(interface1, id4);
DynamixelMotor motor5(interface1, id5);
DynamixelMotor motor6(interface1, id6);

// functions for converting angles
int x_old = 30;

float Angle2Analog(int x_old) {
  float tmp = map(x_old, -150, 150, 0, 300);

  return map(tmp, 0, 300, 0, 1023);
}


float Angle2Analog2(int x_old) {
  float tmp3 = map(x_old, 206.6, -93.4, 0, 300);

  return map(tmp3, 0, 300, 0, 1023);
}


float Angle2Analog3(int x_old) {
  float tmp = map(x_old, 150, -150, 0, 300);

  return map(tmp, 0, 300, 0, 1023);
}

float Angle2Analog4(int x_old) {
  float tmp = map(x_old, -14.8, 285.2, 0, 300);
  
  return map(tmp, 0, 300, 0, 1023);
}

void setup()
{
  Serial.begin(9600); // MATLAB
  Serial1.begin(115200); // Python
  interface.begin(baudrate);
  interface1.begin(baudrate);
  delay(100);

  uint8_t status = motor2.init();

  Serial.print(status);
  motor2.led(1);

  if (status != DYN_STATUS_OK)
  {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
  }

  motor1.enableTorque();
  motor2.enableTorque();
  motor3.enableTorque();
  motor4.enableTorque();
  motor5.enableTorque();
  motor6.enableTorque();

  // set to joint mode, with a 180° angle range
  // see robotis doc to compute angle values
  // motor.jointMode(204, 820);
  motor1.jointMode(0, 1023);
  motor1.speed(speed2);
  motor2.jointMode(0, 1023);
  motor2.speed(speed);
  motor3.jointMode(0, 1023);
  motor3.speed(speed);
  motor4.jointMode(0, 1023);
  motor4.speed(speed2);
  motor5.jointMode(0, 1023);
  motor5.speed(speed2);
  motor6.jointMode(0, 1023);
  motor6.speed(speed2);

  motor1.goalPosition(Angle2Analog(90));
  motor2.goalPosition(Angle2Analog(-90));
  motor3.goalPosition(Angle2Analog2(150));
  motor4.goalPosition(Angle2Analog(150));
  motor5.goalPosition(Angle2Analog3(0));
  motor6.goalPosition(Angle2Analog4(0));

  delay(1000);

  
  myservo.attach(servoPin); 
  myservo2.attach(servoPin2);

}


int i = 0;
String color;
float width;
int theta_int[8]={0};
int color_state = 0;
int ser_num = 0;
int color_num = 0;
int fin_num = 0;
int wait_num = 0;

void loop()
{

    while(Serial.available())
  {
    String inputStr = Serial.readStringUntil('\n');
   
    float th = inputStr.toFloat();
    
    if(i==6) color = inputStr;
    if(color=="red") color_state = 1;
    else if(color=="blue") color_state = 2;
    else if(color=="yellow") color_state = 3;
    if(i==7) width = th; 
    
    theta_int[i]=(int)th;
    i++;
    
  }


  delay(500);
  
    if(i>7)
    {

      myservo.write(150); // 초기 서보값
      myservo2.write(40);
      
      motor4.goalPosition(Angle2Analog(140));
      motor5.goalPosition(Angle2Analog3(80));
      delay(1500);
      motor1.goalPosition(Angle2Analog(theta_int[0]));
      motor2.goalPosition(Angle2Analog(theta_int[1]+4+5));
      motor3.goalPosition(Angle2Analog2(theta_int[2]+10));
      motor6.goalPosition(Angle2Analog4(theta_int[5]));
      delay(1500);
      motor4.goalPosition(Angle2Analog(theta_int[3]));
      delay(3000);
      motor5.goalPosition(Angle2Analog3(theta_int[4]));
      i=0;
      ser_num = 1;
      color_num = 1;
      delay(5000);
    }

 

  if(ser_num==1)
    {
      if(width>25) // 공 기준 너비 지정
      {
        myservo.write(105); //큰공 서보값
        myservo2.write(95); //큰공 서보값
      } 
    
      else
      {
        myservo.write(100); //작은공 서보값
        myservo2.write(100); //작은공 서보값
      }

      ser_num = 0;
      delay(2000);
      motor6.goalPosition(Angle2Analog4(180));
      delay(4000);
      motor2.goalPosition(Angle2Analog(theta_int[1]+4+5+5));
      delay(1000);
    }
    


  if(color_num==1)
  {
    if(color_state==1)
    {
      motor4.goalPosition(Angle2Analog(80));
      motor5.goalPosition(Angle2Analog3(80));
      delay(1500);
      motor1.goalPosition(Angle2Analog(-61));
      motor2.goalPosition(Angle2Analog(0));
      motor3.goalPosition(Angle2Analog2(45));
      motor6.goalPosition(Angle2Analog4(-61));
      delay(1500);
      motor4.goalPosition(Angle2Analog(-43));
      delay(1000);
      motor5.goalPosition(Angle2Analog3(0));
    }
  
    else if(color_state==2)
    {
      motor4.goalPosition(Angle2Analog(80));
      motor5.goalPosition(Angle2Analog3(80));
      delay(1500);
      motor1.goalPosition(Angle2Analog(-83));
      motor2.goalPosition(Angle2Analog(0));
      motor3.goalPosition(Angle2Analog2(45));
      motor6.goalPosition(Angle2Analog4(-84));
      delay(1500);
      motor4.goalPosition(Angle2Analog(-48));
      delay(1000);
      motor5.goalPosition(Angle2Analog3(0));
    }
  
    else if(color_state==3)
    {
      motor4.goalPosition(Angle2Analog(80));
      motor5.goalPosition(Angle2Analog3(80));
      delay(1500);
      motor1.goalPosition(Angle2Analog(-110));
      motor2.goalPosition(Angle2Analog(0));
      motor3.goalPosition(Angle2Analog2(45));
      motor6.goalPosition(Angle2Analog4(-110));
      delay(1500);
      motor4.goalPosition(Angle2Analog(-46));
      delay(1000);
      motor5.goalPosition(Angle2Analog3(0));
    }

    color_num = 0;
    fin_num = 1;
    delay (3000);
  
  }
  

    if(fin_num==1)
  {
    myservo.write(150); // 초기 서보값
    myservo2.write(40);
    fin_num = 0;
    delay(2000);
    wait_num = 1;
  }
  
  

  if(wait_num==1)
  {
   

    motor2.goalPosition(Angle2Analog(0));
    motor3.goalPosition(Angle2Analog2(90));
    motor4.goalPosition(Angle2Analog(90));
    motor5.goalPosition(Angle2Analog3(0));
    motor6.goalPosition(Angle2Analog4(0));
    delay(2000);
    motor1.goalPosition(Angle2Analog(90));
    delay(2000);
    motor3.goalPosition(Angle2Analog2(150));
    motor4.goalPosition(Angle2Analog(150));
    motor2.goalPosition(Angle2Analog(-90));
    delay(3000);
    Serial1.println("0");
    wait_num = 0;
  }
  

}
