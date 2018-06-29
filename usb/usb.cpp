#include "usb.h"
#include "ui_usb.h"

Usb::Usb(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Usb)
{
    ui->setupUi(this);
}

Usb::~Usb()
{
    delete ui;
}

void Usb::on_pushButton_clicked()
{
//    if(myprocess)
//        delete myprocess;

    myprocess = new QProcess(this);
    connect(myprocess, SIGNAL(readyReadStandardOutput()),this, SLOT(result()));
    connect(myprocess, SIGNAL(readyReadStandardError()),this, SLOT(result()));
    //myprocess->start("cat /proc/bus/usb/devices");
    myprocess->start("cat /sys/kernel/debug/usb/devices");
    ui->result->clear();
}
void Usb::result()
{
    QString abc = myprocess->readAllStandardOutput();
    ui->result->append(abc.trimmed());
    QString efg = myprocess->readAllStandardError();
    if(efg.length()>1)ui->result->append(efg.trimmed());

}
