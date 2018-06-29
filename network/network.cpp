#include "network.h"
#include "ui_network.h"

Network::Network(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Network)
{
    ui->setupUi(this);
    proc = NULL;
    flag = false;
    connect(ui->cb_interface, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(on_sel_changed(QString)));
    connect(ui->ok, SIGNAL(clicked()), this, SLOT(on_ok_clicked()));
    connect(ui->radio_dhcp, SIGNAL(toggled(bool)), this, SLOT(on_toggled(bool)));
    connect(ui->radio_static, SIGNAL(toggled(bool)), this, SLOT(on_toggled(bool)));

    refreshInterfaces();
    readConfigs();
    on_sel_changed(ui->cb_interface->currentText());
}

Network::~Network()
{
    delete ui;
    foreach(Interface *i,ints)
        delete i;
}

void Network::state(bool dhcp)
{
    if(dhcp)
    {
        ui->radio_dhcp->setChecked(true);
        ui->radio_static->setChecked(false);
        ui->edt_ip->setDisabled(true);
        ui->edt_mask->setDisabled(true);
        ui->edt_gateway->setDisabled(true);
        ui->edt_dns->setDisabled(true);
    }
    else
    {
        ui->radio_dhcp->setChecked(false);
        ui->radio_static->setChecked(true);
        ui->edt_ip->setDisabled(false);
        ui->edt_mask->setDisabled(false);
        ui->edt_gateway->setDisabled(false);
        ui->edt_dns->setDisabled(false);
    }
}

void Network::refreshInterfaces()
{
    QStringList sl;

    /*???eth[0-9] wlan[0-9]*/
    ::system("ifconfig -a|grep -E \"eth[0-9]\"|cut -d' ' -f 1 >/tmp/interfaces");
    QFile f("/tmp/interfaces");
    if(f.open(QFile::ReadOnly))
    {
        QTextStream t(&f);
        while(!t.atEnd())
        {
            QString str=t.readLine();
            if(str.size()>0)
            {
                //QMessageBox::about(this,"aaa",str);
                ints.append(new Interface(str));
                sl<<str;
            }
        }
    }
    f.close();

    ui->cb_interface->addItems(sl);
}

void Network::readConfigs()
{
    /*???????*/
    foreach(Interface *i,ints)
    {
        QFile f("/etc/network/.conf/"+i->name);
        if(f.open(QFile::ReadOnly))
        {
            QTextStream t(&f);
            QString str = t.readLine();

            if(str == "dhcp")//do nothing
                ;
            else if(str == "static")
            {
                i->dhcp = false;
                i->ip = t.readLine();
                i->mask = t.readLine();
                i->gateway = t.readLine();
                i->dns = t.readLine();
            }
        }
        f.close();
    }
}

unsigned int ip2int(QString ip)
{
    QStringList sl = ip.split('.');
    unsigned int r = 0;
    foreach(QString s,sl)
    {
        r <<= 8;
        r |= s.toUInt();
    }

    return r;
}

QString int2ip(unsigned int ip)
{
    return QString::number((ip >> 24) & 0xff) + "." + QString::number((ip >> 16) & 0xff)
            + "." + QString::number((ip >> 8) & 0xff) + "." + QString::number(ip & 0xff);
}

void Network::writeConfigs()
{
    /*???????*/
    //::system("rm /etc/resolv.conf");
    QFile r("/etc/resolv.conf");//for dns
    QTextStream *t2 = NULL;
    if(r.open(QFile::WriteOnly))
    {
        t2 = new QTextStream(&r);
    }

    QFile m("/etc/network/interfaces");//for interface
    QTextStream *t3 = NULL;
    if(m.open(QFile::WriteOnly))
    {
        t3 = new QTextStream(&m);
    }

    /*write `lo` configration first*/
    *t3<<QString("auto lo\n");
    *t3<<QString("iface lo inet loopback\n");

    ::system("mkdir -p /etc/network/.conf");

    /*???????*/
    foreach(Interface *i,ints)
    {
        QFile f("/etc/network/.conf/"+i->name);

        if(f.open(QFile::WriteOnly))
        {
            QTextStream t(&f);

            if(i->dhcp)
            {
                t<<QString("dhcp")<<QString(QString("\n"));
                *t3<<QString("auto ")<<i->name<<QString(QString("\n"));
                *t3<<QString("iface ")<<i->name<<QString(" inet dhcp\n");
            }
            else
            {
                t<<QString("static")<<QString("\n");
                t<<i->ip<<QString("\n");
                t<<i->mask<<QString("\n");
                t<<i->gateway<<QString("\n");
                t<<i->dns<<QString("\n");

                *t3<<QString("auto ")<<i->name<<QString("\n");
                *t3<<QString("iface ")<<i->name<<QString(" inet static\n");
                *t3<<QString("address ")<<i->ip<<QString("\n");
                *t3<<QString("netmask ")<<i->mask<<QString("\n");
                *t3<<QString("gateway ")<<i->gateway<<QString("\n");
                *t3<<QString("broadcast ")<<int2ip((ip2int(i->ip) & ip2int(i->mask))|(~ip2int(i->mask)))<<QString("\n");

                *t2<<QString("nameserver ")<<i->dns<<QString("\n");//?????/etc/resolv.conf
            //    printf("nameserver:%s\n", (i->dns).toStdString().c_str());
                /* Tony */
                char ip_set[30];
                memset(ip_set, 0, sizeof(ip_set));
                const char *ip = (i->ip).toStdString().c_str();
                sprintf(ip_set, "ifconfig eth0 %s", ip);
                ::system(ip_set);
            }
        }
        f.close();
    }

    delete t2;
    delete t3;

    r.close();
    m.close();
}

void Network::on_toggled(bool b)
{
    Interface *i = NULL;
    foreach(i,ints)
    {
        if(i->name == ui->cb_interface->currentText())
            break;
    }

    state(ui->radio_dhcp->isChecked());

    if(ui->radio_dhcp->isChecked())
    {
        /*ui->edt_ip->clear();
        ui->edt_mask->clear();
        ui->edt_gateway->clear();
        ui->edt_dns->clear();*/
    }
    else
    {
        ui->edt_ip->setText(i->ip);
        ui->edt_mask->setText(i->mask);
        ui->edt_gateway->setText(i->gateway);
        ui->edt_dns->setText(i->dns);
    }
}

void Network::on_sel_changed(const QString &text)
{
    Interface *i = NULL;
    foreach(i,ints)
    {
        if(i->name == text)
            break;
    }

    //QMessageBox::about(this,"aaa",i->name);

    state(i->dhcp);

    if(i->dhcp)
    {
        ui->edt_ip->clear();
        ui->edt_mask->clear();
        ui->edt_gateway->clear();
        ui->edt_dns->clear();
    }
    else
    {
        ui->edt_ip->setText(i->ip);
        ui->edt_mask->setText(i->mask);
        ui->edt_gateway->setText(i->gateway);
        ui->edt_dns->setText(i->dns);
    }
}

void Network::on_ok_clicked()
{
    Interface *i = NULL;
    foreach(i,ints)
    {
        if(i->name == ui->cb_interface->currentText())
            break;
    }

    i->dhcp = ui->radio_dhcp->isChecked();
    i->ip = ui->edt_ip->text();
    i->mask = ui->edt_mask->text();
    i->gateway = ui->edt_gateway->text();
    i->dns = ui->edt_dns->text();

    writeConfigs();

    if(proc)
        delete proc;

    proc = new QProcess(this);

    proc->start("/etc/init.d/networking restart");
    //proc->start("/etc/rc.d/init.d/network restart");
    connect(proc,SIGNAL(finished(int)),this,SLOT(proc_finished(int)));

    this->setDisabled(true);

    flag = true;
}

void Network::closeEvent(QCloseEvent * evt)
{
    if(flag)
    {
        evt->ignore();
        QMessageBox::about(this,"info","network is restarting,please wait");
    }
    else
    {
        destroy();
        exit(0);
    }
}


void Network::moveEvent(QMoveEvent *)
{
    this->move(QPoint(0,0));
}

void Network::resizeEvent(QResizeEvent *)
{
    this->showMaximized();
}

void Network::proc_finished(int code)
{
    if(proc->exitStatus() == QProcess::NormalExit)
    {
        this->setDisabled(false);
        flag = false;
         QMessageBox::about(this,"info","network restart ok!");
    }
    ::system("sync");
}




