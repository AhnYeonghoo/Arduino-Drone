
/* 전역변수 선언
String A = "B";
int B = 1;
*/

/* 
 *  char ->  문자 
 *  String -> 문자의 배열 문자열
 *  int -> 정수형 4바이트
 *  float -> 실수형 
 *  double 
 *  
 */
 
/* 블루투스 모듈 라이브러리 가져오기 */
#include <SoftwareSerial.h>

/* 블루투스 모듈 설정 A0는 신호를 받아오는 것, A1은 신호를 전달해주는 것 */
SoftwareSerial BT(A0, A1);

void setup() {

  Serial.begin(9600);
  /* 블루투스 통신의 속도 설정 */
  BT.begin(9600);
  Serial.println("Start");
  
/*
  시리얼 모니터 사용하기 위해 셋업 
  Serial.begin(9600);
  /* pinMode(시리얼 번호, 출력) 
  pinMode(13, OUTPUT);  

  print하려면 Serial.print() 사용 
  Serial.println("hello");
  Serial.println(A);
  Serial.println(B);

  for문은 자바랑 똑같음 
  for(int i = 0; i < 10; i++) {
    delay(500); 1
    Serial.println("dk");
  }
*/
  
   
}

void loop() {


  /* digitalWrite(시리얼 번호, 신호) HIGH = 불 켜짐, LOW = 불 꺼짐 
  digitalWrite(13, HIGH);
  
    delay(mileSecond 단위로 쉬는 시간 부여)  1000 = 1초 
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
   */
   
  /* 입력 받는 함수는 Serial.read() */
  /* 조건문도 자바랑 똑같음  Serial.available() -> 입력이 들어왔을 때 true가 됨 */
  /*
  if(Serial.available()) {
    A = Serial.read();
    Serial.println(A);
  }
  */

  /* 입력이 있을 시 write()를 이용해 그 입력을 아두이노 블루투스 모듈에 신호 전달 */
  if (Serial.available()) {
    BT.write(Serial.read());
  }
  if (BT.available()) {
    Serial.write(BT.read());
  }
     
  
  
}
