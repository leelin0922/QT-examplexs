# SBC-7112S-FullTest-Qt4.8.5 Example

## 一、说明

* 在阅读该源代码之前，请确保您已经阅读了以下两篇文档：
 * [《SBC-7112S-Linux3.0.35-Qt4.8.5 Quick Start Guide》](https://github.com/AplexOS/zh-cmn-Hans/blob/SBC-7112S-Linux3.0.35-Qt4.8.5-BSP/Quick_Start_Guide.md)
 * [《SBC-7112S-Linux3.0.35-Qt4.8.5 User's Guide》](https://github.com/AplexOS/zh-cmn-Hans/blob/SBC-7112S-Linux3.0.35-Qt4.8.5-BSP/User's_Guide.md)
* 您作为本文档的阅读者，我们将假定您已经具备如下技能：
 * 了解[Linux文件系统架构](http://www.tldp.org/LDP/intro-linux/html/sect_03_01.html)；
 * 熟悉并掌握[Qt 4.8.5编码规范](http://doc.qt.io/qt-4.8/)；
 * 对Linux ARM交叉编译开发流程熟悉；
 * 能够使用[Qt Creator](http://doc.qt.io/qtcreator/)；

## 二、原理

### 2.1 背光调节示例

* 背光设备节点：`/sys/class/backlight/pwm-backlight.1/brightness`；
* 背光值范围`0~248`，这里是字符串；
* 将`0~248`范围内的字符串写入上面的背光设备节点内，就会设置背光亮度；
* 请参考源代码：[src/backlight/backlight.cpp](src/backlight/backlight.cpp)。

### 2.2 蜂鸣器示例

* 蜂鸣器设备节点：`/dev/buzzer`；
* 背光值范围`0~20000`Hz；
* 如下是设置频率的代码：
```C++
    void Buzzer::set_buzzer_freq(int freq)
    {
        int ret = ioctl(fd, PWM_IOCTL_SET_FREQ, freq);
        if(ret < 0){
            perror("set the frequency of the buzzer");
            exit(1);
        }
    }
```
* 请参考源代码：[src/buzzer/buzzer.cpp](src/buzzer/buzzer.cpp)。

### 2.3 GPIO示例

* 4个GPIO input，4个GPIO output；
* GPIO设备节点：`/dev/gpio_aplex`
* 请参考源代码：[src/gpio/myGpio.cpp](src/gpio/myGpio.cpp)。

### 2.4 UART示例

* 设备节点名：`ttymxc*`；
* 使用标准的Linux [UART](http://www.tldp.org/HOWTO/Serial-HOWTO.html)驱动，采用常用的Linux UART配置方式即可；
* 请参考源代码：[src/uart/uart.cpp](src/uart/uart.cpp)

### 2.5 CAN示例

* 设备是网络设备：`can0`；
* 使用标准的Linux [SocketCAN](https://en.wikipedia.org/wiki/SocketCAN)通信协议；
* 请参考源代码：[src/can/canTest.cpp](src/can/canTest.cpp)

### 2.6 Watchdog示例

* 设备节点名：`/dev/watchdog`；
* 使用标准的Linux [Watchdog](https://www.kernel.org/doc/Documentation/watchdog/watchdog-api.txt)通信协议；
* 请参考源代码：[src/watchdog/watchdog.cpp](src/watchdog/watchdog.cpp)

### 2.7 其实程序示例说明

除了以上可能比较特殊的控制设备之外，其他的设备，均是采用标准的Linux设备驱动。

## 三、源代码说明

* 源代码在[`src`](src)目录；
* 源代码Qt版本是`4.8.5`；

## 四、版权说明

以上所有内容最终解释权归[aplex](http://www.aplextec.com/cn/home.php)公司所有。

