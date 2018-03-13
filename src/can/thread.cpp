#include "thread.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include "canTest.h"
#include <QDebug>

Thread::Thread(int recsocket,QObject *parent) :
    QThread(parent)
{
    recive_socket  = recsocket;
    running = true;
}

void Thread::run()
{
    int nbytes;
    //int len;
    struct can_frame frame;
    //struct sockaddr_can addr;
    char buf[32];

    while(running)
    {
         //recvfrom(recive_socket,&frame,sizeof(struct can_frame),0,(struct sockaddr *)&addr,(socklen_t*)&len);
         nbytes = ::read(recive_socket, &frame, sizeof(struct can_frame));
         if(nbytes < 0){
            qDebug() << "Error! while writting can raw socket";
         }
         //if(nbytes<=0)
         //    continue;
         memset(buf,0,sizeof(buf));
         strncpy(buf,(char*)frame.data,8);
         emit msg(QString(buf));
    }

}

void Thread::stop()
{
    running = false;
}
