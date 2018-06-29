#ifndef BURNCPU_H
#define BURNCPU_H

#include <QWidget>
#include <QProcess>
#include <QDebug>
#include <QPushButton>
#include <QThread>
#include <QTime>
#include "parser.h"
#include "runthread.h"

namespace Ui {
class BurnCpu;
}

class BurnCpu : public QWidget
{
    Q_OBJECT

public:
    explicit BurnCpu(QWidget *parent = 0);
    ~BurnCpu();

private:

signals:
    void controlState(bool);

private slots:
    void on_pushButton_clicked();
    void usageSlot(float iUsage);
    void temperatureSlot(float iTemperture);

private:
    Ui::BurnCpu *ui;
    Parser * pParser;
    Runthread * pRunthread;
};


#endif // MAINWINDOW_H
