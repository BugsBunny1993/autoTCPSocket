//
//  autoTCP.h
//  autoTCP
//
//  Created by Kowalski on 1/6/14.
//
//

#ifndef __autoTCP__autoTCP__
#define __autoTCP__autoTCP__

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "cocos2d.h"
USING_NS_CC;
/*
 
 Summary:
 
    this class is light weight and grab low level POSIX Socket API
used for socket (TCP) connection. all method are sync. and only support
 IPv4 protocal. timeout was set to 75 sec by BSD system defualt value.
 
                                        --by Kowalski
 
 */
class autoTCPSocket{
    unsigned int m_socket;
    bool turnOn();
  
public:
    //autoTCPSocket* sock=new autoTCPSocket();
    
    //connect to a remote IP address that must IPv4
    // ip:   "127.0.0.1"  or  "222.242.98.76"
    //port:   target port 0<port<65535
    //return: ture if sucssed otherwise false
    bool turnOnWithIP(const char* ip,unsigned short port);
    
    //connect to a remote IP address that DNS server give to me when we ask a URL.
    //url:  "www.google.com.hk"  or  "pc.qq.com"
    //port: target port 0<port<65535
    //return: ture if sucssed otherwise false
    bool turnOnWithURL(const char* url,unsigned short port);
    
    //set to a socketFD that alreay connected, you don't have to call this
    //becos this is call by autoTCPServerSocket
    bool turnOnWithSocket(int socketFD);
    
    
    //get remote port
    unsigned short getRemotePort();
    
    //get remote IP
    //return "222.242.123.123"
    char* getRemoteIP();
    
    //send data
    //buf:  char[] or something
    //len: how many bytes of data will send to
    //return:ture if all data was sended otherwise will be false
    bool sendData(void* buf,unsigned long len);
    
    //read data
    //buf: get a container that will fill with data.
    //len: how many bytes of data you wannt.
    //wait: if ture method always wait untill
    //        1.got all the data you ask for
    //        2.catch a singnal
    //        3.connection borken
    //      if false method will return as soon. but maybe less data than you want,so you need call this one more time.
    //return: >0 length of data recived. or 0 no more data. or -1 error
    long recvData(void* buf,unsigned long len,bool wait);
    
    
    //shutdown both read and write then close socket.
    //one or more error can appare on console when aother point not call shutdown.
    //you don't have to care the error
    void turnOff();
    ~autoTCPSocket();
    

};

class autoTCPServerSocket{
    unsigned int m_s_socket;
public:
    
    //start a TCP server listen on a local port
    //port:  1024<port<65535
    //return : ture if sucssed othwise will be false
    bool turnOnWithPort(unsigned short port);
    
    //wait untill some one connected in
    //return a autoTCPSocket object
    //  after connection you shall call CC_SAFE_DELETE( autoTCPSocket )
    autoTCPSocket* acceptSocketIn();
    
    
    
    ~autoTCPServerSocket();
};

#endif /* defined(__autoTCP__autoTCP__) */
