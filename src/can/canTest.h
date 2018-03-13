#ifndef CANTEST_H
#define CANTEST_H

#include <QWidget>
#include <QProcess>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include "thread.h"
#include <QButtonGroup>

namespace Ui {
class CanTest;
}

class CanTest : public QWidget
{
    Q_OBJECT
    
public:
    explicit CanTest(QWidget *parent = 0);
    ~CanTest();
protected:
    void moveEvent(QMoveEvent *);
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *);
    void stopcan(int v);
    void startcan(int v);

private slots:
    void on_datasend_clicked();
    void on_start_clicked();
    void msg(QString str);

private:
    Ui::CanTest *ui;
    int pSocket;
    struct sockaddr_can addr;
    Thread *pThread;
    QButtonGroup* btg;
    int canNumber;
    QString baudrate;
};

#endif // MAINWINDOW_H
