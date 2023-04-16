#include <Dynamixel2Arduino.h>
#include <SoftwareSerial.h>

  SoftwareSerial soft_serial(7, 8); // DYNAMIXELShield UART RX/TX
  #define DXL_SERIAL   Serial
  #define DEBUG_SERIAL soft_serial
  const uint8_t DXL_DIR_PIN = 2; // DYNAMIXEL Shield DIR PIN  
const uint8_t DXL_ID_1 = 1; //아래쪽 그리퍼 다이나믹셀 아이디
const uint8_t DXL_ID_2 = 2; //위쪽   그리퍼 다이나믹셀 아이디

const float DXL_PROTOCOL_VERSION = 2.0;


int init_val=0; //그리퍼 초기위치일때 모터각도



Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

using namespace ControlTableItem;

void setup() {
  dxl.begin(57600);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  dxl.ping(DXL_ID_1);
  dxl.ping(DXL_ID_2);

  dxl.torqueOff(DXL_ID_1);
  dxl.torqueOff(DXL_ID_1);
  dxl.setOperatingMode(DXL_ID_1, OP_CURRENT);
  dxl.setOperatingMode(DXL_ID_2, OP_CURRENT);
  dxl.torqueOn(DXL_ID_1);
  dxl.torqueOn(DXL_ID_2);
  //dxl.setGoalPosition(DXL_ID_1, 0);

  //init_val = dxl.readControlTableItem(PRESENT_POSITION, DXL_ID_1);
  dxl.ledOn(DXL_ID_1);
  dxl.ledOn(DXL_ID_2);
  delay(1000);
  dxl.ledOff(DXL_ID_1);
  dxl.ledOff(DXL_ID_2);
  delay(1000);
  
}

void loop() {
  //dxl.setGoalPWM(DXL_ID_1, 80, UNIT_PERCENT);
  //dxl.setGoalPWM(DXL_ID_2, 80, UNIT_PERCENT);

  dxl_mv(DXL_ID_1, 60, 99, 80);     //1번 (아래쪽 다이나믹셀) 닫기
  delay(5000);
  dxl_mv(DXL_ID_2, -80, -99, 90);   //2번 (위쪽 다이나믹셀) 닫기
  delay(5000);
  dxl_mv(DXL_ID_2, 60, 99, 80);     //2번 (위쪽 다이나믹셀) 열기
  delay(5000);
  dxl_mv(DXL_ID_1, -60, -99, 90);   //1번 (아래쪽 다이나믹셀) 열기
  delay(5000);

}


//dxl_mv(다이나믹셀 id, 목표전류(플마100%), 차단전류(플마100%), pwm리미트(100%))

void dxl_mv(int dxl_id, int dxl_cur_goal, int dxl_cur_lim, int dxl_pwm_lim)
{
  dxl.setGoalPWM(dxl_id, dxl_pwm_lim, UNIT_PERCENT);
  dxl.setGoalCurrent(dxl_id, dxl_cur_goal, UNIT_PERCENT);
  delay(150); //1000, 100, 50 //10은 안됨
  
  while(dxl.readControlTableItem(PRESENT_CURRENT, dxl_id)<=dxl_cur_lim) //25, 20, 15굳, 13 //10은 예민함
  {
    dxl.ledOn(dxl_id);
    dxl.setGoalCurrent(dxl_id, dxl_cur_goal, UNIT_PERCENT);
    delay(1);
  }
  
  dxl.torqueOff(dxl_id);
  dxl.ledOff(dxl_id);
  delay(100);
  dxl.ledOn(dxl_id);
  delay(100);
  dxl.ledOff(dxl_id);
  delay(100);
  dxl.ledOn(dxl_id);
  delay(100);
  dxl.ledOff(dxl_id);
  dxl.torqueOn(dxl_id);
  
}
