# Nginx学习
Nginx是web服务器，市场份额排在第二位， Apache(1995)第一位
功能：
1. web服务
2. 反向代理
3. 负载均衡
4. 轻量级（系统资源占用少）
5. 高性能
6. 高并发
7. 高可用
8. 热部署（运行的时候升级应用服务）
9. 高度模块化设计
10. 自由许可证

## 为什么选择Nginx
1. 单机支持10万并发，同时保持立马响应地高效的服务
2. epoll高并发技术只需要占用更多内存就能做到
3. 

## 安装Nginx
1. 下载源码
```bash
wget wget http://nginx.org/download/nginx-1.14.2.tar.gz
```
2. 目录结构
```
├── auto #编译相关的脚本
│   ├── cc #检查编译器的脚本
│   ├── lib # 检查依赖库的脚本
│   │   ├── geoip
│   │   ├── google-perftools
│   │   ├── libatomic
│   │   ├── libgd
│   │   ├── libxslt
│   │   ├── openssl
│   │   ├── pcre
│   │   ├── perl
│   │   └── zlib
│   ├── os #检查操作系统类型的脚本
│   └── types
├── conf # 默认的配置文件
├── contrib
│   ├── unicode2nginx
│   └── vim
│       ├── ftdetect
│       ├── ftplugin
│       ├── indent
│       └── syntax
├── html #欢迎界面和错误界面相关的html文件
├── man
└── src #源码目录
    ├── core #核心代码
    ├── event #事件（模块）相关的代码
    │   └── modules
    ├── http #web服务模块相关代码
    │   ├── modules
    │   │   └── perl
    │   └── v2
    ├── mail #邮件模块相关的代码
    ├── misc
    ├── os 操作系统相关代码
    │   └── unix
    └── stream #流处理相关的代码
```
3. 安装依赖项
```bash
sudo apt-get update
sudo apt-get install libpcre3 libpcre3-dev
```
还有可能需要安装：  
```bash
sudo apt-get install openssl libssl-dev #网络加密协议
```
4. 编译
```bash
./configure 
```
参数配置说明：  
--prefix 指定安装目录默认/usr/local/nginx
5. 生成目录objs及文件
<details><summary>展开/收起</summary>
<pre><code>
├── autoconf.err
├── Makefile
├── ngx_auto_config.h
├── ngx_auto_headers.h
├── ngx_modules.c #包含了被编译的模块
└── src
    ├── core
    ├── event
    │   └── modules
    ├── http
    │   ├── modules
    │   │   └── perl
    │   └── v2
    ├── mail
    ├── misc
    ├── os
    │   ├── unix
    │   └── win32
    └── stream
</code></pre>
</details>  

执行`make`命令进行编译
```bash
cd nginx-1.14.2
make -j9
```
编译结果：  
<details><summary>展开/收起</summary>
<pre><code>
├── autoconf.err
├── Makefile
├── nginx
├── nginx.8
├── ngx_auto_config.h
├── ngx_auto_headers.h
├── ngx_modules.c
├── ngx_modules.o
└── src
    ├── core
    │   ├── nginx.o
    │   ├── ngx_array.o
    │   ├── ngx_buf.o
    │   ├── ngx_conf_file.o
    │   ├── ngx_connection.o
    │   ├── ngx_cpuinfo.o
    │   ├── ngx_crc32.o
    │   ├── ngx_crypt.o
    │   ├── ngx_cycle.o
    │   ├── ngx_file.o
    │   ├── ngx_hash.o
    │   ├── ngx_inet.o
    │   ├── ngx_list.o
    │   ├── ngx_log.o
    │   ├── ngx_md5.o
    │   ├── ngx_module.o
    │   ├── ngx_murmurhash.o
    │   ├── ngx_open_file_cache.o
    │   ├── ngx_output_chain.o
    │   ├── ngx_palloc.o
    │   ├── ngx_parse.o
    │   ├── ngx_parse_time.o
    │   ├── ngx_proxy_protocol.o
    │   ├── ngx_queue.o
    │   ├── ngx_radix_tree.o
    │   ├── ngx_rbtree.o
    │   ├── ngx_regex.o
    │   ├── ngx_resolver.o
    │   ├── ngx_rwlock.o
    │   ├── ngx_sha1.o
    │   ├── ngx_shmtx.o
    │   ├── ngx_slab.o
    │   ├── ngx_spinlock.o
    │   ├── ngx_string.o
    │   ├── ngx_syslog.o
    │   └── ngx_times.o
    ├── event
    │   ├── modules
    │   │   └── ngx_epoll_module.o
    │   ├── ngx_event_accept.o
    │   ├── ngx_event_connect.o
    │   ├── ngx_event.o
    │   ├── ngx_event_pipe.o
    │   ├── ngx_event_posted.o
    │   └── ngx_event_timer.o
    ├── http
    │   ├── modules
    │   │   ├── ngx_http_access_module.o
    │   │   ├── ngx_http_auth_basic_module.o
    │   │   ├── ngx_http_autoindex_module.o
    │   │   ├── ngx_http_browser_module.o
    │   │   ├── ngx_http_charset_filter_module.o
    │   │   ├── ngx_http_chunked_filter_module.o
    │   │   ├── ngx_http_empty_gif_module.o
    │   │   ├── ngx_http_fastcgi_module.o
    │   │   ├── ngx_http_geo_module.o
    │   │   ├── ngx_http_gzip_filter_module.o
    │   │   ├── ngx_http_headers_filter_module.o
    │   │   ├── ngx_http_index_module.o
    │   │   ├── ngx_http_limit_conn_module.o
    │   │   ├── ngx_http_limit_req_module.o
    │   │   ├── ngx_http_log_module.o
    │   │   ├── ngx_http_map_module.o
    │   │   ├── ngx_http_memcached_module.o
    │   │   ├── ngx_http_mirror_module.o
    │   │   ├── ngx_http_not_modified_filter_module.o
    │   │   ├── ngx_http_proxy_module.o
    │   │   ├── ngx_http_range_filter_module.o
    │   │   ├── ngx_http_referer_module.o
    │   │   ├── ngx_http_rewrite_module.o
    │   │   ├── ngx_http_scgi_module.o
    │   │   ├── ngx_http_split_clients_module.o
    │   │   ├── ngx_http_ssi_filter_module.o
    │   │   ├── ngx_http_static_module.o
    │   │   ├── ngx_http_try_files_module.o
    │   │   ├── ngx_http_upstream_hash_module.o
    │   │   ├── ngx_http_upstream_ip_hash_module.o
    │   │   ├── ngx_http_upstream_keepalive_module.o
    │   │   ├── ngx_http_upstream_least_conn_module.o
    │   │   ├── ngx_http_upstream_zone_module.o
    │   │   ├── ngx_http_userid_filter_module.o
    │   │   ├── ngx_http_uwsgi_module.o
    │   │   └── perl
    │   ├── ngx_http_copy_filter_module.o
    │   ├── ngx_http_core_module.o
    │   ├── ngx_http_file_cache.o
    │   ├── ngx_http_header_filter_module.o
    │   ├── ngx_http.o
    │   ├── ngx_http_parse.o
    │   ├── ngx_http_postpone_filter_module.o
    │   ├── ngx_http_request_body.o
    │   ├── ngx_http_request.o
    │   ├── ngx_http_script.o
    │   ├── ngx_http_special_response.o
    │   ├── ngx_http_upstream.o
    │   ├── ngx_http_upstream_round_robin.o
    │   ├── ngx_http_variables.o
    │   ├── ngx_http_write_filter_module.o
    │   └── v2
    ├── mail
    ├── misc
    ├── os
    │   ├── unix
    │   │   ├── ngx_alloc.o
    │   │   ├── ngx_channel.o
    │   │   ├── ngx_daemon.o
    │   │   ├── ngx_dlopen.o
    │   │   ├── ngx_errno.o
    │   │   ├── ngx_files.o
    │   │   ├── ngx_linux_init.o
    │   │   ├── ngx_linux_sendfile_chain.o
    │   │   ├── ngx_posix_init.o
    │   │   ├── ngx_process_cycle.o
    │   │   ├── ngx_process.o
    │   │   ├── ngx_readv_chain.o
    │   │   ├── ngx_recv.o
    │   │   ├── ngx_send.o
    │   │   ├── ngx_setaffinity.o
    │   │   ├── ngx_setproctitle.o
    │   │   ├── ngx_shmem.o
    │   │   ├── ngx_socket.o
    │   │   ├── ngx_time.o
    │   │   ├── ngx_udp_recv.o
    │   │   ├── ngx_udp_sendmsg_chain.o
    │   │   ├── ngx_udp_send.o
    │   │   ├── ngx_user.o
    │   │   └── ngx_writev_chain.o
    │   └── win32
    └── stream
</code></pre>
</details>  

6. 安装
```bash
sudo make install 
```
nginx默认安装到了/usr/local/nginx目录下

7. 启动
在IP地址为192.168.3.157的机器终端上执行：  
```bash
cd /usr/local/nginx/sbin
sudo ./nginx
```
在IP地址为192.168.3.126机器的浏览器地址栏中输入192.168.3.126，则会跳转出nginx的显示画面，说明nginx服务启动成功

