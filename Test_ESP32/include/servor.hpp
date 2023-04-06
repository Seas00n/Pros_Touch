#ifndef SERVER_H
#define SERVER_H
#include <Arduino.h>
#include "math.h"
static int freq = 100;
static int resolution = 10;
static int servor_channel = 1;
static int servor_pin = 13;
static int servor_duty;
static float deadZone = 0.5;
static float maxZone = 2.5;
// 0.5/(1000/50)*(256)
static float deadZone_duty = deadZone*freq*(1<<resolution)/1000;
static float maxZone_duty = maxZone*freq*(1<<resolution)/1000;
static int min_position = 0;
static int max_position = 180;
void Servor_Init(uint8_t channel, uint8_t pin){
    ledcSetup(channel, freq, resolution);
    ledcAttachPin(servor_pin, channel);
    servor_channel = channel;
    servor_pin = pin;
}
int Deg_To_Duty(int degree){
    degree = min(max(degree, min_position),max_position);
    return (int)(((maxZone_duty-deadZone_duty)/(max_position-min_position))*degree+deadZone_duty);
}
void Server_Control_Position(int degree){
    printf("%d %d\r\n",degree,Deg_To_Duty(degree));
    ledcWrite(servor_channel, Deg_To_Duty(degree));
}
void Servor_Control_PWM(int duty){
    if(duty>maxZone_duty){   
        duty = (int)maxZone_duty;
    }else if(duty<deadZone_duty){
        duty = (int)deadZone_duty;
    }
    ledcWrite(servor_channel, duty);
}
#endif