#ifndef SD_H
#define SD_H

#include <QWidget>
#include <QFileSystemModel>
#include <QThread>
#include "mountthread.h"

namespace Ui {
class Sd;
}

class Sd : public QWidget
{
    Q_OBJECT

public:
    explicit Sd(QWidget *parent = 0);
    ~Sd();

protected:
    void moveEvent(QMoveEvent *);
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *);

private slots:
    void on_detectButton_clicked();
    void on_umountButton_clicked();
    /**
     * 处理MountThread线程发送过来的preMount()和postMount()信号
     */
    void dealwithUi(int mesg);

private:
    QFileSystemModel model;
    Ui::Sd *ui;
    MountThread *mountThread;    // 挂载线程
};

#endif // MAINWINDOW_H
