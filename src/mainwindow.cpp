#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QGroupBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#ifdef	SBC7112_ONOFF
    onoff = new Onoff();
    ui->tabWidget->addTab(onoff, "On/Off test");
#endif

#ifdef	SBC7112_BURNCPU
    burncpu = new BurnCpu();
    ui->tabWidget->addTab(burncpu, "burncpu");
#endif

#ifdef  SBC7112_INFO
    info = new Info();
    ui->tabWidget->addTab(info, "info");
#endif

#ifdef SBC7109_LED
    led = new Led();
    ui->tabWidget->addTab(led, "led");
#endif

#ifdef  SBC7112_GPIO
    gpio = new MyGpio();
    ui->tabWidget->addTab(gpio, "gpio");
#endif

#ifdef  SBC7112_BUZZER
    buzzer = new Buzzer();
    ui->tabWidget->addTab(buzzer, "buzzer");
#endif

#ifdef  SBC7112_BACKLIGHT
    backlight = new Backlight();
    ui->tabWidget->addTab(backlight, "backlight");
#endif

#ifdef  SBC7112_EEPROM
    eeprom = new Eeprom();
    ui->tabWidget->addTab(eeprom, "I2C");
#endif

#ifdef  SBC7112_SPI
    spi = new Spi();
    ui->tabWidget->addTab(spi, "spi");
#endif

#ifdef  SBC7112_NETWORK
    network = new Network();
    ui->tabWidget->addTab(network, "network");
#endif

#ifdef  SBC7112_PING
    ping= new Ping();
    ui->tabWidget->addTab(ping, "ping");
#endif

#ifdef  SBC7112_RTC
    rtc = new RtcTest();
    ui->tabWidget->addTab(rtc, "rtc");
#endif

#ifdef  SBC7112_USB
    usb = new Usb();
    ui->tabWidget->addTab(usb, "usb");
#endif

#ifdef  SBC7112_SD
    sd = new Sd();
    ui->tabWidget->addTab(sd, "SD");
#endif

#ifdef  SBC7112_CAN
    can = new CanTest();
    ui->tabWidget->addTab(can, "can");
#endif

#ifdef  SBC7112_COM_MODE
    com_mode= new Com_mode();
    ui->tabWidget->addTab(com_mode, "COM Mode Select");
#endif

#ifdef  SBC7112_UART
    uart= new Uart();
    ui->tabWidget->addTab(uart, "uart");
#endif

#ifdef  SBC7112_WATCHDOG
    watchdog = new Watchdog();
    ui->tabWidget->addTab(watchdog, "watchdog");
#endif

#ifdef  SBC7112_AUDIO
    audio= new Audio();
    ui->tabWidget->addTab(audio, "audio");
#endif

#ifdef  SBC7112_EMMC_ERASE
    pEmmc_erase = new Emmc_erase();
    ui->tabWidget->addTab(pEmmc_erase,"EMMC Erase");
#endif

#ifdef  SBC7112_VERSION
    version1 = new version();
    ui->tabWidget->addTab(version1,"version");
#endif

}

MainWindow::~MainWindow()
{
#ifdef	SBC7112_ONOFF
    delete onoff;
#endif

#ifdef	SBC7112_BURNCPU
    burncpu = new BurnCpu();
    delete burncpu;
#endif

#ifdef		SBC7109_LED
    delete led;
#endif

#ifdef		SBC7112_BUZZER
    delete buzzer;
#endif

#ifdef		SBC7112_BACKLIGHT
    delete backlight;
#endif

#ifdef		SBC7112_EEPROM
    delete eeprom;
#endif

#ifdef		SBC7112_SPI
    delete spi;
#endif

#ifdef		SBC7112_NETWORK
    delete network;
#endif

#ifdef		SBC7112_PING
    delete ping;
#endif

#ifdef		SBC7112_RTC
    delete rtc;
#endif

#ifdef		SBC7112_USB
    delete usb;
#endif

#ifdef		SBC7112_SD
    delete sd;
#endif

#ifdef  SBC7112_COM_MODE
    delete com_mode;
#endif
#ifdef		SBC7112_UART
    delete uart;
#endif

#ifdef		SBC7112_WATCHDOG
    delete watchdog;
#endif

#ifdef		SBC7112_CAN
    delete can;
#endif

#ifdef		SBC7112_AUDIO
    delete audio;
#endif

#ifdef		SBC7112_VERSION
    delete version1;
#endif

    delete ui;
}
