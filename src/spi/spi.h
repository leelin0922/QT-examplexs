#ifndef SPI_H 
#define SPI_H

#include <QWidget>

namespace Ui {
class Spi;
}

class Spi : public QWidget
{
    Q_OBJECT
    
public:
    explicit Spi(QWidget *parent = 0);
    ~Spi();
    
private slots:
    void on_send_clicked();

    void on_loop_clicked(bool checked);

    void on_clockphase_clicked(bool checked);

    void on_clockpolarity_clicked(bool checked);

    void on_lsb_clicked(bool checked);

    void on_cshigh_clicked(bool checked);

    void on_wire_clicked(bool checked);

    void on_nocs_clicked(bool checked);

    void on_ready_clicked(bool checked);

    void update_params();

    void on_speed_textChanged(const QString &arg1);

    void on_delay_textChanged(const QString &arg1);

    void on_bits_textChanged(const QString &arg1);

    void on_pushButton_open_clicked();

    void on_pushButton_clicked();

protected:
    void moveEvent(QMoveEvent *);
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *);
private:
    Ui::Spi *ui;
    int fd;
};

#endif // MAINWINDOW_H
