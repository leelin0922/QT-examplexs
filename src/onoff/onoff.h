#ifndef ONOFF_H
#define ONOFF_H

#include <QWidget>
#include <QFile>

namespace Ui {
class Onoff;
}

class Onoff : public QWidget
{
    Q_OBJECT

public:
    explicit Onoff(QWidget *parent = 0);
    ~Onoff();

private slots:
    void on_pushButton_clicked();

private:
    void add_startup_program();
    void add_datafile();
    void delete_onoff_startup();
    Ui::Onoff *ui;
};

#endif // ONOFF_H
