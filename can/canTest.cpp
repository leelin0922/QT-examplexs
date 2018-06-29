#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include "canTest.h"
#include "ui_canTest.h"
#include <QDebug>
#include <QMessageBox>
#include <QTime>

CanTest::CanTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CanTest)
{
    //int pd;
    //char buf[32];

    ui->setupUi(this);
    canNumber=0;
    pSocket=-1;
    btg = new QButtonGroup;
    btg->addButton(ui->can0,0);
    btg->addButton(ui->can1,1);
    system("ifconfig can0 down");
    system("ifconfig can1 down");
}

CanTest::~CanTest()
{
    delete ui;
}

void CanTest::msg(QString str)
{
    ui->label->append(str);
}

void CanTest::on_datasend_clicked()
{
    //qDebug() << "on_datasend_clicked:"<< "pSocket" << pSocket << endl;
    if(pSocket>=0)
    {
        struct can_frame frame;
        std::string  str=ui->edit->text().toStdString();

        if(str.length() > 8)
        {
            QMessageBox::about(this,"error","length of send string must less than 8 bytes");
            return;
        }

        frame.can_id = 0x7ff;
        strcpy((char*)frame.data,str.c_str());
        frame.can_dlc = str.length();

        int nbytes = ::write(pSocket, &frame, sizeof(struct can_frame));
        if(nbytes < 0){
            qDebug() << "Error! while writting can raw socket";
        }
        //sendto(pSocket,&frame,sizeof(struct can_frame),0,(struct sockaddr*)&addr,sizeof(addr));
    }
}

void CanTest::moveEvent(QMoveEvent *)
{
    this->move(QPoint(0,0));
}

void CanTest::resizeEvent(QResizeEvent *)
{
    this->showMaximized();
}

void CanTest::closeEvent(QCloseEvent *)
{
     exit(0);
}

void CanTest::startcan(int v)
{
    QTime pTimer;
    QString command;

    command.clear();
    //command.append("canconfig can").append(QString::number(v)).append(" bitrate ").append(baudrate).append(" ctrlmode triple-sampling on");
    //ip link set can0 up type can bitrate 125000
    command.append("ip link set can").append(QString::number(v)).append(" up type can bitrate ").append(baudrate);
    qDebug() << command;
    system(command.toLocal8Bit().constData());
    //system(command.toUtf8().constData());

    pTimer.start();
    while(pTimer.elapsed()<100);
    if(v == 0)
    {
        //system("canconfig can0 bitrate 125000 ctrlmode triple-sampling on");
        system("ifconfig can0 up");
    }
    else
    {
        //system("canconfig can1 bitrate 125000 ctrlmode triple-sampling on");
        system("ifconfig can1 up");
    }

    pTimer.restart();
    while(pTimer.elapsed()<100);
    pSocket =  ::socket(PF_CAN,SOCK_RAW,CAN_RAW);
    qDebug() << "socket" << pSocket << endl;
    if(pSocket < 0) {
        return;
     }

    struct ifreq ifr;
    strcpy((char *)(ifr.ifr_name),v == 0 ? "can0" : "can1");
    ioctl(pSocket,SIOCGIFINDEX,&ifr);

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if(bind(pSocket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    	qDebug() << "Error in socket bind" << endl;
	}

    pTimer.restart();
    while(pTimer.elapsed()<100);

    pThread = NULL;
    pThread = new Thread(pSocket);
    connect(pThread,SIGNAL(msg(QString)),this,SLOT(msg(QString)));
    pThread->start();
}

void CanTest::stopcan(int v)
{
    if(pThread)
    {
        pThread->stop();
        pThread->deleteLater();
    }

    ::close(pSocket);

    if(v == 0)
        system("canconfig can0 stop");
    else
        system("canconfig can1 stop");
}

void CanTest::on_start_clicked()
{
    if ( this->ui->start->text().trimmed().compare("start") == 0 ) {
        canNumber = this->btg->checkedId();
        int baudrateNumber = this->ui->baudrate->currentIndex();

        switch (baudrateNumber) {
            case 0:
                baudrate = "10000";
                break;
            case 1:
                baudrate = "20000";
                break;
            case 2:
                baudrate = "40000";
                break;
            case 3:
                baudrate = "50000";
                break;
            case 4:
                baudrate = "80000";
                break;
            case 5:
                baudrate = "100000";
                break;
            case 6:
                baudrate = "125000";
                break;
            case 7:
                baudrate = "200000";
                break;
            case 8:
                baudrate = "250000";
                break;
            case 9:
                baudrate = "400000";
                break;
            case 10:
                baudrate = "500000";
                break;
            case 11:
                baudrate = "666000";
                break;
            case 12:
                baudrate = "800000";
                break;
            case 13:
                baudrate = "1000000";
                break;
            default:
                baudrate = "1000000";
        }
        qDebug() << "canNumber" << canNumber << "baudrate: " << baudrate << endl;

        startcan(canNumber);
        this->ui->currentBaudrate->setText( QString().append("Current Baudrate : ").append(this->ui->baudrate->currentText()) );
        this->ui->start->setText("stop");
    } else {
        stopcan(canNumber);
        this->ui->start->setText("start");
    }
}
