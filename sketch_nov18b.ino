#include <SoftwareSerial.h>
SoftwareSerial BT(A0, A1);

#define OPERATION_STEP_0  0
#define OPERATION_STEP_1  1
#define OPERATION_STEP_2  2
#define OPERATION_STEP_3  3
#define OPERATION_STEP_4  4
#define OPERATION_STEP_5  5
#define OPERATION_STEP_6  6
#define OPERATION_STEP_7  7
#define OPERATION_STEP_8  8
#define OPERATION_STEP_90  90

String uartString = "";
unsigned int currentStep;
unsigned int oldStep;
unsigned char commandBit = 0xA1;
unsigned char rolling = 0x64;
unsigned char pitching = 0x64;
unsigned char yawing = 0x64;
unsigned char throttle = 0x50;
unsigned char operationBit = 0x01;
unsigned char checkSum = 0x46;


/* 요잉(수평 상태로 좌우 회전) */
void checkYawing() {
   if (!digitalRead(7)) {
    Serial.println("Press 7");
    yawing = 50;
 
  } else if (!digitalRead(8)) {
    Serial.println("Press 8");
    yawing = 150;
  } else {
    yawing = 100;
  }
  
}

/* 롤링(좌우 회전) 조정 함수 */ 
void checkRolling() {
  int analogRolling = analogRead(4);
  Serial.println(analogRead(4));
  if (analogRolling > 700) {
    rolling = 120;
  } else if (analogRolling < 300) {
    rolling = 80;
  } else {
    rolling = 100; //default 기본값
  }
}



/* 피치(전후진) 조정 함수 */
void checkPitching() {
  int analogPitching = analogRead(5);
  Serial.println(analogRead(5));
  if (analogPitching > 700) {
     pitching = 120;
  } else if (analogPitching < 300) {
     pitching = 80;
  } else {
    pitching = 100; // default 기본값 
  }
}



/* 스로틑 출력 조정 함수 */
void checkThrottle() {
  if (!digitalRead(5)) {
    Serial.println("Press 5");
    throttle += 20;
    if (throttle > 200) {
      throttle = 200;
    }
 
  } else if (!digitalRead(6)) {
    Serial.println("Press 6");
    throttle -= 20;
    if (throttle < 0) {
      throttle = 0;
    }
  }
}




/*
 * checkSum은 위에 모든 비트 더한 값이고
 * 2진수 두자리만 남겨야 하므로 & 비트연산자로 0x00FF 계산.
 */
void check_checkSum() {
  checkSum = commandBit + rolling + pitching + yawing + throttle + operationBit;
  checkSum = checkSum & 0x00FF; 
}

/*
 * 기체 조종하는 함수들이 들어있는 함수들 
 */
void sendCommand() {
        checkRolling();
        checkThrottle();
        checkYawing();
        checkPitching();
        check_checkSum();
        
        BT.print("AT+WRITEH000D");   //앞으로 블루투스 통신시 16비트로 보내겠다


        if (rolling < 0x10) {
          BT.print("0"+String(rolling,HEX)); //CheckSum -> 위에서 다 합친 값이랑 실제로 전달받은 값이 일치하는 지 체크.        
        } else {
          BT.print(rolling,HEX);
        }

          
        if (pitching < 0x10) {
          BT.print("0"+String(pitching,HEX)); //CheckSum -> 위에서 다 합친 값이랑 실제로 전달받은 값이 일치하는 지 체크.        
        } else {
          BT.print(pitching,HEX);
        }


        if (yawing < 0x10) {
          BT.print("0"+String(yawing,HEX));
        } else {
          BT.print(yawing,HEX);
        } 
        
        if (throttle < 0x10) {
          BT.print("0"+String(throttle,HEX));
        } else {
          BT.print(throttle,HEX);
        } 
        
        BT.print("F0");//startBit -> 고정된 값
        BT.print(String(commandBit, HEX)); //commandBit -> 고정된 값 
        BT.print(String(rolling, HEX)); //Rolling(0~200까지의 범위 100일 때는 수평) -> 좌우 회전
        BT.print(String(pitching, HEX)); //Pitching(0~200까지의 범위 100일 때는 수평) -> 전진 후진
        BT.print(String(yawing, HEX)); //Yawing (0~200까지의 범위 100일 때는 수평) -> 수평 상태에서 좌회전, 우회전       
        BT.print(String(throttle,HEX)); //Throttle (0~200) 기체의 높이 상승하강           
        BT.print("0"+String(operationBit,HEX)); //OperationBit -> 1과 5만 존재, 1은 높이를 수동으로 조정, 5는 자동으로 조정하겠다는 뜻

                    
        if (checkSum < 0x10) {
          BT.print("0"+String(checkSum,HEX)); //CheckSum -> 위에서 다 합친 값이랑 실제로 전달받은 값이 일치하는 지 체크.        
        } else {
          BT.print(checkSum,HEX);
        }
        
       
        BT.print("\r"); // 캐리지 리턴 -> 신호 보냄
        delay(100);
       
}


void checkNextStep() {
  delay(300);
  uartString = "";
  oldStep = currentStep;
  currentStep = OPERATION_STEP_90;
}

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  for(int i = 5; i < 11; i++) {
    pinMode(i,INPUT);
    digitalWrite(i,HIGH);
  }
  
  currentStep = 0;
}

void loop() {
  
  switch(currentStep) {
    case OPERATION_STEP_0:
      Serial.println("Bluetooth Connect/Disconnect Test");
      currentStep++;
      break;
      
    case OPERATION_STEP_1:
      if(!digitalRead(9)) {
        Serial.println("Pressed Connect Button");
        BT.print("atd");
        BT.print("083A5C1F0001");
        BT.print("\r");
        checkNextStep();
      }
      break;
      
    case OPERATION_STEP_2:
      if(uartString.equals("\r\nOK\r\n")) {
        Serial.println("Received OK");
        checkNextStep();
      }
      break;
      
    case OPERATION_STEP_3:
      if(uartString.startsWith("\r\nCONNECT ")) {
        Serial.println("Received CONNECT");
        delay(300);
        uartString = "";
        currentStep++;
      }
      break;
      /* 블루투스 연결 후 진행되는 스텝 여기서 10번 클릭 시 해제 */
      
    case OPERATION_STEP_4:
      sendCommand();
      
      if(BT.available()) {
        BT.read();
      }
      
      if(!digitalRead(10)) {
        Serial.println("Pressed Disconnect Button");
        BT.flush();
        while(BT.available()) {
          BT.read();
        }
        BT.print("ath");
        BT.print("\r");
        checkNextStep();
      }
      break;
      
    case OPERATION_STEP_5:
      if(uartString.equals("\r\nOK\r\n")) {
        Serial.println("Received OK");
        checkNextStep();
      }
      break;
      
    case OPERATION_STEP_6:
      if(uartString.startsWith("\r\nDISCONNECT")) {
        Serial.println("Recieved DISCONNECT");
        checkNextStep();
      }
      break;
      
    case OPERATION_STEP_7:
      if(uartString.startsWith("\r\nREADY")) {
        Serial.println("Recieved READY");
        delay(300);
        uartString = "";
        currentStep = OPERATION_STEP_0;
      }
      break;
      
    case OPERATION_STEP_90:
      if(BT.available()) {
        char inChar = BT.read();
        uartString += inChar;

        if((uartString.length() > 4) && (uartString.startsWith("\r\n")) && (uartString.endsWith("\r\n"))) {
          currentStep = oldStep;
          currentStep++;
        }
      }
      break;
  }
}
