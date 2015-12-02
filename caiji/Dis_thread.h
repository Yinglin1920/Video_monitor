#ifndef DIS_THREAD_H
#define DIS_THREAD_H
#include<QThread>


class Dis_thread : public QThread
{
    Q_OBJECT


public:
    Dis_thread();

signals:
    void dispaly();
//    void time(QString);

protected:
    void run();

};

#endif // DIS_THREAD_H
