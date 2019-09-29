/****************************************************************
* @project     localsocket
* @brief         摘要
* @author      kevin.yang
* @email        jhonconal2016@gmail.com
* @date          2019-05-20
* Conttact:     jhonconal2016@gmail.com
* Copyright (c) 2019 jhonconal or its subsidiary.
****************************************************************/
#ifndef _LOCAL_SOCKET_CLIENT_H
#define _LOCAL_SOCKET_CLIENT_H

#include <cutils/sockets.h>
// #include <cutils/socket_local.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stddef.h>

#define  LOCALSOCKET_PATH   "defined-socket"

#if 1
#include <android/log.h>
#define LOG_TAG "localsocket"
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))
#else
#define LOGD  printf;
#define LOGI  	printf;
#define LOGW  printf;
#define LOGE  	printf;
#endif

void *callback_func(void *arg)
{
    char rcvbuf[1024] = {
        0,
    };
    char sndbuf[1024] = {
             0,
    }; //read/write buffer
    int sockfd,n;
    while(1)
    {
         sockfd = socket_local_client(LOCALSOCKET_PATH,ANDROID_SOCKET_NAMESPACE_ABSTRACT,SOCK_STREAM);
        if(sockfd<0)
        {
            LOGE("(Client)///[%s]<%d>socket_local_client error: %s\n",__func__,__LINE__,strerror(errno));
            close(sockfd);
            sockfd  =-1;
            continue;
        }
        LOGD("(Client)///You have connected to server :%d\n",sockfd);
        while(1)
        {
            bzero(rcvbuf,sizeof(rcvbuf));
            n = read(sockfd,rcvbuf,sizeof(rcvbuf));
            if(n<0)
            {
                LOGE("(Client)///[%s]<%d>The other side has been closed : %s.\n",__func__,__LINE__,strerror(errno));  
                close(sockfd);
                sockfd =-1;
                break;
            }
            else
            {
                LOGD("(Client)///Get buffer from server : %s \n",rcvbuf);
                bzero(sndbuf,sizeof(sndbuf));
                sprintf(sndbuf,"[ACK]: %s",rcvbuf);
                n = write(sockfd,sndbuf,(int)strlen(sndbuf));
                if(n<=0)
                {
                    LOGE("(Client)///Write Ack to Server Failed...\n");
                }
            }
        }
    }
}

int
main(int argc,char*argv[])
{
#if  1
    callback_func(NULL);
#endif
	return 0;
}

#endif 