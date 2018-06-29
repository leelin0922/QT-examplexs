#-------------------------------------------------
#
# Project created by QtCreator 2016-06-20T17:31:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = utils
target.files = utils
target.path = /usr/bin/
INSTALLS += target

TEMPLATE = app

SOURCES += main.cpp\
    mainwindow.cpp \
    qipaddressedit.cpp \
    qipaddressedititem.cpp \
    led/led.cpp \
    onoff/onoff.cpp \
    buzzer/buzzer.cpp \
    ping/ping.cpp \
    usb/usb.cpp \
    SD/sd.cpp \
    uart/uart.cpp \
    watchdog/watchdog.cpp \
    can/thread.cpp \
    can/canTest.cpp \
    audio/audio.cpp \
    backlight/backlight.cpp \
    rtc/rtcTest.cpp \
    info/info.cpp \
    burncpu/burnCpu.cpp \
    gpio/myGpio.cpp \
    eeprom/i2c.cpp \
    eeprom/eeprom.cpp \
    SD/mountthread.cpp \
    version/version.cpp \
    spi/spi.cpp \
    burncpu/parser.cpp \
    com_mode/com_mode.cpp \
    burncpu/runthread.cpp \
    emmc_erase/emmc_erase.cpp \
    network/interface.cpp \
    network/network.cpp

HEADERS  += mainwindow.h \
    led/led.h \
    qipaddressedit.h \
    qipaddressedititem.h \
    onoff/onoff.h \
    buzzer/buzzer.h \
    ping/ping.h \
    usb/usb.h \
    SD/sd.h \
    uart/uart.h \
    watchdog/watchdog.h \
    can/thread.h \
    can/canTest.h \
    audio/audio.h \
    backlight/backlight.h \
    rtc/rtcTest.h \
    info/info.h \
    burncpu/burnCpu.h \
    gpio/myGpio.h \
    eeprom/i2c.h \
    eeprom/eeprom.h \
    SD/mountthread.h \
    version/version.h \
    spi/spi.h \
    burncpu/parser.h \
    com_mode/com_mode.h \
    burncpu/runthread.h \
    emmc_erase/emmc_erase.h \
    network/interface.h \
    network/network.h

FORMS    += mainwindow.ui \
    led/led.ui \
    onoff/onoff.ui \
    buzzer/buzzer.ui \
    ping/ping.ui \
    usb/usb.ui \
    SD/sd.ui \
    uart/uart.ui \
    watchdog/watchdog.ui \
    can/canTest.ui \
    audio/audio.ui \
    backlight/backlight.ui \
    rtc/rtcTest.ui \
    info/info.ui \
    burncpu/burnCpu.ui \
    gpio/myGpio.ui \
    eeprom/eeprom.ui \
    version/version.ui \
    spi/spi.ui \
    com_mode/com_mode.ui \
    emmc_erase/emmc_erase.ui \
    network/network.ui

OTHER_FILES +=

# deployment on Linux
unix {
    target.path = /usr/bin/
    INSTALLS += target \
}
