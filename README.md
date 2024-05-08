# ChatServer
可以工作在nginx tcp负载均衡环境中的集群聊天服务器和客户端，基于muduo实现，使用redis的发布订阅实现服务器之间的通信
#编译方式
cd build
rm -rf *
cmake ..
make
#运行需要配置nginx tcp的负载均衡
