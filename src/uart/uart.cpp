#include "uart.h"
#include "ui_uart.h"

#include <QMessageBox>

Uart::Uart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Uart)
{
    ui->setupUi(this);

    //接收定时器
    connect(&testTimer,SIGNAL(timeout()),this,SLOT(SotSetTime()));
    //重复send定时器
    connect(&sendTimer,SIGNAL(timeout()),this,SLOT(repeatSendTime()));

     autosend_flag = 0;
     auto_send_flag = 0;
     count = 0;
     memset(recvString, 0, sizeof(recvString));
     recvByteCount = 0;

    //默认时间间隔
     ui->repeatTimeLineEdit->setText("100");

     ui->sendTextLineEdit->setText("abcdefghijklmnopqrstuvwxyz0123456789");
/*
     fd_com_mode_sel = open( "/dev/com3mode", O_RDWR|O_NDELAY);
     if (-1 == fd_com_mode_sel)
     {
         printf("open /dev/com3mode fail\n");
         //return(-1);
     }
*/
}

Uart::~Uart()
{
    if (testTimer.isActive())
        testTimer.stop();
    if (sendTimer.isActive())
        sendTimer.stop();
    tcflush(fd,TCIOFLUSH);
    ::close(fd);
    ::close(fd_com_mode_sel);
    delete ui;
}

int Uart::open_uart_port(int fd,int comport)
{
        //select uart port
        int ret;
        if (comport==1)
        {
            try {
                ret = system("grep ttymxc0 /etc/inittab | grep  -v \"#\"");
                if (ret  == 0)
                {
                    throw "Current port has been used by debug port!";
                }
                fd = open( "/dev/ttymxc0", O_RDWR|O_NDELAY);
                if (-1 == fd)
                {
                    printf("open fail\n");
                    ::close(fd);
                    delete ui;
                    return(-1);
                }
                else
                {
                    printf("open ttymxc0 .....\n");
                }
            }
            catch (const char * msg){
                QMessageBox::information(this, tr("warning"), msg);
                return -1;
            }
        }
        else if(comport==2)
        {
            fd = open( "/dev/ttymxc1", O_RDWR|O_NOCTTY|O_NDELAY);
            if (-1 == fd)
            {
                return(-1);
            }
            else
            {
                printf("open ttymxc1 .....\n");
            }
        }
        else if (comport==3)
        {
            fd = open( "/dev/ttymxc2", O_RDWR|O_NOCTTY|O_NDELAY);
            if (-1 == fd)
            {
                return(-1);
            }
            else
            {
                printf("open ttymxc2 .....\n");
            }
        }
        else if (comport==4)
        {
            fd = open( "/dev/ttymxc3", O_RDWR|O_NOCTTY|O_NDELAY);
            if (-1 == fd)
            {
                return(-1);
            }
            else
            {
                printf("open ttymxc3 .....\n");
            }
        }
        else if (comport==5)
        {
            fd = open( "/dev/ttymxc4", O_RDWR|O_NOCTTY|O_NDELAY);
            if (-1 == fd)
            {
                return(-1);
            }
            else
            {
                printf("open ttymxc4 .....\n");
            }
        }

        if(fcntl(fd, F_SETFL, 0)<0)
        {
            printf("fcntl failed!\n");
        }
        else
        {
            printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));
        }
        if(isatty(STDIN_FILENO)==0)
        {
            printf("standard input is not a terminal device\n");
        }
        else
        {
            printf("isatty success!\n");
        }

        printf("fd-open=%d\n",fd);
        if (ui->repeatCheckBox->isChecked()) {
            sendTimer.start(ui->repeatTimeLineEdit->text().toInt());
        }
        testTimer.start(1);

        return fd;
}

int Uart::set_uart_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{

    struct termios newtio,oldtio;
       if  ( tcgetattr( fd,&oldtio)  !=  0)
       {
           perror("SetupSerial 1");
           return -1;
       }
       bzero( &newtio, sizeof( newtio ) );
       newtio.c_cflag  |=  CLOCAL | CREAD;
       newtio.c_cflag &= ~CSIZE;

       switch( nBits )
       {
       case 7:
           newtio.c_cflag |= CS7;
           break;
       case 8:
           newtio.c_cflag |= CS8;
           break;
       }

       switch( nBits )
          {
          case 7:
              newtio.c_cflag |= CS7;
              break;
          case 8:
              newtio.c_cflag |= CS8;
              break;
          }

          switch( nEvent )
          {
          case 'O':                     //奇校验
              newtio.c_cflag |= PARENB;
              newtio.c_cflag |= PARODD;
              newtio.c_iflag |= (INPCK | ISTRIP);
              break;
          case 'E':                     //偶校验
              newtio.c_iflag |= (INPCK | ISTRIP);
              newtio.c_cflag |= PARENB;
              newtio.c_cflag &= ~PARODD;
              break;
          case 'N':                    //无校验
              newtio.c_cflag &= ~PARENB;
              break;
      }

          switch( nSpeed )
              {
          case 300:
              cfsetispeed(&newtio, B300);
              cfsetospeed(&newtio, B300);
              break;
          case 600:
              cfsetispeed(&newtio, B600);
              cfsetospeed(&newtio, B600);
              break;

              case 1200:
                  cfsetispeed(&newtio, B1200);
                  cfsetospeed(&newtio, B1200);
                  break;
              case 2400:
                  cfsetispeed(&newtio, B2400);
                  cfsetospeed(&newtio, B2400);
                  break;
              case 4800:
                  cfsetispeed(&newtio, B4800);
                  cfsetospeed(&newtio, B4800);
                  break;
              case 9600:
                  cfsetispeed(&newtio, B9600);
                  cfsetospeed(&newtio, B9600);
                  break;
              case 19200:
                  cfsetispeed(&newtio, B19200);
                  cfsetospeed(&newtio, B19200);
                  break;
              case 38400:
                  cfsetispeed(&newtio, B38400);
                  cfsetospeed(&newtio, B38400);
                  break;
              case 57600:
                  cfsetispeed(&newtio, B57600);
                  cfsetospeed(&newtio, B57600);
                  break;
              case 115200:
                  cfsetispeed(&newtio, B115200);
                  cfsetospeed(&newtio, B115200);
                  break;
              default:
                  cfsetispeed(&newtio, B9600);
                  cfsetospeed(&newtio, B9600);
                  break;
      }
          if( nStop == 1 )
          {
              newtio.c_cflag &=  ~CSTOPB;
          }
          else if ( nStop == 2 )
          {
              newtio.c_cflag |=  CSTOPB;
          }
          newtio.c_cc[VTIME]  = 0;
          newtio.c_cc[VMIN] = 0;
          tcflush(fd,TCIOFLUSH);
          if((tcsetattr(fd,TCSANOW,&newtio))!=0)
          {
              perror("com set error");
              return -1;
          }
          printf("set done!\n");
          return 0;
}

void Uart::on_pushButton_send_clicked()
{

    if (fd <=0)
    {
        value = "open device error!";
        //ui->label->setText(value);
        return ;
    }
    /*
    if (ui->repeatCheckBox->isChecked())
    {
            return;
    }
    */
    //ui->label->setText("0123456789");
    QByteArray ba = (ui->sendTextLineEdit->text()).toLatin1();
    char *str = ba.data();
    int len = strlen(str);
    :: write(fd, str, len);
}

void Uart::repeatSendTime()
{
//    int len = ui->sendTextLineEdit->text().length();
    QByteArray ba = (ui->sendTextLineEdit->text() + '\n').toLatin1();
    char *str = ba.data();
    int len = strlen(str);
    ::write(fd, str, len);
}

void Uart::SotSetTime()
{
     int i,re;

     if (ui->recv_send_checkBox->isChecked())
     {
        memset(buffer, 0, 300);
        re = read(fd,buffer,300);
		if (re == 0)
                return;
        ::write(fd, buffer, re);
        //::write(fd, buffer, strlen(buffer));
     }
     else
     {
         memset(buffer, 0, 300);
         re = read(fd,buffer,300);
        if (re == 0)
                return;
        value = "";
        for (i=0;i < re;i++)
        {
            //value += QString::number(buffer[i],16) + " ";
            value.append(buffer[i]);
        }
        ui->textEdit->append(value);
     }
}

void Uart::on_pushButton_clean_clicked()
{
    value = "";
    ui->textEdit->setText(value);
}

void Uart::on_repeatCheckBox_clicked()
{
    if (fd <= 0)
        return;
    if (ui->repeatCheckBox->isChecked()) {
        sendTimer.start(ui->repeatTimeLineEdit->text().toInt());
    }
    else
    {
        sendTimer.stop();
        tcflush(fd,TCIOFLUSH);
    }
}


void Uart::on_pushButton_open_clicked()
{
    //static int cli_flag = 0;
    int re;
    int tmp;
    int comport = 0,baudrate = 0,nbit = 0, nstop = 0;
    char parity;

    if (ui->pushButton_open->text() == "close")
    {
        if (testTimer.isActive())
        {
            testTimer.stop();
        }
        if (sendTimer.isActive())
        {
            sendTimer.stop();
        }
            tcflush(fd, TCIOFLUSH);
          ::close(fd);
    //      cli_flag = 0;
          value = "open";
          ui->pushButton_open->setText(value);
            return;
    }

    tmp = ui->portNameComboBox->currentIndex();
    switch(tmp)
    {
        case 0: comport = 2; break;
        case 1: comport = 3; break;
        case 2: comport = 4; break;
        case 3: comport = 5; break;
        //case 4: comport = 5; break;
    }
    tmp = ui->baudRateComboBox->currentIndex();
    switch(tmp)
    {
        case 0: baudrate = 1200; break;
        case 1: baudrate = 2400; break;
        case 2: baudrate = 4800; break;
        case 3: baudrate = 9600; break;
        case 4: baudrate = 19200; break;
        case 5: baudrate = 38400; break;
        case 6: baudrate = 57600; break;
        case 7: baudrate = 115200; break;
    }
    tmp = ui->dataBitsComboBox->currentIndex();
    switch(tmp)
    {
        case 0: nbit = 8; break;
        case 1: nbit = 8; break;
    }
    tmp = ui->stopBitsComboBox->currentIndex();
    switch(tmp)
    {
        case 0: nstop = 1; break;
        case 1: nstop = 2; break;
    }
    parity = 'N';
    tmp = ui->parityComboBox->currentIndex();
    switch(tmp)
    {
        case 0 : parity = 'N';break;
        case 1 : parity = 'O';break;
        case 2 : parity = 'E';break;
    }

    if((fd=open_uart_port(fd,comport))<0)
    {
        fd  = 0;
        printf("open fail\n");
        return;
    }
    re = set_uart_opt(fd,baudrate,nbit,parity,nstop);
    if (re < 0 )
    {
        ::close(fd);
        fd = 0;
    }
    else
    {
        value = "close";
        ui->pushButton_open->setText(value);
    }
}
