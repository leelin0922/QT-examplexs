#include "eeprom.h"
#include "ui_eeprom.h"
#include <QDebug>
#include <stdio.h>
#include <fcntl.h>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QFrame>
#include <QtCore>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QCloseEvent>
#include <QMessageBox>
#include <unistd.h>
#include <QByteArray>
#include <QMessageBox>
#include <time.h>

#include <iostream>

#include <unistd.h>
#include "i2c.h"

#define BUFSIZE  32768

Eeprom::Eeprom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Eeprom)
{
    ui->setupUi(this);
    fd = -1;
}

Eeprom::~Eeprom()
{
    if (fd > 0)
	    ::close(fd);
    delete ui;
}


void Eeprom::moveEvent(QMoveEvent *)
{
    this->move(QPoint(0,0));
}

void Eeprom::resizeEvent(QResizeEvent *)
{
    this->showMaximized();
}

void Eeprom::closeEvent(QCloseEvent *)
{
    exit(0);
}

void Eeprom::on_pushButton_open_clicked()
{
    QString checkdev = ui->comboBox_dev->currentText();
    if(checkdev=="i2c-0")
        ui->lineEdit_addr->setText("0x1a");
    if(checkdev=="i2c-1")
        ui->lineEdit_addr->setText("0x08");
    if(checkdev=="i2c-2")
        ui->lineEdit_addr->setText("0x68");
    if(checkdev=="i2c-3")
        ui->lineEdit_addr->setText("0x50");
    if (ui->pushButton_open->text() == "open")
    {
        ui->pushButton_open->setText("close");
        QString dev_name = "/dev/";
        dev_name.append(ui->comboBox_dev->currentText());
        char *dev = dev_name.toLatin1().data();
        fd = open(dev, O_RDWR);
        if (fd < 0) {
            perror("open i2c device fail");
            exit(1);
        }
        /*
        if (ui->comboBox_dev->currentIndex() == 3)
        {
            ui->pushButton_write->setEnabled(false);
        }
        */
        i2c_set(fd, 3, 4);
    }
    else
    {
        ui->pushButton_open->setText("open");
        ::close(fd);
        //ui->pushButton_write->setEnabled(true);
        ui->pushButton_write->setEnabled(false);
        fd = -1;
    }
}

void Eeprom::on_pushButton_read_clicked()
{
    if (fd == -1)
    {
        QMessageBox::information(this, tr("warning"), "device is not open!");
        return;
    }
    int ret;
    QString addr_s = ui->lineEdit_addr->text();
    QString reg_s = ui->lineEdit_reg->text();

    unsigned char addr ;
    bool ok;
    if (addr_s.startsWith("0x") || addr_s.startsWith("0X"))
    {
        QString addr_t = addr_s.mid(2);
        addr = (unsigned char)addr_s.toInt(&ok, 16);
    }
    else
    {
        addr = addr_s.toInt();
    }

    unsigned char reg;
    if (reg_s.startsWith("0x") || reg_s.startsWith("0X"))
    {
        QString reg_t = reg_s.mid(2);
        reg = (unsigned char)reg_t.toInt(&ok, 16);
    }
    else
    {
        reg = reg_s.toInt();
    }

    int len = ui->lineEdit_len->text().toInt();

    unsigned char recvBuf[256];
    memset(recvBuf, 0, sizeof(recvBuf));

    ret = i2c_nbytes_read(fd, addr, reg, recvBuf, len);

    if (ret == -1) {
        QMessageBox::information(this, tr("warning"), "read error!");
    }
    else
    {
        char psztest[514]={0};
        memset(psztest,0,sizeof(psztest));
        for(int i=0;i<len;i++)
            sprintf(psztest+i*2,"%02x",recvBuf[i]);
        //ui->textEdit_read->setText((char *)recvBuf);
        ui->textEdit_read->setText((char *)psztest);
        QMessageBox::information(this, tr("info"),"read success!");
    }
}

void Eeprom::on_pushButton_write_clicked()
{
    if (fd == -1)
    {
        QMessageBox::information(this, tr("warning"), "device is not open!");
        return;
    }

    char input_data[512];
    memset(input_data, 0, sizeof(input_data));

    char *input = ui->textEdit_write->toPlainText().toLatin1().data();
//    printf("input: %s\n", input);
//    printf("input: %c\n", (unsigned char)input[0]);
//    printf("input: %c\n", (unsigned char)input[1]);
//    printf("input: %c\n", (unsigned char)input[2]);
    memcpy(input_data, input, strlen(input));
//    printf("input_data: %s\n", input_data);

    int str_len = strlen(input);
    QString addr_s = ui->lineEdit_addr->text();
    QString reg_s = ui->lineEdit_reg->text();

    int i;
    int ret;

    unsigned char addr ;
    bool ok;
    if (addr_s.startsWith("0x") || addr_s.startsWith("0X"))
    {
        QString addr_t = addr_s.mid(2);
        addr = (unsigned char)addr_s.toInt(&ok, 16);
    }
    else
    {
        addr = addr_s.toInt();
    }

    unsigned char reg;
    if (reg_s.startsWith("0x") || reg_s.startsWith("0X"))
    {
        QString reg_t = reg_s.mid(2);
        reg = (unsigned char)reg_t.toInt(&ok, 16);
    }
    else
    {
        reg = reg_s.toInt();
    }

    bool wrong_flag = false;
    int count = ui->lineEdit_len->text().toInt();

    for (i = 0; i < count; i++)
    {
        if (i < str_len)
        {
            ret = i2c_byte_write(fd, addr, reg + i, input_data[i]);
            usleep(5000);
        }
        else
        {
            ret = i2c_byte_write(fd, addr, reg + i, 0);
            usleep(5000);
        }
        if (ret == -1) {
            wrong_flag = true;
            printf("error , index: %d\n", i);
        }
    }
        if (wrong_flag) {
            QMessageBox::information(this, tr("warning"), "write error!");
        }
        else
        {
            QMessageBox::information(this, tr("info"),"write success!");
        }
}
