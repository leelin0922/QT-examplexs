#include "parser.h"
#include <QDebug>

Parser::Parser(QObject *parent) :
    QThread(parent)
{
    prev_total = 0;
    prev_idle = 0;
    running = 1;
}

void Parser::run()
{
    //int nbytes;
    //int len;
    //struct can_frame frame;
    //struct sockaddr_can addr;
    //char buf[32];
    QProcess pProcess;
    QString p_stdout;
    QStringList list1;
    while(running !=0)
    {
        pProcess.start("sh", QStringList() << "-c" << "cat /proc/stat | head -n1 | sed 's/cpu //'");
        pProcess.waitForFinished(-1);

        p_stdout = pProcess.readAllStandardOutput();

        list1 = p_stdout.split(" ");

        //qDebug() << p_stdout;

        int user = list1[1].toInt();
        int system = list1[2].toInt();
        int nice = list1[3].toInt();
        int idle = list1[4].toInt();
        int wait = list1[5].toInt();
        int irq = list1[6].toInt();
        int srq = list1[7].toInt();
        int zero = list1[8].toInt();

        int total=( user + system + nice + idle + wait + irq + srq + zero);

        int diff_idle = idle-prev_idle;

        int diff_total = (total-prev_total);

        float cpuusage=((( 1000.0 * ( (diff_total - diff_idle)) / diff_total+5) ) / 10);

        emit parsercpuusageSignal(cpuusage);

        pProcess.start("sh", QStringList() << "-c" << "cat /sys/class/thermal/thermal_zone0/temp");
        pProcess.waitForFinished(-1);
        p_stdout = pProcess.readAllStandardOutput();
        //qDebug() << p_stdout;

        float cputemperature=1.0*p_stdout.toInt()/1000;
        emit parsercputemperatureSignal(cputemperature);

        prev_total = total;
        prev_idle = idle;
        if(running>0)
        {
            QTime pTimer;
            pTimer.start();
            while(pTimer.elapsed()<1000);
        }
        else
        {
            if(running<0)
                msleep(1000);
        }
    }
    qDebug() << "parse thread exit";
    pProcess.close();
}

void Parser::changestatus(int status)
{
    running = status;
}

void Parser::stop()
{
    running = 0;
}
