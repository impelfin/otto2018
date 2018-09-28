#include <RPLidar.h>
#include <math.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <SparkFun_ADXL345.h>




SoftwareSerial mySerial(10, 11);
RPLidar lidar;





#define RPLIDAR_MOTOR 5 // 라이다 모터

#define I2C_SLAVE_ADDR 7  // 첫 번째 초음파 모듈 I2C slave 주소
#define I2C_SLAVE_ADDR2 4  // 두 번째 초음파 모듈 I2C slave 주소
#define ULTRASONIC_NUM 3   // 초음파 모듈에 달린 초음파 센서의 개수
#define DEVICE (0x53) // 가속도 센서 디바이스 주소(?)


uint8_t distance[ULTRASONIC_NUM]; // 거리[초음파센서 번호]
byte _buff[6]; // 가속도 센서 데이터 버퍼
char POWER_CTL = 0x2D;  //Power Control Register
char DATA_FORMAT = 0x31;
char DATAX0 = 0x32; //X-Axis Data 0
char DATAX1 = 0x33; //X-Axis Data 1
char DATAY0 = 0x34; //Y-Axis Data 0
char DATAY1 = 0x35; //Y-Axis Data 1
char DATAZ0 = 0x36; //Z-Axis Data 0
char DATAZ1 = 0x37; //Z-Axis Data 1
int pi_command = 0;

void waitForResponse_pi() { // SoftwareSerial 통신 대기
  if(Serial.available()) {
    pi_command = Serial.parseInt();
  }
}

void readAccel() { // adxl345 data pull
  uint8_t howManyBytesToRead = 6;
  readFrom(DATAX0, howManyBytesToRead, _buff); //read the acceleration data from the ADXL345

                         // each axis reading comes in 10 bit resolution, ie 2 bytes.  Least Significat Byte first!!
                         // thus we are converting both bytes in to one int
  int x = (((int)_buff[1]) << 8) | _buff[0];
  int y = (((int)_buff[3]) << 8) | _buff[2];
  int z = (((int)_buff[5]) << 8) | _buff[4];
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" y: ");
  Serial.print(y);
  Serial.print(" z: ");
  Serial.println(z);
}

// Reads num bytes starting from address register on device in to _buff array
void readFrom(byte address, int num, byte _buff[]) {
  Wire.beginTransmission(DEVICE); // start transmission to device 
  Wire.write(address);             // sends address to read from
  Wire.endTransmission();         // end transmission

  Wire.beginTransmission(DEVICE); // start transmission to device
  Wire.requestFrom(DEVICE, num);    // request 6 bytes from device

  int i = 0;
  while (Wire.available())         // device may send less than requested (abnormal)
  {
    _buff[i] = Wire.read();    // receive a byte
    i++;
  }
  Wire.endTransmission();         // end transmission
}

void writeTo(byte address, byte val) {
  Wire.beginTransmission(DEVICE); // start transmission to device 
  Wire.write(address);             // send register address
  Wire.write(val);                 // send value to write
  Wire.endTransmission();         // end transmission
}

void Lidar_data_request() { // 라이다 데이터 받아오기
  rplidar_response_device_info_t info;
  if (IS_OK(lidar.getDeviceInfo(info, 100))) {

    //detected...
    lidar.startScan();

    analogWrite(RPLIDAR_MOTOR, 255);

    delay(1000);
    while (IS_OK(lidar.waitPoint())) {
      //perform data processing here...

      float distance = lidar.getCurrentPoint().distance;
      float angle = lidar.getCurrentPoint().angle;

      Serial.print("angle : ");
      Serial.print(angle);
      Serial.print(", distance : ");
      Serial.print(distance);
      Serial.print(", Xpos : ");
      Serial.print(distance*cos(angle*(3.14159265358979) / 180));
      Serial.print(", Ypos : ");
      Serial.println(distance*sin(angle*(3.14159265358979) / 180));
    }
  }
  else {
    delay(1000);
  }
}
void Sonic_data_request() {
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

    Serial.print(i + 3);
    Serial.print(" : ");
    Serial.print(distance[i]);
    Serial.println("");
  }
  Serial.println("ㅡㅡ");
  delay(500);
}
void setup()
{
  lidar.begin(Serial);
  pinMode(RPLIDAR_MOTOR, OUTPUT);


  Serial.begin(115200); // 파이와의 통신속도는 9600이 좋은거같은데
                         // 라이다의 통신 속도가 기본 115200임
  Wire.begin();

  writeTo(DATA_FORMAT, 0x01);
  writeTo(POWER_CTL, 0x08);
}
void loop()
{
  //Serial.read()로 읽은 문자, 문자열을 정확하게 보관할 방법이 필요함

  // 라이다 4, 초음파 2, 가속도 1 ex) 6 = 라이다 + 초음파
  switch (pi_command) {

  case 1:
      Serial.print("Raspberry Pi command : ");
    Serial.println(pi_command);
    readAccel();
    break;

  case 2:
      Serial.print("Raspberry Pi command : ");
    Serial.println(pi_command);
    Sonic_data_request();
    break;

  case 3:
      Serial.print("Raspberry Pi command : ");
    Serial.println(pi_command);
    Sonic_data_request();
    readAccel();
    break;

  case 4:
      Serial.print("Raspberry Pi command : ");
    Serial.println(pi_command);
    Lidar_data_request();
    break;

  case 5:
    break;

  case 6:
    break;

  case 7:
    break;

  default:
    waitForResponse_pi();
    break;


  }

  // Switch문으로
  // 라이다는 4, 초음파는 2, 가속도는 1
  // 7이면 모든 데이터를 전송하고, 6이면 라이다와 초음파의 데이터를 전송하는식으로
  // 라이다는 데이터를 모으고 보내는데에 있어서 CPU(?)를 독점해야하기때문에 그것 생각해야함
  // 얼마동안 모았다가 보낼지, 아니면 그 사이에 다른 센서 구동 및 데이터 요청코드를 끼워넣을 수 있을지



}
