#include "myGpio.h"
#include "ui_myGpio.h"

#define    IOCTL_DEV_NAME   "/dev/gpio_mio" //leelin

#define GPIO_IN0_CMD_APLEX          66
#define GPIO_IN1_CMD_APLEX          67
#define GPIO_IN2_CMD_APLEX          68
#define GPIO_IN3_CMD_APLEX          69
#define GPIO_OUT0_CMD_APLEX         70
#define GPIO_OUT1_CMD_APLEX         71
#define GPIO_OUT2_CMD_APLEX         72
#define GPIO_OUT3_CMD_APLEX         73

#define IO_VAULE_H          1
#define IO_VAULE_L          0

MyGpio::MyGpio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyGpio)
{
    ui->setupUi(this);
    connect(&testTimer,SIGNAL(timeout()),this,SLOT(SotSetTime()));
    testTimer.start(10);
    io_out_1 = 1;
    io_out_2 = 1;
    io_out_3 = 1;
    io_out_4 = 1;
    io_in_1 = 0;
    io_in_2 = 0;
    io_in_3 = 0;
    io_in_4 = 0;

    fd = open( IOCTL_DEV_NAME, O_RDWR|O_NOCTTY|O_NDELAY);
    if (fd < 0)
        return;
}

MyGpio::~MyGpio()
{
    ::close(fd);
    delete ui;
}

void MyGpio::SotSetTime()
{
    char buf;

    buf = GPIO_IN0_CMD_APLEX;
    io_in_1 = ioctl(fd,buf,2);

    buf = GPIO_IN1_CMD_APLEX;
    io_in_2 = ioctl(fd,buf,2);

    buf = GPIO_IN2_CMD_APLEX;
    io_in_3 = ioctl(fd,buf,2);

    buf = GPIO_IN3_CMD_APLEX;
    io_in_4 = ioctl(fd,buf,2);

    if (io_in_1 == IO_VAULE_H)
        ui->label_I_1->setText("IO_IN_1_H");
    else if (io_in_1 == IO_VAULE_L)
        ui->label_I_1->setText("IO_IN_1_L");
    else
        ui->label_I_1->setText("IO_IN_1_E");

    if (io_in_2 == IO_VAULE_H)
        ui->label_I_2->setText("IO_IN_2_H");
    else if (io_in_2 == IO_VAULE_L)
        ui->label_I_2->setText("IO_IN_2_L");
    else
        ui->label_I_2->setText("IO_IN_2_E");

    if (io_in_3 == IO_VAULE_H)
        ui->label_I_3->setText("IO_IN_3_H");
    else if (io_in_3 == IO_VAULE_L)
        ui->label_I_3->setText("IO_IN_3_L");
    else
        ui->label_I_3->setText("IO_IN_3_E");

    if (io_in_4 == IO_VAULE_H)
        ui->label_I_4->setText("IO_IN_4_H");
    else if (io_in_4 == IO_VAULE_L)
        ui->label_I_4->setText("IO_IN_4_L");
    else
        ui->label_I_4->setText("IO_IN_4_E");
}

void MyGpio::on_pushButton_O_1_clicked()
{
    char buf;

    buf = GPIO_OUT0_CMD_APLEX;

    if ( io_out_1 == 1)
    {
        ioctl(fd,buf,io_out_1);
        ui->pushButton_O_1->setText("IO_OUT_1_H");
        io_out_1 = 0;
    }
    else
    {
        ioctl(fd,buf,io_out_1);
        ui->pushButton_O_1->setText("IO_OUT_1_L");
        io_out_1 = 1;
    }
}

void MyGpio::on_pushButton_O_2_clicked()
{
    char buf;

    buf = GPIO_OUT1_CMD_APLEX;

    if (io_out_2 == 1)
    {
        ioctl(fd, buf, io_out_2);
        ui->pushButton_O_2->setText("IO_OUT_2_H");
        io_out_2 = 0;
    }
    else
    {
        ioctl(fd,buf,io_out_2);
        ui->pushButton_O_2->setText("IO_OUT_2_L");
        io_out_2 = 1;
    }
}

void MyGpio::on_pushButton_O_3_clicked()
{
    char buf;

    buf = GPIO_OUT2_CMD_APLEX;

    if ( io_out_3 == 1)
    {
        ioctl(fd,buf,io_out_3);
        ui->pushButton_O_3->setText("IO_OUT_3_H");
        io_out_3 = 0;
    }
    else
    {
        ioctl(fd,buf,io_out_3);
        ui->pushButton_O_3->setText("IO_OUT_3_L");
        io_out_3 = 1;
    }
}

void MyGpio::on_pushButton_O_4_clicked()
{
    char buf;

    buf = GPIO_OUT3_CMD_APLEX;

    if ( io_out_4 == 1)
    {
        ioctl(fd,buf,io_out_4);
        ui->pushButton_O_4->setText("IO_OUT_4_H");
        io_out_4 = 0;
    }
    else
    {
        ioctl(fd,buf,io_out_4);
        ui->pushButton_O_4->setText("IO_OUT_4_L");
        io_out_4 = 1;
    }
}
