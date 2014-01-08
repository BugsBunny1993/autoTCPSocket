//
//  autoTCP.cpp
//  autoTCP
//
//  Created by Kowalski on 1/6/14.
//
//

#include "autoTCP.h"

bool autoTCPSocket::turnOn(){
    int sockid= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockid==-1) {
        CCLog("autoTCP: create POSIX socket fail");
        return false;
    }else{
        m_socket=sockid;
        return true;
    }
}

bool autoTCPSocket::turnOnWithIP(const char *ip, unsigned short port){
    if (this->turnOn()==false) {
        return false;
    }
    struct sockaddr_in address;
    
    unsigned int raw_ip_address=inet_addr(ip);
    if (raw_ip_address==INADDR_NONE) {
        CCLog("autoTCP: IP address format error");
        return false;
    }
    
    address.sin_addr.s_addr=raw_ip_address;
    address.sin_family=AF_INET;
    address.sin_port=htons(port);
    
    int connect_result=connect(m_socket, (sockaddr*)&address, sizeof(address));
    if (connect_result==-1) {
        CCLog("autoTCP: connect to %s:%u fail",ip,port);
        return false;
    }
    return true;
}

bool autoTCPSocket::turnOnWithSocket(int socketFD){
    if (!socketFD||socketFD==-1) {
        CCLog("autoTCP: socketFD must be none zero number!");
        return false;
    }
    m_socket=socketFD;
    return true;
}

bool autoTCPSocket::turnOnWithURL(const char *url, unsigned short port){
    hostent *ip_addr;
    ip_addr=gethostbyname(url);
    if (ip_addr==NULL) {
        CCLog("autoTCP: can't solve this URL:%s",url);
        return false;
    }
    
    CCString *addr_info=CCString::createWithFormat("%u.%u.%u.%u",
                                                   (unsigned char)ip_addr->h_addr_list[0][0],
                                                   (unsigned char)ip_addr->h_addr_list[0][1],
                                                   (unsigned char)ip_addr->h_addr_list[0][2],
                                                   (unsigned char)ip_addr->h_addr_list[0][3]);
    if(this->turnOnWithIP(addr_info->getCString(), port)==false){
        return false;
    }
    return true;
}

unsigned short autoTCPSocket::getRemotePort(){
    struct sockaddr_in local_addr;
    socklen_t size=sizeof(local_addr);
        if(getpeername(m_socket, (sockaddr*)&local_addr, &size)==-1){
            CCLog("autoTCP: can't get Remote port");
                return -1;
        }
    return ntohs(local_addr.sin_port);
}

char* autoTCPSocket::getRemoteIP(){
    struct sockaddr_in local_addr;
    socklen_t size=sizeof(local_addr);
        if(getpeername(m_socket, (sockaddr*)&local_addr, &size)==-1){
            CCLog("autoTCP: can't get Remote IP");
            return NULL;
        }
    return inet_ntoa(local_addr.sin_addr);
}

bool autoTCPSocket::sendData(void *buf,unsigned long len){
    if(send(m_socket, buf, len, 0)<0){
        CCLog("autoTCP: send fail");
        return false;
    }
    return true;
}

long autoTCPSocket::recvData(void *buf, unsigned long len,bool wait){
    return recv(m_socket, buf, len , wait?MSG_WAITALL:0x0);
}

void autoTCPSocket::turnOff(){
    if(shutdown(m_socket, SHUT_RDWR)<0){
        CCLog("autoTCP: shutdown error !");
    }
    if(close(m_socket)<0){
        CCLog("autoTCP: close error !");
    }
}

autoTCPSocket::~autoTCPSocket(){
    turnOff();
}

bool autoTCPServerSocket::turnOnWithPort(unsigned short port){
    int sockid= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockid==-1) {
        CCLog("autoTCPServer: create POSIX socket fail");
        return false;
    }
    m_s_socket=sockid;
    struct sockaddr_in localAdd;
    localAdd.sin_addr.s_addr=htonl(INADDR_ANY);
    localAdd.sin_family=AF_INET;
    localAdd.sin_port=htons(port);
    if(bind(m_s_socket, (sockaddr*)&localAdd, sizeof(localAdd))<0){
        CCLog("autoTCPServer: can't bind to local port %u ",port);
        return false;
    }
    
    if(listen(m_s_socket, 20)<0){
        CCLog("autoTCPServer: can't listen I don't know why");
        return false;
    };
    return true;
}

autoTCPSocket* autoTCPServerSocket::acceptSocketIn(){
   unsigned int socketFD =accept(m_s_socket, NULL, NULL);
    autoTCPSocket *soc=new autoTCPSocket();
    soc->turnOnWithSocket(socketFD);
    return soc;
}

autoTCPServerSocket::~autoTCPServerSocket(){
    if(shutdown(m_s_socket, SHUT_RDWR)<0){
        CCLog("autoTCPServer: shutdown error !");
    }
    if(close(m_s_socket)<0){
        CCLog("autoTCPServer: close error !");
    }
}
