#include "com_mode.h"
#include "ui_com_mode.h"
#include <QDebug>

#define    IOCTL_DEV_NAME   "/dev/com_mode"

#define TEST_RS232_CMD          66
#define TEST_RS485_CMD          67
#define TEST_RS422_CMD          68
#define TEST_LOOPBACK_CMD       69
#define TEST_READ_TYPE       	  70

Com_mode::Com_mode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Com_mode)
{
    ui->setupUi(this);
    fd = open( IOCTL_DEV_NAME, O_RDWR|O_NOCTTY|O_NDELAY);
    if (fd < 0)
    {
        qDebug() << IOCTL_DEV_NAME << " Open failed !!!";
    }
    else
    {
        qDebug() << IOCTL_DEV_NAME << " IOCTL_DEV_NAME pass";
    }
}

Com_mode::~Com_mode()
{
    if(fd>=0)
        ::close(fd);
    delete ui;
}

void Com_mode::on_pushButton_O_1_clicked()
{
    if(fd>=0)
    {
        char buf;

        qDebug() << TEST_RS232_CMD << " TEST_RS232_CMD";
        buf = TEST_RS232_CMD;
        ioctl(fd,buf,1);
    }
}

void Com_mode::on_pushButton_O_2_clicked()
{
    if(fd>=0)
    {
        char buf;

        qDebug() << TEST_RS422_CMD << " TEST_RS422_CMD";
        buf = TEST_RS422_CMD;
        ioctl(fd,buf,1);
    }
}

void Com_mode::on_pushButton_O_3_clicked()
{
    if(fd>=0)
    {
        char buf;

        qDebug() << TEST_RS485_CMD << " TEST_RS485_CMD";
        buf = TEST_RS485_CMD;
        ioctl(fd,buf,1);
    }
}

void Com_mode::on_pushButton_O_4_clicked()
{
    if(fd>=0)
    {
        char buf;

        qDebug() << TEST_LOOPBACK_CMD << " TEST_LOOPBACK_CMD";
        buf = TEST_LOOPBACK_CMD;
        ioctl(fd,buf,1);
    }
}

