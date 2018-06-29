#include "emmc_erase.h"
#include "ui_emmc_erase.h"
#include <QDebug>
#include <QTime>
#include <QMessageBox>

Emmc_erase::Emmc_erase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Emmc_erase)
{
    ui->setupUi(this);
}

Emmc_erase::~Emmc_erase()
{
    delete ui;
}

void Emmc_erase::on_pushButton_clicked()
{
    QString state = ui->lineEdit->text();
    if (state == "Yes") {
        QTime pTimer;
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Erase ?", "Erase EMMC?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {

            qDebug() << "Yes was clicked";
            system("echo 0 > /sys/block/mmcblk3boot0/force_ro");
            pTimer.restart();
            while(pTimer.elapsed()<100);
            system("sync");
            pTimer.restart();
            while(pTimer.elapsed()<100);
            system("dd if=/dev/zero of=/dev/mmcblk3boot0 bs=512 seek=2");
            pTimer.restart();
            while(pTimer.elapsed()<100);
            system("sync");
            pTimer.restart();
            while(pTimer.elapsed()<100);
            system("echo 1 > /sys/block/mmcblk3boot0/force_ro");
            pTimer.restart();
            while(pTimer.elapsed()<100);
            system("sync");
            pTimer.restart();
            while(pTimer.elapsed()<100);
            system("reboot");
            pTimer.restart();
            while(pTimer.elapsed()<100);
            system("sync");
        } else {
            qDebug() << "Yes was *not* clicked";
        }


    }
}
