#ifndef USB_H
#define USB_H

#include <QWidget>
#include <QProcess>

namespace Ui {
class Usb;
}

class Usb : public QWidget
{
    Q_OBJECT
    
public:
    explicit Usb(QWidget *parent = 0);
    ~Usb();
    
private slots:
    void on_pushButton_clicked();
    void result();
private:
    Ui::Usb *ui;
    QProcess *myprocess;
};

#endif // MAINWINDOW_H
