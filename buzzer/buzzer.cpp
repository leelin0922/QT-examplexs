#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "buzzer.h"
#include "ui_buzzer.h"
#include <QMessageBox>

//#define PWM_IOCTL_SET_FREQ	1
//#define PWM_IOCTL_STOP		0
#define BUZZER_ENABLE   182
#define BUZZER_FREQENCY 183
#define BUZZER_DISABLE  184
#define    IOCTL_DEV_NAME   "/dev/pwm-buzzer"

Buzzer::Buzzer(QWidget *parent) :
	QWidget(parent),
    ui(new Ui::Buzzer)
{
    ui->setupUi(this);
    ui->slider->setRange(1,8000);
    ui->slider->setValue(4000);
    fd = open(IOCTL_DEV_NAME, O_RDWR|O_NOCTTY|O_NDELAY);
    if (fd < 0) {
        perror("open buzzer device");
        exit(1);
    }
    ioctl(fd, BUZZER_DISABLE,0);
    //set_buzzer_freq(5000);
}

Buzzer::~Buzzer()
{
    if(fd>=0)
    {
        ioctl(fd, BUZZER_DISABLE,0);
        ::close(fd);
    }
	delete ui;
}

void Buzzer::set_buzzer_freq(int freq)
{
    int ret = ioctl(fd, BUZZER_FREQENCY, freq);
    if(ret < 0){
        perror("set the frequency of the buzzer");
        exit(1);
    }
}

void Buzzer::on_slider_valueChanged(int value)
{
    QString nextState = ui->pushButton->text();
    if (nextState == "STOP") {
        set_buzzer_freq(value);
    }
    ui->label->setText(QString::number(value));
}

void Buzzer::moveEvent(QMoveEvent *)
{
    this->move(QPoint(0,0));
}

void Buzzer::resizeEvent(QResizeEvent *)
{
    this->showMaximized();
}

void Buzzer::on_pushButton_clicked()
{
    int freq;
    QString state = ui->pushButton->text();
    if (state == "START") {
        ui->pushButton->setText("STOP");
        freq = ui->slider->value();
        set_buzzer_freq(freq);

        ioctl(fd, BUZZER_ENABLE,0);
    } else if (state == "STOP") {
        ui->pushButton->setText("START");
        ioctl(fd, BUZZER_DISABLE,0);
    }
}
