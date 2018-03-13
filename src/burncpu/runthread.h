#ifndef RUNTHREAD_H
#define RUNTHREAD_H

#include <QThread>
#include <QProcess>
#include <QTime>
#include <QDebug>


class Runthread : public QThread
{
    Q_OBJECT
public:
    explicit Runthread(QObject *parent = 0);

public:
    int prev_total;
    int prev_idle;

public slots:
    void run();
    void stop();
    void changestatus(int state);

private:
    int running;
};

#endif // RUNTHREAD_H
