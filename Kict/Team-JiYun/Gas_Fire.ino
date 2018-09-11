int sensorValue;
// 13번 핀을 LED로 지정합니다.
int ledPin = 7;
// 디지털 2번핀을 불꽃감지센서로 지정합니다.
int inputPin = 3;
// 불꽃 감지 센서의 상태를 저장합니다.(처음 상태를 LOW로 설정)
int pirState = LOW;
// 센서 값을 읽기 위해 변수를 선언합니다. 
int val = 0;   

void setup()
{
  // LED 를 출력으로 설정합니다.
  pinMode(ledPin, OUTPUT);      
  // 센서를 입력으로 설정합니다.
  pinMode(inputPin, INPUT);     
  Serial.begin(9600);      // sets the serial port to 9600
}

void loop()
{
  sensorValue = analogRead(0);       // read analog input pin 0
  Serial.println(sensorValue, DEC);  // prints the value read
  delay(1000);                        // wait 100ms for next reading

    val = digitalRead(inputPin);  
  // 만약 값이 HIGH 일때,
  if (val == HIGH, sensorValue > 600) {            
    // 13번 핀(보드에 내장되어 있는 LED) 를 켭니다.
    digitalWrite(ledPin, HIGH);  
    
    if (pirState == LOW) {
      // 센서의 상태가 LOW일때
      Serial.println("Beware of fire.");
      // 다음의 문구를 시리얼 모니터로 출력합니다.
      pirState = HIGH;
    }
    
  } else {
    // LED를 끕니다.
    digitalWrite(ledPin, LOW); 
    if (pirState == HIGH) {
      //센서값이 HIGH 일때 
      Serial.println("FIRE!!!!");
      // 다음의 문구를 시리얼 모니터로 출력합니다.
      pirState = LOW;
    }
  }
}
