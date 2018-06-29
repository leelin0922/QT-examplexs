#ifndef PARSER_H
#define PARSER_H

#include <QThread>
#include <QProcess>
#include <QTime>
#include <QDebug>


class Parser : public QThread
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = 0);

signals:
    void parsercpuusageSignal(float iUsage);
    void parsercputemperatureSignal(float itemp);

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

#endif // PARSER_H
