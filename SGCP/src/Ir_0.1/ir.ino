
/*
  arduino ==> 라인트레이서를 아두이노를 활용해 구현한 코드
*/
 

 
/*
   아두이노의 PWM신호는 0 ~ 255의 해상도를 가집니다.
   예를들어 5v의 최대전압을 모터에 줄 수 있을 경우 최대속도가 된다면

   0(min)    :  0v, 모터 정지
   ...
   128         :  2.5v, 모터 중간속도
   ...
   255(max)  :  5v, 모터 최대속도
*/
 
 
 
//---------------------------------------------------------------
// 라인트레이서 적외선센서 5개의 값을 읽을 변수 a,b,c,d,e를 선언합니다
int a,b,c;
 
// 오른쪽 끝, 왼쪽 끝에 있는 적외선센서 값이 읽힐 경우 1이 되는 Flag를 선언합니다
int rightFlag = 0;
int leftFlag = 0;
 
// 적외선 센서를 편리하게 사용하기 위한 구조체 선언
// 구조체로 선언해서 사용하는 것이 여러개의 적외선센서 값을 읽는데 편리해서 사용합니다
struct SENSOR{
  union{
    int R;
    struct{
      int sensor1:1;
      int sensor2:1;
      int sensor3:1;
    }B;
  }sen;
};
 
// SENSOR의 구조체 이름을 tracesensor로 선언합니다
struct SENSOR tracesensor;
 

 
 
// motorController 객체를 생성합니다
// 맨 끝 파라미터 1,1은 각각 좌측, 우측모터의 최대속도(%) 입니다.
 
 
// 적외선 센서값을 읽어서 tracesensor 구조체 안에 저장하는 함수. 값을 읽을 경우 해당 위치에 1이 저장됩니다
void Sensing(){
  a=0;b=0;c=0;
 
  if(!digitalRead(2)){

    a = 1;
  }
  if(!digitalRead(5)){

    b = 1;
  }
  if(!digitalRead(3)){

    c = 1;
  }

 
  tracesensor.sen.B.sensor1 = a;
  tracesensor.sen.B.sensor2 = b;
  tracesensor.sen.B.sensor3 = c;
}
 
void setup() {
  // 시리얼모니터로 센서값이 제대로 읽히는지 확인하기 위해 (println함수로) 시리얼모니터를 사용한다고 선언
  Serial.begin(115200);
 
  // 아두이노와 적외선센서가 연결되는 핀들 선언
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
}
 
 
void loop() {
  // Sensing()함수를 호출해서 적외선센서값을 읽습니다
  Sensing();
 switch(tracesensor.sen.R){

  case 0b000:
  Serial.println("000");
  break;
    case 0b100:
  Serial.println("100");
  break;
    case 0b010:
  Serial.println("010");
  break;
      case 0b001:
  Serial.println("001");
  break;
      case 0b110:
  Serial.println("110");
  break;
        case 0b101:
  Serial.println("101");
  break;
        case 0b011:
  Serial.println("011");
  break;
        case 0b111:
  Serial.println("111");
  break;
    default:
      break;
  }
   delay(1000);
}
