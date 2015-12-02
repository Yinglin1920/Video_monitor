#ifndef THREAD_H
#define THREAD_H


#include <QImage>
#include <opencv/highgui.h>  //包含opencv库头文件
#include<linux/videodev2.h>

class cthread
{
public:
    cthread();
    ~cthread();

public:
    void create_thread();

};

#endif // THREAD_H
