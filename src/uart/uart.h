#ifndef UART_H
#define UART_H

#include <stdlib.h>
#include <stdio.h>
#include <QPushButton>
#include <qobject.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <linux/spi/spidev.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include <QTimer>
#include <QMainWindow>
#include <QWidget>

#include <QThread>


namespace Ui {
class Uart;
}

class Uart : public QWidget
{
    Q_OBJECT
    

public:
    explicit Uart(QWidget *parent = 0);
    int open_uart_port(int fd,int comport);
    int set_uart_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop);

    ~Uart();
public slots:
    void SotSetTime();
    void repeatSendTime();

private slots:
    void on_pushButton_send_clicked();

    void on_pushButton_clean_clicked();

    void on_pushButton_open_clicked();

    void on_repeatCheckBox_clicked();

private:
    Ui::Uart *ui;
    int fd;
    int fd_com_mode_sel;
    int autosend_flag;
    int count;
    int auto_send_flag;
    int receive_flag;
    char buffer[300];
    QTimer testTimer ;
    QTimer sendTimer ;

    QString value;

    char ch_first;
    char ch_last;
    char stringLen;

    int matchCount;
    int misMatchCount;
    char recvString[100];
    int recvByteCount;
    char *matchString;
};

#endif // MAINWINDOW_H
