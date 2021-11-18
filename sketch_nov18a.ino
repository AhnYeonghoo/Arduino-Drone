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
#define OPERATION_STEP_9  9
#define OPERATION_STEP_10  10
#define OPERATION_STEP_11  11
#define OPERATION_STEP_12  12

String uartString = "";
unsigned int currentStep;

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
        BT.print("083a5c1f015b");
        BT.print("\r");
        delay(300);
        uartString = "";
        currentStep++;
      }
      break;
      
    case OPERATION_STEP_2:
      if(BT.available()) {
        char inChar = BT.read();
        uartString += inChar;
        
        if((uartString.length() > 4) && (uartString.startsWith("\r\n")) && (uartString.endsWith("\r\n"))) {
          currentStep++;
        }
      }
      break;
      
    case OPERATION_STEP_3:
      if(uartString.equals("\r\nOK\r\n")) {
        Serial.println("Received OK");
        delay(300);
        uartString = "";
        currentStep++;
      }
      break;
      
    case OPERATION_STEP_4:
      if(BT.available()) {
        char inChar = BT.read();
        uartString += inChar;

        if((uartString.length() > 4) && (uartString.startsWith("\r\n")) && (uartString.endsWith("\r\n"))) {
          currentStep++;
        }
      }
      break;
      
    case OPERATION_STEP_5:
      if(uartString.startsWith("\r\nCONNECT ")) {
        Serial.println("Received CONNECT");
        delay(300);
        uartString = "";
        currentStep++;
      }
      break;
      
    case OPERATION_STEP_6:
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
        delay(300);
        uartString = "";
        currentStep++;
      }
      break;
      
    case OPERATION_STEP_7:
      if(BT.available()) {
        char inChar = BT.read();
        uartString += inChar;
        
        if((uartString.length() > 4) && (uartString.startsWith("\r\n")) && (uartString.endsWith("\r\n") )) {
          currentStep++;
        }
      }
      break;
      
    case OPERATION_STEP_8:
      if(uartString.equals("\r\nOK\r\n")) {
        Serial.println("Received OK");
        delay(300);
        uartString = "";
        currentStep++;
      }
      break;
      
    case OPERATION_STEP_9:
      if(BT.available()) {
        char inChar = BT.read();
        uartString += inChar;

        if((uartString.length() > 4) && (uartString.startsWith("\r\n")) && (uartString.endsWith("\r\n"))) {
          currentStep++;
        }
      }
      break;
      
    case OPERATION_STEP_10:
      if(uartString.startsWith("\r\nDISCONNECT")) {
        Serial.println("Recieved DISCONNECT");
        delay(300);
        uartString = "";
        currentStep++;
      }
      break;
      
    case OPERATION_STEP_11:
      if(BT.available()) {
        char inChar = BT.read();
        uartString += inChar;
        
        if((uartString.length() > 4) && (uartString.startsWith("\r\n")) && (uartString.endsWith("\r\n") )) {
          currentStep++;
        }
      }
      break;
      
    case OPERATION_STEP_12:
      if(uartString.startsWith("\r\nREADY")) {
        Serial.println("Recieved READY");
        delay(300);
        uartString = "";
        currentStep = OPERATION_STEP_0;
      }
      break;
  }
}
