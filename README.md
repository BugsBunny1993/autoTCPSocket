autoTCPSocket
=============
 Summary:
 
    this class is light weight and grab low level POSIX Socket API
used for socket (TCP) connection. all method are sync. and only support
 IPv4 protocal. timeout was set to 75 sec by BSD system defualt value.
 
                                        --by Kowalski
 

简介：
      
       这个API对底层的POSIX套接字做了简单的封装，可以很方便的进行TCP套接字通信，所有的方法都是同步的，目前只支持IPv4协议，超时为BSD系统默认为75秒钟，任何问题请参考 UNIX网络编程一书，任何API调用查看头文件。


                                     -- 科沃斯基  QQ:547098469

功能：

1. 连接到一个目标主机已知IP和端口
2. 连接到一个目标主机已知URL和端口
3. 发送和接收信息
4. 查看已连接目标主机的IP和端口
5. 启动一个简单的TCP 服务端，


项目启动后，单击界面右下角的圆形退出按钮即可启动服务器，
在浏览器地址栏中输入 127.0.0.1:3456 回车， 
控制台即刻输出浏览器的请求头。

支持: 所有的类UNIX系统包括MacOS X，Linux，Android，iOS等
不支持: Microsoft Windows 
