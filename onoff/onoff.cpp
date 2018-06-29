#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "onoff.h"
#include "ui_onoff.h"
#include <QDebug>

#define ONOFF_DATAFILE      "/etc/xdg/onoff"
#define ONOFF_STARTUP_FILE  "/etc/xdg/autostart/onoff.desktop"

Onoff::Onoff(QWidget *parent) :
	QWidget(parent),
    ui(new Ui::Onoff)
{
    ui->setupUi(this);
    QFile qfile( ONOFF_DATAFILE );
    if(!qfile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
        ui->pushButton->setText("START");
        return;
    }
    if(qfile.size()<=0)
    {
        qfile.close();
        system("sync");
        qDebug()<<"Can't open the file!"<<endl;
        ui->pushButton->setText("START");
        delete_onoff_startup();
        return;
    }
    QString pline = qfile.readLine();
    qfile.close();
    remove(ONOFF_DATAFILE);
    sync();
    if(!qfile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        ui->pushButton->setText("START");
        return;
    }
    if(qfile.size()>0)
    {
        qDebug()<< "file creat error" << qfile.size();
    }

    ui->pushButton->setText("STOP");
    int pcount=pline.toInt()+1;
    pline =QString::number(pcount);

    ui->runtimescount->setText(pline);
    qDebug() << pline;
    qfile.reset();
    qfile.seek(0);
    qfile.write(pline.toLatin1());
    qfile.close();
    system("sync");
}

Onoff::~Onoff()
{
	delete ui;
}

void Onoff::add_startup_program()
{
    QFile qfile( ONOFF_STARTUP_FILE );
    if(!qfile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
        ui->pushButton->setText("START");
        return;
    }
    qfile.reset();
    qfile.seek(0);
    qfile.write("[Desktop Entry]\n");
    qfile.write("Exec=/usr/share/utils\n");
    qfile.close();
    system("sync");
}

void Onoff::add_datafile()
{
    QFile qfile( ONOFF_DATAFILE );
    if(!qfile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
        ui->pushButton->setText("START");
        return;
    }
    qfile.reset();
    qfile.seek(0);
    qfile.write("0");
    qfile.close();
    system("sync");
}

void Onoff::delete_onoff_startup()
{
    ::remove(ONOFF_DATAFILE);
    ::remove(ONOFF_STARTUP_FILE);
    system("sync");
}

void Onoff::on_pushButton_clicked()
{

    QString state = ui->pushButton->text();
    if (state == "START") {
        ui->pushButton->setText("STOP");
        qDebug() << "start";
        add_startup_program();
        add_datafile();
        ui->runtimescount->setText("0");
        system("sync");
    } else if (state == "STOP") {
        ui->pushButton->setText("START");
        qDebug() << "stop";
        delete_onoff_startup();
        ui->runtimescount->setText(" ");
        system("sync");
    }
}
