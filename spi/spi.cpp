#include "spi.h"
#include "ui_spi.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <QMessageBox>
#include <stdio.h>

Spi::Spi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Spi)
{
    ui->setupUi(this);

    /*
    fd = ::open("/dev/spidev0.0",O_RDWR);

    if(fd < 0)
    {
        //QMessageBox::about(this,"error","open spidev failure");
        //exit(0);
    }

    update_params();
    */
}

void Spi::update_params()
{
    unsigned char mode = 0,bits;
    unsigned int speed;
    //unsigned short delay;
    int ret;

    speed = ui->speed->text().toInt();
    //delay = (unsigned short)ui->delay->text().toInt();
    bits  = ui->bits->text().toInt();

    if(ui->loop->isChecked())
        mode |= SPI_LOOP;

    if(ui->clockphase->isChecked())
        mode |= SPI_CPHA;

    if(ui->clockpolarity->isChecked())
        mode |= SPI_CPOL;

    if(ui->lsb->isChecked())
        mode |= SPI_LSB_FIRST;

    if(ui->cshigh->isChecked())
        mode |= SPI_CS_HIGH;

    if(ui->wire->isChecked())
        mode |= SPI_3WIRE;

    if(ui->nocs->isChecked())
        mode |= SPI_NO_CS;

    if(ui->ready->isChecked())
        mode |= SPI_READY;

    // spi模式 
    ret = ::ioctl(fd,SPI_IOC_WR_MODE,&mode);
    if(ret < 0)
    {
        QMessageBox::about(this,"error","SPI_IOC_WR_MODE failure");
        return;
   //     exit(0);
    }
    // 传送字的位数
    ret = ::ioctl(fd,SPI_IOC_WR_BITS_PER_WORD,&bits);
    if(ret < 0)
    {
        QMessageBox::about(this,"error","SPI_IOC_WR_BITS_PER_WORD failure");
        return;
    //    exit(0);
    }
    //传送的最大速度
    ret = ::ioctl(fd,SPI_IOC_WR_MAX_SPEED_HZ,&speed);
    if(ret < 0)
    {
        QMessageBox::about(this,"error","SPI_IOC_WR_MAX_SPEED_HZ failure");
        return;
    //    exit(0);
    }
}

Spi::~Spi()
{
    delete ui;
    //::close(fd);
}

//发送的时候也在接收
//MISO和MOSI引脚连接的时候，接收端可以收到显示的数据。
void Spi::on_send_clicked()
{
    if (fd < 0)
        return;
    std::string str = ui->editsend->text().toStdString();
    struct spi_ioc_transfer tr;
    char buf[str.length()+1];
    memset(buf,0,str.length()+1);
    //要发送的数据
    tr.tx_buf = (__u64)str.c_str();
    //要接收的数据
    tr.rx_buf = (__u64)buf;
    //数据长度
    tr.len = str.length();
    //本次发送和下次发送时间间隔
    tr.delay_usecs = ui->delay->text().toInt();
    //总线速率
    tr.speed_hz = ui->speed->text().toInt();
    //每一字的二进制位数
    tr.bits_per_word = ui->bits->text().toInt();
    //发送数据，接收数据
    ::ioctl(fd,SPI_IOC_MESSAGE(1),&tr);
    //显示接收的数据
    ui->editrecv->append(QString(buf));

}

void Spi::on_loop_clicked(bool checked)
{
    update_params();
}

void Spi::on_clockphase_clicked(bool checked)
{
    update_params();
}

void Spi::on_clockpolarity_clicked(bool checked)
{
    update_params();
}

void Spi::on_lsb_clicked(bool checked)
{
    update_params();
}

void Spi::on_cshigh_clicked(bool checked)
{
    update_params();
}

void Spi::on_wire_clicked(bool checked)
{
    update_params();
}

void Spi::on_nocs_clicked(bool checked)
{
    update_params();
}

void Spi::on_ready_clicked(bool checked)
{
    update_params();
}

void Spi::on_speed_textChanged(const QString &arg1)
{
    update_params();
}

void Spi::on_delay_textChanged(const QString &arg1)
{
    update_params();
}

void Spi::on_bits_textChanged(const QString &arg1)
{
    update_params();
}

void Spi::moveEvent(QMoveEvent *)
{
    this->move(QPoint(0,0));
}

void Spi::resizeEvent(QResizeEvent *)
{
    this->showMaximized();
}

void Spi::closeEvent(QCloseEvent *)
{
    exit(0);
}

void Spi::on_pushButton_open_clicked()
{

    if (ui->pushButton_open->text() == "open")
    {
        ui->pushButton_open->setText("close");

        QString dev_name = "/dev/";
        dev_name.append(ui->comboBox_dev->currentText());
        char *dev = dev_name.toLatin1().data();
        fd = open(dev, O_RDWR);
        if (fd < 0) {
            printf("open i2c device fail");
            exit(1);
        }
        update_params();
    }
    else
    {
        ui->pushButton_open->setText("open");
        //close(fd);
        fd = -1;
    }
}

void Spi::on_pushButton_clicked()
{
   ui->editrecv->clear();
}
