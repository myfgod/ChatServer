#include"chatserver.hpp"
#include<functional>
#include<string>
#include"../thirdparty/json.hpp"
#include<chatservice.hpp>
using namespace std;
using namespace placeholders;
using json=nlohmann::json;

ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &listenAddr,
                       const string &nameArg)
    : _server(loop, listenAddr, nameArg),
      _loop(loop)
{
    // 注册回调函数
    _server.setConnectionCallback(bind(&ChatServer::onConnection,this,_1));
    _server.setMessageCallback(bind(&ChatServer::onMessage,this,_1,_2,_3));
    //设置线程数量
    _server.setThreadNum(4);
}

void ChatServer::start()
{
    _server.start();
}

void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    if(!conn->connected())
    {
        ChatService::getinstance()->clientCloseException(conn);
        conn->shutdown();
    }
}
void ChatServer::onMessage(const TcpConnectionPtr &conn,
                           Buffer *buffer,
                           Timestamp time)
{
    string buf=buffer->retrieveAllAsString();
    //数据的反序列化
    json js=json::parse(buf);
    //达到的目的：完全解耦网络模块的代码和业务模块的代码
    //通过js["masgid"]读出来的数值绑定回调函数，获取业务处理器handler
    auto msgHandler=ChatService::getinstance()->getHandler(js["msgid"].get<int>());
    //回调消息对应绑定好的事件处理器，来执行响应的业务处理
    msgHandler(conn,js,time);
    
}
