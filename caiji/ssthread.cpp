#include "ssthread.h"
#include<QDebug>

ssThread::ssThread()
{
    Flame =false;
    Shake =false;
    Smoke = false;
    isEnd = false;
    wiringPiSetup();
}


void ssThread::checkSensor(){
    int res;
    res  = readSensor(PIN_FLAME);
    if (res == 0)
        Flame = true;
    res  = readSensor(PIN_SHAKE);
    if (res == 1)
        Shake =true;
    res  = readSensor(PIN_SMOKE);
    if (res == 1)
        Smoke =true;
}

bool ssThread::readSensor(int sensorPin){
    bool res = false;
    res = digitalRead(sensorPin);
    return res;
}

void ssThread::stop(){
    isEnd =true;
}

void ssThread::run(){
    mutex.lock();
    while(!isEnd){
        checkSensor();
        aleart();
        delay(200);
    }
    mutex.unlock();
}

void ssThread::aleart(){
    if(Flame){
        emit SENSOR_ALEART("FLAME");
        Flame = false;
    }
    if(Shake){
        emit SENSOR_ALEART("SHAKE");
        Shake = false;
    }
    if(Smoke){
        emit SENSOR_ALEART("SMOKE");
        Smoke = false;
    }
}
