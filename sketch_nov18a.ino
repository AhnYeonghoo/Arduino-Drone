
/* 전역변수 선언
String A = "B";
int B = 1;
*/
/*
 * 버튼들은 digitalRead 사용
 * 조이스틱은 아날로그라서 analogRead 사용
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


/* 블루투스 모듈 설정 A0는 신호를 받아오는 것, A1은 신호를 전달해주는 것  */
SoftwareSerial BT(A0, A1);


void setup() {
  
  /* 조이스틱 쉴드 버튼들에 대한 핀 셋팅 
   *  5 -> 스로틀 업 
   *  6 -> 스로틀 다운
   *  7 -> 왼쪽 파워
   *  8 -> 오른쪽 파워
   *  9 -> Emergency(On)
   *  10 -> disconnect(Off)
   *  조이스틱은 아날로그 값임. 
   *  버튼들은 5~10까지의 디지털값 
   */
   Serial.begin(9600); 
   for (int i = 5; i < 11; i++) {
    pinMode(i, INPUT);
   }
 
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

/* 조이스틱 버튼 조작 함수 */
void displayPressButton() {
  for (int i = 5; i < 11; i++) {
    if (!digitalRead(i)) {
      Serial.print("Press ");
      Serial.println(i);
    }
  }
}

/* 조이스틱 조작 함수 */
void joysticPress() {
  Serial.print(analogRead(4));
  Serial.print(", ");
  Serial.println(analogRead(5));
}


/* 블루투스 연결 함수 */
void bluetoothOn() {
  if (!digitalRead(9)) {
    Serial.println("Bluetooth ON");
    BT.print("atd"); // atd는 연결을 시도하겠다.
    BT.print("083A5C1F0001"); // MAC Address 전송  
    BT.print("\r"); // 캐리지 리턴
  }
}

/* 블루투스 해제 함수 */
void bluetoothOff() {
   if (!digitalRead(10)) {
    Serial.println("Bluethooth OFF");  
    BT.print("ath"); // ath는 블루투스 연결 해제 요청
    BT.print("\r"); // 캐리지 리턴
  }
}

void loop() {
  /* --------------------------------------------------------- */
  /* 조이스틱 쉴드 입력 받아오는 것 
  button = digitalRead(5); // pinMode(5, INPUT)으로 받아온 조이스틱 쉴드 핀 번호를 읽어오는 것  
  */
  
  /* 파워에 대한 조작 
  for (int i = 5; i < 11; i++) {
    if (!digitalRead(i)) {
      Serial.print("Press ");
      Serial.println(i);
    }
  }
  */

  /* 블루투스 연결 함수 호출 */
  bluetoothOn();

  /* 블루투스 해제 함수 호출 */
  bluetoothOff();
  
 

  
  /* 스로틑 조작 함수 호출 
  displayPressButton();
 
  조이스틱 조작 함수 호출 
  joysticPress();
  */



  /* ------------------------------------------------ */
  /* 스토를 업 
  if (!digitalRead(5)) {
    Serial.println("Press 5");
  }
  
     스토를 다운
  if (!digitalRead(6)) {
    Serial.println("Press 6");
  }

     left power
  if (!digitalRead(7)) {
    Serial.println("Press 7");
  }

     right power 
  if (!digitalRead(8)) {
    Serial.println("Press 8");
  }

   Emergency(On) 
  if (!digitalRead(9)) {
    Serial.println("Press 9");
  }

   disConnect(Off) 
  if (!digitalRead(10)) {
    Serial.println("Press 10");
  }
  */
  
  /* ----------------------------------------------- */
  
    
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

/* --------------------------------------------------- */
  /* 입력이 있을 시 write()를 이용해 그 입력을 아두이노 블루투스 모듈에 신호 전달 
  if (Serial.available()) {
    BT.write(Serial.read());
  }
  if (BT.available()) {
    Serial.write(BT.read());
  }
  */
}
