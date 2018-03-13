#include "backlight.h"
#include "ui_backlight.h"
#include <fcntl.h>
#include <stdio.h>
//#include <qpushbutton.h>
#include <sys/types.h>
#include <unistd.h>
#include <QDebug>

#define MAX_BRIGHTNESS    "/sys/class/backlight/pwm-backlight/max_brightness"
#define CUR_BRIGHTNESS    "/sys/class/backlight/pwm-backlight/brightness"

Backlight::Backlight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Backlight)
{
    ui->setupUi(this);
    connect(ui->slider,SIGNAL(valueChanged(int)),this,SLOT(sliderchanged(int)));

    fd = ::open(MAX_BRIGHTNESS,O_RDONLY|O_NONBLOCK);
    if(fd>=0)
    {
        char buf[16];
        memset(buf, 0, sizeof(buf));
        ::read(fd, buf, 6);

        int value=atoi(buf);
        ui->slider->setRange(1,value);
        ::close(fd);
        qDebug() << MAX_BRIGHTNESS << " : " << value;
        ui->label_2->setText(buf);
    }
    else
    {
        qDebug() << MAX_BRIGHTNESS << " Open failed !!!";
    }

    fd = ::open(CUR_BRIGHTNESS,O_RDWR|O_NONBLOCK);
    if(fd>=0)
    {
        char buf[16];
        memset(buf, 0, sizeof(buf));
        ::read(fd, buf, 6);

        int value=atoi(buf);
        ui->slider->setValue(value);
        qDebug() << CUR_BRIGHTNESS << " : " << value;
        ui->label_3->setText(buf);
    }
    else
    {
        qDebug() << CUR_BRIGHTNESS << " Open failed !!!";
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
    system("cat /sys/class/backlight/pwm-backlight/brightness > /etc/brightness");
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

