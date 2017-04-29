# 数据加密聊天软件demo
## 简介
实现了局域网内聊天软件的demo，可注册用户、添加好友、聊天、
发送文件。主要的难点是从基础开始实现[3DES][1]和[NSSK][0]协议。
前者用于加密聊天的记录和文件数据，后者用于通信双方建立连接时
交换通信秘钥。

3DES的核心代码在[src/kernel/DES.java][2]，NSSK协议的核心代码在
[src/server/Dispatcher.java][3]。

## 界面截图
### GUI界面
![gui][4]

### 控制台界面
![cli][5]

## 开发平台
- Eclipse Mars.1 Release(4.5.1)
- JDK 1.8.0_20
- 数据库 MariaDB10.1
- 操作系统 Window 10

[0]: https://en.wikipedia.org/wiki/Needham%E2%80%93Schroeder_protocol
[1]: https://en.wikipedia.org/wiki/Triple_DES
[2]: src/kernel/DES.java
[3]: src/server/Dispatcher.java
[4]: images/gui.png
[5]: images/cli.png