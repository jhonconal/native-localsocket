/****************************************************************
* @project     localsocket
* @brief         摘要
* @author      kevin.yang
* @email        jhonconal2016@gmail.com
* @date          2019-05-20
* Conttact:     jhonconal2016@gmail.com
* Copyright (c) 2019 jhonconal or its subsidiary.
****************************************************************/
#ifndef _LOCAL_SOCKET_SERVER_H
#define _LOCAL_SOCKET_SERVER_H

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
    int serverfd,connfd,count;

while(1)
{
    serverfd = socket_local_server(LOCALSOCKET_PATH,ANDROID_SOCKET_NAMESPACE_ABSTRACT, SOCK_STREAM);
    if(serverfd<0)
    {
        LOGE("(Server)///[%s]<%d>Get local socket server error: %s\n",__FILE__,__LINE__,strerror(errno));
        close(serverfd);
        serverfd =-1;
        continue;
    }
    if(listen(serverfd,5)<0)
    {
        LOGE("(Server)///[%s]<%d>Get local socket listen error: %s\n",__FILE__,__LINE__,strerror(errno));
        close(serverfd);
        serverfd = -1;
        continue;
    }
    LOGD("(Server)Get local socket accpeting...\n");
    while(1) 
    {
            connfd = accept(serverfd,NULL,NULL);
            if(connfd<0)
            {
                LOGE("(Server)///[%s]<%d>Get local socket accept error: %s\n",__FILE__,__LINE__,strerror(errno));
                close(connfd);
                connfd =-1;
                continue;
            }
            LOGD("(Server)Get local socket client connected: %d\n",connfd );
            write(connfd,"Hi,Guys you have connect with server.",strlen("Hi,Guys you have connect with server."));
            while(1) 
            {
                memset(rcvbuf, 0, sizeof(rcvbuf));
                count = read(connfd, rcvbuf, sizeof(rcvbuf));
                if (count < 0)
                {
                    LOGE("(Server)///[%s]<%d>Read error :%s\n",__FILE__,__LINE__,strerror(errno));
                    break;
                }
                else if (count == 0)
                {
                    LOGE("(Server)///[%s]<%d>Read error :%s\n",__FILE__,__LINE__,strerror(errno));
                    connfd = -1;
                    break;
                }
                else
                {
                        LOGD("(Server)Get local socket buf from client: %s\n",rcvbuf);
                }
            }
    }
    close(serverfd);
}

int
main(int argc,char*argv[])
{
#if 1
    callback_func(NULL);
#endif
	return 0;
}

#endif 