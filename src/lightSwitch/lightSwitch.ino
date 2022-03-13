#include<SoftwareSerial.h>
#include<Servo.h>

#define BITRAT 9600 // 비트레이트
#define MT_CTR 9 //전기모터 컨트롤(~표시가 있는 PWM을 지원하는 디지털 핀에 연결해야함)
#define BT_RXD 8 //블루투스 전송
#define BT_TXD 7 //블루투스 수신

#define TURN_RIGH 'a'
#define TURN_LEFT 'b'
#define TURN_OFF  'c' //종료
#define TURN_ON   's' //시작
#define ANGLE_OFFSET 20

SoftwareSerial bluetooth(BT_RXD, BT_TXD);
Servo servo;
int angle = 30;
int old_angle = 0;
int valid = 0;
char phoneChar;

void setup() {  // put your setup code here, to run once:
  Serial.begin(BITRAT);
  bluetooth.begin(BITRAT);
  servo.attach(MT_CTR);
  servo.write(angle);
}

void fn_validation(){// 모터 각도가 유효한 값인지 검사
  if(angle > 180)    { angle = 180; }
  else if(angle < 0) { angle = 0; }
}

void fn_res(String msg){// 스마트폰으로 보내기
  bluetooth.print("RES: ");
  bluetooth.println(msg);
}

void loop() {  // put your main code here, to run repeatedly:
  if(bluetooth.available() && valid == 0){
      Serial.write("BlueTooth is ready "); 
      phoneChar = (char)bluetooth.read();
      if(phoneChar == TURN_ON){ fn_res("OK"); valid = 1; }
  }
  
  if(Serial.available()){bluetooth.write(Serial.read());}
  
  phoneChar = (char)bluetooth.read();
  
  if(valid == 1){
    Serial.write(phoneChar);//모니터 화면에 출력
    if(phoneChar == TURN_RIGH)     { angle += ANGLE_OFFSET; }
    else if(phoneChar == TURN_LEFT){ angle -= ANGLE_OFFSET; }
    else if(phoneChar == TURN_OFF){ angle  = 30;  fn_res("OFF"); valid = 0;}
    fn_validation();
    
    if(angle != old_angle){
      fn_res(String(angle)); 
      old_angle = angle;
    }
    Serial.print(angle);
    servo.write(angle);
  }
  delay(1000);
}
