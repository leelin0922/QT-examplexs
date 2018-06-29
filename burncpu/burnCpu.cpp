#include "burnCpu.h"
#include "ui_burnCpu.h"
#include <QDebug>
//#include <QTimer>

BurnCpu::BurnCpu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BurnCpu)
{
    ui->setupUi(this);
    pParser = new Parser();
    connect(pParser, SIGNAL(parsercpuusageSignal(float)), this, SLOT(usageSlot(float)));
    connect(pParser, SIGNAL(parsercputemperatureSignal(float)), this, SLOT(temperatureSlot(float)));
    pParser->changestatus(-1);
    pParser->start();

    pRunthread = new Runthread();
    pRunthread->changestatus(-1);
    pRunthread->start();
}


BurnCpu::~BurnCpu()
{
    if(pParser)
    {
        pParser->stop();
        pParser->deleteLater();
    }
    if(pRunthread)
    {
        pRunthread->stop();
        pRunthread->deleteLater();
    }
    delete ui;
}

void BurnCpu::usageSlot(float iUsage)
{
    QString tempString = QString::number(iUsage,'g',4);
    tempString += "%";

    ui->cpuusagevalue->setText(tempString);
}

void BurnCpu::temperatureSlot(float iTemperature)
{
    QString tempString = QString::number(iTemperature,'g',4);
    tempString += "°C";

    ui->cputempvalue->setText(tempString);
}

void BurnCpu::on_pushButton_clicked()
{

    QString state = ui->pushButton->text();
    if (state == "START") {
        pParser->changestatus(1);
        pRunthread->changestatus(1);
        ui->pushButton->setText("STOP");
    } else if (state == "STOP") {
        pParser->changestatus(-1);
        pRunthread->changestatus(-1);
        ui->pushButton->setText("START");
    }
}
