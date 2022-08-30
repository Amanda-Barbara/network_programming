# 摘要

## 课程计划
1. 围绕通讯架构
2. 讲解`linux`下的`C++`编程细节
3. 以学习`Nginx`源码为主，掌握`epoll`高并发知识点

## 建立知识库
1. 完全理解掌握的代码片段
2. 

## 工具书籍推荐
1. `UNIX`网络编程
2. `TCP/IP`详解

## 基础知识
1. 主动发送数据包的一端成为“客户端”，另一端称为服务器端
2. 在`centos`的`/etc/network/`目录下修改`address/gateway/netmask`字段的值
3. dns是域名解析的作用 `nameserver 8.8.8.8`
4. 使用`ps -e | grep ssh` 查看ssh是否安装成功，列出所有进程并查找
5. 安装gcc(编译c程序)/g++(编译c++程序)
6. sudo apt-get install build-essential #(软件包)
7. 

## docker多容器部署
1. 通过镜像启用多容器
* 创建并启用`nginx0`容器
```shell
cd /home/e00130/workspace/tutorial/network_program/network_programming
docker run --name nginx0 -v $PWD:/network_programming -it --cap-add=SYS_PTRACE ubuntu:20.04 bash
apt-get install inetutils-ping strace vim net-tools -y
docker commit nginx0 network_programming:v1
docker run --name nginx0 -v $PWD:/network_programming -it --cap-add=SYS_PTRACE network_programming:v1 bash
```
* 创建并启用`nginx1`容器
```bash
docker run --name nginx1 -v $PWD:/network_programming -it --cap-add=SYS_PTRACE network_programming:v1 bash
```
`--cap-add=SYS_PTRACE` 允许容器使用`strace`命令跟踪进程状态 
2. 测试容器间通信
* 进入`nginx1`容器输入以下命令查看虚拟网路的配置：
```bash
ifconfig
```
<details><summary>展开/收起</summary>
<pre><code>

eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 172.17.0.3  netmask 255.255.0.0  broadcast 172.17.255.255
        ether 02:42:ac:11:00:03  txqueuelen 0  (Ethernet)
        RX packets 77  bytes 83730 (83.7 KB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 34  bytes 2630 (2.6 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        loop  txqueuelen 1000  (Local Loopback)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

</code></pre>
</details>  
* 在容器nginx1的虚拟终端中使用ping指令测试地址为172.17.0.2的容器nginx0是否能与地址为172.17.0.3的容器nginx1之间进行通信  

```bash
ping 172.17.0.2
```

```
PING 172.17.0.2 (172.17.0.2): 56 data bytes
64 bytes from 172.17.0.2: icmp_seq=0 ttl=64 time=0.152 ms
64 bytes from 172.17.0.2: icmp_seq=1 ttl=64 time=0.112 ms
64 bytes from 172.17.0.2: icmp_seq=2 ttl=64 time=0.113 ms
```
* 容器nginx0与nginx1之间可以进行通信
