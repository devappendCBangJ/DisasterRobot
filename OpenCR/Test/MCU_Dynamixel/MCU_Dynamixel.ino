char rx_grip = '0';
bool gripped = 0;

void setup() {
  Serial.begin(115200); // pc
  Serial1.begin(115200); // mbed
  Serial1.setTimeout(0);
}

void loop() {
  // mbed 통신 받기
  if(Serial1.available() > 0){
    rx_grip = Serial1.read();
  }

  // 통신 받으면, 잡기
  if(rx_grip == "1"){
    // Serial.println(rx_grip);  // 확인용 코드
    
    // 여기에 잡기 코드 넣어야됨
    // 잡으면, gripped = 1로 바꾸는 코드 넣어야됨
    gripped = 1;
  }
  
  // 잡았다면, 다 잡았다고 보냄
  if(gripped = 1){
    // Serial.print(String(gripped));    // 확인용 코드
    Serial1.print(char(gripped));
    
    rx_grip = '0';
    gripped = 0;
  }
}
