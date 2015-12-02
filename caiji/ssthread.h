#ifndef SSTHREAD_H
#define SSTHREAD_H

#define PIN_FLAME 0
#define PIN_SHAKE 2
#define PIN_SMOKE 3

#include <QThread>
#include <QMutex>
#include <wiringPi.h>
class ssThread : public QThread
{
    Q_OBJECT
public:
    ssThread();
signals:
    void SENSOR_ALEART(QString sensorName);
public slots:
    

private:
    bool Flame;
    bool Shake;
    bool Smoke;

    bool isEnd;
    void checkSensor();
    bool readSensor(int sensorPin);
    void aleart();

public:
    void run();
    void stop();

    QMutex mutex;
};

#endif // SSTHREAD_H
