//#include <MsTimer2.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
char blue;
void waitForResponse() {
  delay(1000);
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  Serial.write("\n");
}

#define CAR_DIR_FW 0 //전진
#define CAR_DIR_BK 1 //후진
#define CAR_DIR_LF 2 //좌선회
#define CAR_DIR_RF 3 //우선회
#define CAR_DIR_ST 4 //정지






//sonic
#define trig1 26
#define echo1 27
#define trig2 28 
#define echo2 29 



//accel


int motor_speed_l = 0;
int motor_speed_r = 0;
int g_carDirection = CAR_DIR_ST;

// motor
#define MR_INT1 50 //Control pin 1 - Motor1
#define MR_EN1 2
#define MR_INT2 51 //Control pin 2 - Motor2
#define MR_EN2 3
#define MR_INT3 52 //Control pin 1 - Motor3
#define MR_EN3 4
#define MR_INT4 53 //Control pin 2 - Motor4
#define MR_EN4 5
void setup() {
  mySerial.begin(115200);
  Serial.println("Check Bluetooth LED blinking");
 pinMode(MR_INT1, OUTPUT);         // Motor 1 방향 설정 핀
 pinMode(MR_INT2, OUTPUT);         // Motor 2 방향 설정 핀
 pinMode(MR_INT3, OUTPUT);         // Motor 3 방향 설정 핀
  pinMode(MR_INT4, OUTPUT);        // Motor 4 방향 설정 핀

  pinMode(MR_EN1, OUTPUT);         // Motor 1 방향 설정 핀
 pinMode(MR_EN2, OUTPUT);         // Motor 2 방향 설정 핀
 pinMode(MR_EN3, OUTPUT);         // Motor 3 방향 설정 핀
  pinMode(MR_EN4, OUTPUT);        // Motor 4 방향 설정 핀
  Serial.begin(115200);


  pinMode(trig1, OUTPUT); //trig 1
  pinMode(echo1, INPUT); //echo  1
  pinMode(trig2, OUTPUT); //trig 2 
  pinMode(echo2, INPUT); //echo  2


}
//4   2
//3   1

// 1 전진, 2 오른쪽전진, 3 왼쪽전진, 4 정지, 5 후진, 6 오른쪽후진, 7 왼쪽후진
// 차량의 이동경로 기준
void loop() {  


if (mySerial.available()){
  
  blue=(char)mySerial.read();
  Serial.print("Recevied data : ");
  Serial.println(blue);

if ((blue=='1') || (blue=='2') || (blue=='3') || (blue=='4')) {
digitalWrite(MR_INT1, 0);
digitalWrite(MR_INT2, 0);
digitalWrite(MR_INT3, 0);
digitalWrite(MR_INT4, 0);

  if(blue=='1') {
    analogWrite(MR_EN1, 255);
    analogWrite(MR_EN2, 255);
    analogWrite(MR_EN3, 255);
    analogWrite(MR_EN4, 255);
  }
    if(blue=='2') {
    analogWrite(MR_EN1, 0);
    analogWrite(MR_EN2, 255);
    analogWrite(MR_EN3, 0);
    analogWrite(MR_EN4, 255);
  }
    if(blue=='3') {
    analogWrite(MR_EN1, 255);
    analogWrite(MR_EN2, 0);
    analogWrite(MR_EN3, 255);
    analogWrite(MR_EN4, 0);
  }
    if(blue=='4') {
    analogWrite(MR_EN1, 0);
    analogWrite(MR_EN2, 0);
    analogWrite(MR_EN3, 0);
    analogWrite(MR_EN4, 0);
  }
}

if ((blue=='5') || (blue=='6') || (blue=='7')) {
digitalWrite(MR_INT1, 1);
digitalWrite(MR_INT2, 1);
digitalWrite(MR_INT3, 1);
digitalWrite(MR_INT4, 1);


  if(blue=='5') {
    analogWrite(MR_EN1, 255);
    analogWrite(MR_EN2, 255);
    analogWrite(MR_EN3, 255);
    analogWrite(MR_EN4, 255);
  }
    if(blue=='6') {
    analogWrite(MR_EN1, 0);
    analogWrite(MR_EN2, 255);
    analogWrite(MR_EN3, 0);
    analogWrite(MR_EN4, 255);
  }
    if(blue=='7') {
    analogWrite(MR_EN1, 255);
    analogWrite(MR_EN2, 0);
    analogWrite(MR_EN3, 255);
    analogWrite(MR_EN4, 0);
  }
}
}
}
