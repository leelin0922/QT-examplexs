#include "backlight.h"
#include "ui_backlight.h"
#include <fcntl.h>
#include <stdio.h>
//#include <qpushbutton.h>
#include <sys/types.h>
#include <unistd.h>
#include <QDebug>

#define COMMAND_LINE       "/proc/cmdline"
#define MAX_BRIGHTNESS0    "/sys/class/backlight/pwm-backlight.0/max_brightness"
#define CUR_BRIGHTNESS0    "/sys/class/backlight/pwm-backlight.0/brightness"
#define MAX_BRIGHTNESS1    "/sys/class/backlight/pwm-backlight.1/max_brightness"
#define CUR_BRIGHTNESS1    "/sys/class/backlight/pwm-backlight.1/brightness"

Backlight::Backlight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Backlight)
{
    char * cmdline_finder;
    ui->setupUi(this);
    connect(ui->slider,SIGNAL(valueChanged(int)),this,SLOT(sliderchanged(int)));
    pwm_chno=1;

    fd = ::open(COMMAND_LINE,O_RDONLY|O_NONBLOCK);
    if(fd>=0)
    {
        char buf[512];
        memset(buf, 0, sizeof(buf));
        ::read(fd, buf, sizeof(buf));
        ::close(fd);

        cmdline_finder=strstr(buf,"sin0");
        if(cmdline_finder!=NULL)
            pwm_chno=0;
        qDebug() << COMMAND_LINE << " : " << pwm_chno;
    }

    if(pwm_chno==0)
    {
        system("cat /etc/brightness > /sys/class/backlight/pwm-backlight.0/brightness");
        fd = ::open(MAX_BRIGHTNESS0,O_RDONLY|O_NONBLOCK);
    }
    else
    {
        system("cat /etc/brightness > /sys/class/backlight/pwm-backlight.1/brightness");
        fd = ::open(MAX_BRIGHTNESS1,O_RDONLY|O_NONBLOCK);
    }
    if(fd>=0)
    {
        char buf[16];
        memset(buf, 0, sizeof(buf));
        ::read(fd, buf, 6);
        ::close(fd);

        int value=atoi(buf);
        ui->slider->setRange(1,value);
        if(pwm_chno==0)
            qDebug() << MAX_BRIGHTNESS0 << " : " << value;
        else
            qDebug() << MAX_BRIGHTNESS1 << " : " << value;
        ui->label_2->setText(buf);
    }
    else
    {
        if(pwm_chno==0)
            qDebug() << MAX_BRIGHTNESS0 << " Open failed !!!";
        else
            qDebug() << MAX_BRIGHTNESS1 << " Open failed !!!";
    }

    if(pwm_chno==0)
    {
        fd = ::open(CUR_BRIGHTNESS0,O_RDWR|O_NONBLOCK);
    }
    else
    {
        fd = ::open(CUR_BRIGHTNESS1,O_RDWR|O_NONBLOCK);
    }
    if(fd>=0)
    {
        char buf[16];
        memset(buf, 0, sizeof(buf));
        ::read(fd, buf, 6);

        int value=atoi(buf);
        ui->slider->setValue(value);
        if(pwm_chno==0)
            qDebug() << CUR_BRIGHTNESS0 << " : " << value;
        else
            qDebug() << CUR_BRIGHTNESS1 << " : " << value;
        ui->label_3->setText(buf);
    }
    else
    {
        if(pwm_chno==0)
            qDebug() << CUR_BRIGHTNESS0 << " Open failed !!!";
        else
            qDebug() << CUR_BRIGHTNESS1 << " Open failed !!!";
    }
    ui->label->setText("1");
}

Backlight::~Backlight( )
{
    if(fd>=0)
    {
        ::close(fd);
        fd=-1;
    }
    delete ui;
}

void Backlight::sliderchanged(int v)
{
    char buf[20];
    memset(buf, 0, sizeof(buf));
    sprintf(buf,"%d",(int) v);
    ::write(fd,buf,strlen(buf));
    ui->label_3->setText(buf);
    if(pwm_chno==0)
        system("cat /sys/class/backlight/pwm-backlight.0/brightness > /etc/brightness");
    else
        system("cat /sys/class/backlight/pwm-backlight.1/brightness > /etc/brightness");
    system("sync");
    //qDebug() << (int)(v);
}

void Backlight::moveEvent(QMoveEvent *)
{   
    this->move(QPoint(0,0));
}

void Backlight::resizeEvent(QResizeEvent *)
{
    this->showMaximized();
}

