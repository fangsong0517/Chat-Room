# Chat-Room
简易聊天室

# 介绍

运行在linux上的简易聊天室，可支持多人聊天和私聊

# 运行环境

项目运行在linux系统上

# 安装

```html
git clone https://gitee.com/fgsong/Chat-Room.git
```

# 使用方法

可自定义server和client文件中的配置文件server.conf和client.conf

```bash
cd Char-Room
vim ./server/server.conf
```

自行修改：

```
SERVER_PORT=8888
```

```bash
vim ./client/client.conf
```

自行修改：

```
SERVER_IP=192.168.43.5 #自行修改server端的IP地址
SERVER_PORT=8888
MY_NAME=fangsong
LOG_FILE=./chat.log #聊天日志
```

然后执行进行编译：

```bash
cd ./server
./G
cd ../client
./G
```

安装完毕后，执行一下以下命令就可以启动该项目 （先启动服务端然后启动客户端）

```bash
cd ./server
./server
```

打开另一个终端：

```bash
cd Char-Room/client
./client
```

当发送信息为：

```
#1        #1获取当前在线人数
@name     #进行与名为name的进行私聊（默认为公聊）
ctrl + C  #退出聊天室
```

当你想获取全部信息时可以打开文件夹char.log进行查看

# TODO

封装图形化界面，将filetramsfer中的文件传输整合在项目中...

