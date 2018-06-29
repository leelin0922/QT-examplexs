#ifndef COM_MODE_H
#define COM_MODE_H

#include <QWidget>
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
#include <sys/ioctl.h>

namespace Ui {
class Com_mode;
}

class Com_mode : public QWidget
{
    Q_OBJECT

public:
    explicit Com_mode(QWidget *parent = 0);
    ~Com_mode();

private:
    Ui::Com_mode *ui;
    int fd;
private slots:
    void on_pushButton_O_1_clicked();
    void on_pushButton_O_2_clicked();
    void on_pushButton_O_3_clicked();
    void on_pushButton_O_4_clicked();
};

#endif // COM_MODE_H
