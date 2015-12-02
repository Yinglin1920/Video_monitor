#include"Dis_thread.h"
#include<QtCore/QTime>


Dis_thread::Dis_thread()
{

}

void Dis_thread::run()
{
    while(1)
    {
        emit dispaly();
        msleep(150 );
    }
}
