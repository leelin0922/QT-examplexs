#ifndef MOUNTTHREAD_H
#define MOUNTTHREAD_H

#include <QThread>
#include <QString>
#include <QMessageBox>
#include <QFileInfo>

/**
 * @brief The MountThread class
 * 挂载文件系统线程，需要创建这个线程的原因如下：
 *     1. 当mountSD按钮被按下的时候，需要使按钮处于无效状态；
 *     2. 当SD卡文件系统挂载完毕时，按钮要处于有效状态；
 *     3. 这么做主要是防止一些误操作，或者也可当作为一种状态提示；
 *     4. 基于以上原因，就出现了preMount()、postMount()这两个信号；
 *     5. preMount()在处理mount之前发出的信号，UI线程可以更新按钮到无效状态；
 *     6. postMout()在处理mount之后发出的信号，UI先生可以更新按钮到有效状态；
 *
 * 其实之所以要这么做，是因为如果这些在UI线程中做，一般在一个函数里完成，UI线程采用
 * 从上到下的程序执行流程，无法更新UI控件的状态，所以目前只能采用这种方式来做。
 */
class MountThread : public QThread
{
    Q_OBJECT
public:
    /**
     * @param exsdNode         扩展sd卡生成的设备节点
     * @param mountNode        要将sd卡挂载到那个文件系统节点上
     * @param parent
     */
    explicit MountThread(QString exsdNode, QString mountNode, QObject *parent = 0);

    /**
     * 信号通过传参的方式，后续由UI线程dealWithUi()槽统一处；
     */
    static const int PRE_MOUNT       = 1;
    static const int POST_MOUNT      = 2;
    static const int DEVICE_UNEXIST  = 3;
    /**
     * @brief SLEEP_DELAY_MS
     * 设置mount后等待的时间，这里其实可以不需要，但是本人还是设置了，没有原因   :)
     */
    static const int SLEEP_DELAY_MS = 1000;

signals:
    void preMount(int mesg);
    void postMount(int mesg);
    void deviceUnExist(int mesg);

private:
    /**
     * 重写run方法
     */
    void run();

private:
    /**
     * 扩展sd卡生成的设备节点
     */
    QString exsdNode;
    /**
     * 要将sd卡挂载到那个文件系统节点上
     */
    QString mountNode;
};

#endif // MOUNTTHREAD_H
