#ifndef EMMC_ERASE_H
#define EMMC_ERASE_H

#include <QWidget>

namespace Ui {
class Emmc_erase;
}

class Emmc_erase : public QWidget
{
    Q_OBJECT

public:
    explicit Emmc_erase(QWidget *parent = 0);
    ~Emmc_erase();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Emmc_erase *ui;
};

#endif // EMMC_ERASE_H
