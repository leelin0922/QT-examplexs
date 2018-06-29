#include "sd.h"
#include "ui_sd.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <QFileInfo>
#include <QMessageBox>
#include <QTreeView>
#include <QDebug>

/* sd卡生成的设备节点 */
#define EXSD_NODE             "/dev/mmcblk1p1"
/* sd卡挂载的文件系统节点 */
#define MOUNT_NODE            "/mnt/exsd"

Sd::Sd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sd)
{

    ui->setupUi(this);

    /**
     * 这里主要是设置treeview的一些参数
     */
    ui->showDir->setModel( &model );
    model.setRootPath( MOUNT_NODE );
    ui->showDir->setRootIndex( model.index( MOUNT_NODE ) );

    // Demonstrating look and feel features
    ui->showDir->setAnimated( false );
    ui->showDir->setIndentation( 20 );
    ui->showDir->setSortingEnabled( true );
    ui->showDir->setColumnWidth( 0, 250 );

    /**
     * 1. 创先mount线程；
     * 2. 绑定信号与槽。
     */
    mountThread = new MountThread( EXSD_NODE, MOUNT_NODE );
    connect( mountThread, SIGNAL(preMount(int)), this, SLOT(dealwithUi(int)) );
    connect( mountThread, SIGNAL(postMount(int)), this, SLOT(dealwithUi(int)) );
    connect( mountThread, SIGNAL(deviceUnExist(int)), this, SLOT(dealwithUi(int)) );

}

void Sd::dealwithUi(int mesg)
{
    if( MountThread::PRE_MOUNT == mesg ) {

        /* 将button设置为无效效果 */
        ui->detectButton->setEnabled( false );
        ui->umountButton->setEnabled( false );

        qDebug() << "premount." << endl;

    } else if ( MountThread::POST_MOUNT == mesg ) {

        /**
         * 1. 这里一定需要:
         *        model.setRootPath( "/mnt" );
         *     model.setRootPath( MOUNT_NODE );
         * 2. /mnt不是固定的，随便什么值都行，这里主要是为了触发rootPath改变了，在设置回来,
         *        要不然，treeview不会显示。
         */
        model.setRootPath( "/mnt" );
        model.setRootPath( MOUNT_NODE );
        ui->showDir->setRootIndex( model.index( MOUNT_NODE ) );

        /* 恢复按钮有效效果 */
        ui->detectButton->setEnabled( true );
        ui->umountButton->setEnabled( true );

        qDebug() << "postmount." << endl;

    } else if (MountThread::DEVICE_UNEXIST == mesg ) {
        QMessageBox::warning(this, "WARNING", "Please check your SD card has plugin slot.");
    }
}

void Sd::on_detectButton_clicked()
{
    /**
     * 1. 开启线程，看似无关紧要的，只有短短一行，却包暗含着UI线程与普通线程的区别；
     * 2. UI线程维护UI界面的更新；
     * 3. UI界面不宜做时间很长、耗费资源的事；
     * 4. 普通线程通过发送信号与UI线程进行沟通，处理UI显示更新。
     */
    mountThread->start();
}

void Sd::on_umountButton_clicked()
{
    /* 卸载sd卡 */
    system( QString( "umount " ).append( EXSD_NODE ).toLocal8Bit() );
}

Sd::~Sd()
{
    delete ui;
}
void Sd::moveEvent(QMoveEvent *)
{
    this->move( QPoint( 0, 0 ) );
}

void Sd::resizeEvent(QResizeEvent *)
{
    this->showMaximized();
}

void Sd::closeEvent(QCloseEvent *)
{
    exit(0);
}
