#include "runthread.h"
#include <QDebug>

Runthread::Runthread(QObject *parent) :
    QThread(parent)
{
    prev_total = 0;
    prev_idle = 0;
    running = -1;
}

void Runthread::run()
{
    int loop=0;
    while(running!=0)
    {
        loop++;
        if(loop>30000)
        {
            qDebug() << "running : " << running;
            loop=0;
        }
        if(running<=0)
        {
             if(running<0)
             {
                msleep(1000);
             }
        }
    }
    qDebug() << "Runthread thread exit";
}

void Runthread::stop()
{
    running = 0;
}

void Runthread::changestatus(int status)
{
    running = status;
}
