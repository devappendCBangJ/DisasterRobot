#include <Dynamixel2Arduino.h>
#include <SoftwareSerial.h>

  SoftwareSerial soft_serial(7, 8); // DYNAMIXELShield UART RX/TX
  #define DXL_SERIAL   Serial
  #define DEBUG_SERIAL soft_serial
  const uint8_t DXL_DIR_PIN = 2; // DYNAMIXEL Shield DIR PIN  
const uint8_t DXL_ID = 2;
const float DXL_PROTOCOL_VERSION = 2.0;


int init_val=0; //그리퍼 초기위치일때 모터각도



Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

using namespace ControlTableItem;

void setup() {
  dxl.begin(57600);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  dxl.ping(DXL_ID);

  dxl.torqueOff(DXL_ID);
  dxl.setOperatingMode(DXL_ID, OP_CURRENT);
  dxl.torqueOn(DXL_ID);
  //dxl.setGoalPosition(DXL_ID, 0);

  //init_val = dxl.readControlTableItem(PRESENT_POSITION, DXL_ID);
  dxl.ledOn(DXL_ID);
  delay(1000);
  dxl.ledOff(DXL_ID);
  delay(1000);
  
}

void loop() {

  dxl.torqueOff(DXL_ID);
  dxl.setOperatingMode(DXL_ID, OP_CURRENT);
  dxl.torqueOn(DXL_ID);
  
  dxl.setGoalCurrent(DXL_ID, 50, UNIT_PERCENT);
  delay(40); //1000, 100, 50 //10은 안됨
  while(dxl.readControlTableItem(PRESENT_CURRENT, DXL_ID)<=25) //25, 20, 15굳, 13 //10은 예민함
  {
    dxl.ledOn(DXL_ID);
    dxl.setGoalCurrent(DXL_ID, 50, UNIT_PERCENT);
    delay(1);
  }
  dxl.torqueOff(DXL_ID);
  dxl.ledOff(DXL_ID);
  delay(100);
  dxl.ledOn(DXL_ID);
  delay(100);
  dxl.ledOff(DXL_ID);
  delay(100);
  dxl.ledOn(DXL_ID);
  delay(100);
  dxl.ledOff(DXL_ID);
  dxl.torqueOn(DXL_ID);
  delay(2000);

//  dxl.setGoalCurrent(DXL_ID, -50, UNIT_PERCENT);
//  delay(40); //1000, 100. 50
//  while(dxl.readControlTableItem(PRESENT_CURRENT, DXL_ID)>=-25) //25, 20, 15굳, 13 //10은 예민함
//  {
//    dxl.ledOn(DXL_ID);
//    dxl.setGoalCurrent(DXL_ID, -50, UNIT_PERCENT);
//    delay(5);
//  }
//  dxl.ledOff(DXL_ID);
//  dxl.torqueOff(DXL_ID);
//  delay(100);
//  dxl.ledOn(DXL_ID);
//  delay(100);
//  dxl.ledOff(DXL_ID);
//  delay(100);
//  dxl.ledOn(DXL_ID);
//  delay(100);
//  dxl.ledOff(DXL_ID);
//  dxl.torqueOn(DXL_ID);
//  delay(2000);

  dxl.torqueOff(DXL_ID);
  dxl.setOperatingMode(DXL_ID, OP_POSITION);
  dxl.torqueOn(DXL_ID);

  if(dxl.setGoalPosition(DXL_ID, init_val))
  {
    delay(2000);
  }

}
