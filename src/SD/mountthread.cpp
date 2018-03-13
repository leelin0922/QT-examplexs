#include "mountthread.h"

MountThread::MountThread(QString exsdNode, QString mountNode, QObject *parent) :
    QThread(parent)
{
    /* 获取sd卡设备节点，mount需要挂载到的文件系统节点 */
    this->exsdNode = exsdNode;
    this->mountNode = mountNode;
}

void MountThread::run()
{
    /* 发送开始mount信号 */
    emit preMount( PRE_MOUNT );

    QFileInfo fileInfo( exsdNode );
    if( fileInfo.exists() ) {

        /**
         * 1. 先卸载一下，保证当前次挂载
         * 2. 重新挂载在目标文件节点上
         * 3. 等待一下，这里貌似可以不等待的，没有理由  :)
         */
        system( QString( "umount " ).append( exsdNode ).toLocal8Bit() );
        system( QString( "mount " ).append( exsdNode ).append( " " ).append( mountNode ).toLocal8Bit() );
        msleep( SLEEP_DELAY_MS );

    } else {
        /* 设备节点不存在，弹出提示框 */
        // QMessageBox::warning(NULL, "WARNING", "Please check your SD card has plugin slot.");
        emit deviceUnExist(DEVICE_UNEXIST);
    }

    /* 发送结束mount信号 */
    emit postMount( POST_MOUNT );
}
