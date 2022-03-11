#include<SoftwareSerial.h>
#include<Servo.h>

#define BITRAT 9600 // 비트레이트
#define MT_CTR 9 //전기모터 컨트롤(~표시가 있는 PWM을 지원하는 디지털 핀에 연결해야함)
#define BT_RXD 8 //블루투스 전송
#define BT_TXD 7 //블루투스 수신
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

void loop() {  // put your main code here, to run repeatedly:
  if(bluetooth.available() && valid == 0){Serial.write("BlueTooth is ready"); valid = 1;}
  if(Serial.available()){bluetooth.write(Serial.read());}
  phoneChar = (char)bluetooth.read();

  if(valid == 1){
    Serial.write(phoneChar);//모니터 화면에 출력
    if(phoneChar == 'a')        { angle += 30; }
    else if(phoneChar == 'b')   { angle -= 30; }
    else if(phoneChar == 'c')   { angle  = 30; valid = 0;}
    if(angle > 180)             { angle -= 30; }
    else if(angle < 0)          { angle += 30; }
    Serial.print(angle);
    if(angle != old_angle){
      bluetooth.print("Sent by aduino");
      bluetooth.println(angle); // 스마트폰으로 보내기
      old_angle = angle;
    }
    servo.write(angle);
  }
  delay(1000);
}
