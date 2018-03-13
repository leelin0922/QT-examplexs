#include "audio.h"
#include "ui_audio.h"
#include <QDebug>

Audio::Audio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Audio)
{
    ui->setupUi(this);
}

Audio::~Audio()
{
    delete ui;
}

void Audio::on_pushButton_clicked()
{

    // system("mkdir /tmp/usb_disk");
    // system("umount /tmp/usb_disk");
    // system("mount /dev/sda1 /tmp/usb_disk");


    qDebug() << "aplay /usr/share/sbc-7109-test.wav &" << endl;
    system("aplay  /usr/share/sbc-7109-test.wav &");
    sleep(1);
    // system("umount /tmp/usb_disk");
}
