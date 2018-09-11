# urpc_release
a RPC lib by UDP socket

目录说明：
1，include目录是存在的头文件；
2,lib目录是存放的动态依赖库；
3，test目录是测试示例目录，包括客户端和服务端；
4，bin目录是用来生成可执行文件的存放目录。


编译环境准备：
1, 进入urpc_release 目录
2，执行source setenv.sh

编译：
1, cd test
2，make

运行：
1，打开两个shell窗口，分别进入到urpc_release 目录并执行source setenv.sh；
2，进入bin目录；
3，一个窗口启动server端，执行./urpc_server_test
4，另外一个窗口启动client端，执行./urpc_client_test  $(server_ip)  $(server_port)

其中server_ip指server端的ip地址，如果是同一台机器，指定127.0.0.1即可；server_port指server监听的端口，这里默认是7895.

