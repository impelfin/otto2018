#include <RPLidar.h>
#include <math.h>
RPLidar lidar;

#define RPLIDAR_MOTOR 3
void setup() {
lidar.begin(Serial);
pinMode(RPLIDAR_MOTOR, OUTPUT);

}


int a=0;
void loop() {

rplidar_response_device_info_t info;
if(IS_OK(lidar.getDeviceInfo(info, 100))) {

//detected...
lidar.startScan();

analogWrite(RPLIDAR_MOTOR, 255);

delay(500);
while(IS_OK(lidar.waitPoint())) {
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


} else {
  delay(1000);
}


}
