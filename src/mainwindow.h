#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>

#define		SBC7112_ONOFF
#define		SBC7112_BURNCPU
#define		SBC7112_INFO
#define		SBC7112_GPIO
#define		SBC7112_BUZZER
#define		SBC7112_RTC
#define		SBC7112_BACKLIGHT
#define		SBC7112_EEPROM
#define		SBC7112_NETWORK
#define		SBC7112_PING
#define		SBC7112_USB
#define		SBC7112_CAN
//#define		SBC7112_SD
#define		SBC7112_UART
#define		SBC7112_WATCHDOG
#define		SBC7112_VERSION
//#define		SBC7112_SPI
#define     SBC7112_AUDIO
#define     SBC7112_COM_MODE
#define     SBC7112_EMMC_ERASE

//#define 	SBC7109_LED
//#define	SBC7109_AUDIO

#ifdef	SBC7112_ONOFF
#include "./onoff/onoff.h"
#endif

#ifdef	SBC7112_BURNCPU
#include "./burncpu/burnCpu.h"
#endif

#ifdef	SBC7112_INFO
#include "./info/info.h"
#endif

#ifdef	SBC7109_LED
#include "./led/led.h"
#endif

#ifdef	SBC7112_GPIO
#include "./gpio/myGpio.h"
#endif

#ifdef	SBC7112_BUZZER
#include "./buzzer/buzzer.h"
#endif

#ifdef	SBC7112_BACKLIGHT
#include "./backlight/backlight.h"
#endif

#ifdef	SBC7112_EEPROM
#include "./eeprom/eeprom.h"
#endif

#ifdef	SBC7112_NETWORK
#include "./network/network.h"
#endif

#ifdef	SBC7112_PING
#include "./ping/ping.h"
#endif

#ifdef	SBC7112_USB
#include "./usb/usb.h"
#endif

#ifdef	SBC7112_SD
#include "./SD/sd.h"
#endif

#ifdef	SBC7112_UART
#include "./uart/uart.h"
#endif

#ifdef	SBC7112_WATCHDOG
#include "./watchdog/watchdog.h"
#endif

#ifdef	SBC7112_CAN
#include "./can/canTest.h"
#endif

#ifdef	SBC7112_AUDIO
#include "./audio/audio.h"
#endif

#ifdef	SBC7112_RTC
#include "./rtc/rtcTest.h"
#endif

#ifdef	SBC7112_SPI
#include "./spi/spi.h"
#endif

#ifdef     SBC7112_COM_MODE
#include "./com_mode/com_mode.h"
#endif

#ifdef	SBC7112_VERSION
#include "./version/version.h"
#endif

#ifdef  SBC7112_EMMC_ERASE
#include "./emmc_erase/emmc_erase.h"
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QTabWidget *tabWidget;
    void updateSizes(int index);

public:

#ifdef	SBC7112_ONOFF
    Onoff *onoff;
#endif

#ifdef	SBC7112_BURNCPU
    BurnCpu *burncpu;
#endif

#ifdef	SBC7112_INFO
    Info *info;
#endif

#ifdef	SBC7109_LED
    Led *led;
#endif

#ifdef	SBC7112_GPIO
    MyGpio *gpio;
#endif

#ifdef	SBC7112_BUZZER
    Buzzer *buzzer;
#endif

#ifdef	SBC7112_BACKLIGHT
    Backlight *backlight;
#endif

#ifdef	SBC7112_EEPROM
    Eeprom *eeprom;
#endif

#ifdef	SBC7112_NETWORK
    Network *network;
#endif

#ifdef	SBC7112_PING
    Ping *ping;
#endif

#ifdef	SBC7112_RTC
    RtcTest *rtc;
#endif

#ifdef	SBC7112_USB
    Usb *usb;
#endif

#ifdef	SBC7112_SD
    Sd *sd;
#endif

#ifdef  SBC7112_COM_MODE
    Com_mode *com_mode;
#endif

#ifdef	SBC7112_UART
    Uart *uart;
#endif

#ifdef	SBC7112_WATCHDOG
    Watchdog *watchdog;
#endif

#ifdef	SBC7112_CAN
    CanTest *can;
#endif

#ifdef	SBC7112_AUDIO
    Audio *audio;
#endif

#ifdef	SBC7112_SPI
    Spi *spi;
#endif

#ifdef  SBC7112_EMMC_ERASE
    Emmc_erase *pEmmc_erase;
#endif

#ifdef	SBC7112_VERSION
    version *version1;
#endif

private slots:
//    void on_tabWidget_currentChanged(QWidget *arg1);

//    void on_tabWidget_currentChanged(int index);

//    void on_tabWidget_selected(const QString &arg1);

//    void on_tabWidget_tabCloseRequested(int index);

//    void on_tabWidget_destroyed();

//    void on_tabWidget_destroyed(QObject *arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
