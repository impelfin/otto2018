// 알칸도 초음파센서 모듈로 부터 받은 데이터 확인 (http://www.RSFTech.com) V2.0
// I2C 통신 : 모듈의 SDA, SCL은 아두이노 우노의 A4, A5핀과 연결
// 모듈의 VIN, GND, S/RST은 아두이노 우노의 5V, GND, RESET핀과 연결(RESET은 연결하지 않아도 무방)
// 시리얼 모니터(115200)에서 데이터 확인
// distance[ ] : 왼쪽/전방/오른쪽/별도(후방, '알칸도 초음파 센서모듈-2') 거리(Cm)

#include <Wire.h>
#define I2C_SLAVE_ADDR 7 
#define I2C_SLAVE_ADDR2 4  // >>>>> I2C 슬레이브 주소(초음파 센서모듈 주소)
#define ULTRASONIC_NUM 3          // >>>>> 초음파 센서를 하나 더 추가할 경우 4로 변경('알칸도 초음파 센서모듈-2') 

uint8_t distance[ULTRASONIC_NUM];

void setup() {
  Serial.begin(115200);
  Wire.begin(); 
  }

void loop() {
  Wire.requestFrom(I2C_SLAVE_ADDR, ULTRASONIC_NUM);    // 슬레이브로 부터 ULTRASONIC_NUM 바이트 데이터 요청
  for (int i = 0; i < ULTRASONIC_NUM; i++) {
    distance[i] = Wire.read();
    
    Serial.print(i);
    Serial.print(" : ");
    Serial.print(distance[i]);
    Serial.println("");
    }
    Wire.requestFrom(I2C_SLAVE_ADDR2, ULTRASONIC_NUM);    // 슬레이브로 부터 ULTRASONIC_NUM 바이트 데이터 요청
  for (int i = 0; i < ULTRASONIC_NUM; i++) {
    distance[i] = Wire.read();
    
    Serial.print(i+3);
    Serial.print(" : ");
    Serial.print(distance[i]);
    Serial.println("");
    }
    Serial.println("ㅡㅡ");
      delay(500);
}  

  
