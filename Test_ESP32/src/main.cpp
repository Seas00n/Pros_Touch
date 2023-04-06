#include <Arduino.h>
#include "servor.hpp"
#define LED 2

int interruptCounter = 0;
hw_timer_t *timer = NULL;
int deg = 0;
int delta = 1;

void IRAM_ATTR TimerEvent(){
  Serial.printf("InteruptCounter = %d\r\n",interruptCounter++);
  if(interruptCounter>5){
    interruptCounter = 1;
  }
}
void setup(){
    Serial.begin(115200);
    timer = timerBegin(0,80,true);
    timerAttachInterrupt(timer, &TimerEvent, true);
    timerAlarmWrite(timer, 1000000, true); 
    timerAlarmEnable(timer);
    pinMode(LED,OUTPUT);
    Servor_Init(1, 13);  
}
void loop(){
  // digitalWrite(LED, HIGH);
  // delay(10);
  // digitalWrite(LED, LOW);
  delay(5);
  Server_Control_Position(deg);
  if(deg==180){
    delta = -1;
  }else if (deg==0){
    delta = 1;
  }
  deg+=delta;
}