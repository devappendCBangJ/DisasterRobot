#include <DynamixelWorkbench.h>

#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif   

// Dynamixel target 초기화
#define BAUDRATE  1000000
#define DXL_ID    15

// Dynamixel 변수
uint8_t dxl_id;
uint16_t model_number;

// 잡기 변수
char rx_grip = '0';
bool gripped = 0;

DynamixelWorkbench dxl_wb;

void setup() {
  const char *log;
  bool result = false;

  // Dynamixel 초기화
  dxl_id = DXL_ID;
  model_number = 0;

  // Dynamixel 시작 + 확인
  result = dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to init");
  }
  else
  {
    Serial.print("Succeeded to init : ");
    Serial.println(BAUDRATE);  
  }

  // Dynamixel 통신 + 확인
  result = dxl_wb.ping(dxl_id, &model_number, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  else
  {
    Serial.println("Succeeded to ping");
    Serial.print("id : ");
    Serial.print(dxl_id);
    Serial.print(" model_number : ");
    Serial.println(model_number);
  }

  // Dynamixel Mode 변경 + 확인
  result = dxl_wb.jointMode(dxl_id, 0, 0, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to change joint mode");
  }
  else
  {
    Serial.println("Succeed to change joint mode");
    Serial.println("Dynamixel is moving...");

    dxl_wb.goalPosition(dxl_id, (int32_t)1023); // 벌리기

//    // Dynamixel 움직임 Test
//    for (int count = 0; count < 3; count++)
//    {
//      dxl_wb.goalPosition(dxl_id, (int32_t)0); // open
//      delay(1000);
//
//      dxl_wb.goalPosition(dxl_id, (int32_t)1023); // close
//      delay(1000);
//    }
  }

  // Serial 초기화
  Serial.begin(115200); // pc
  Serial1.begin(115200); // mbed
  Serial1.setTimeout(0);
}

void loop() {
  // mbed 통신 받기
  if(Serial1.available() > 0){
    rx_grip = Serial1.read();
  }
  Serial.println(rx_grip);
  
  // 통신 받으면, 잡기
  if(rx_grip == '1'){
    // Serial.println(rx_grip); // 확인용 코드
    dxl_wb.goalPosition(dxl_id, (int32_t)165); // 잡기
  }
  else if(rx_grip == '2'){
    // Serial.println(rx_grip); // 확인용 코드
    dxl_wb.goalPosition(dxl_id, (int32_t)1023); // 벌리기
  }
  else if(rx_grip == '3'){
    // Serial.println(rx_grip); // 확인용 코드
    dxl_wb.goalPosition(dxl_id, (int32_t)0); // 잡기
  }
}
