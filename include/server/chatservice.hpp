#ifndef CHATSERVICE_H
#define CHATSERVICE_H
#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include <../thirdparty/json.hpp>
#include <mutex>
#include "UserModel.hpp"
#include"friendmodel.hpp"
#include"offlinemessagemodel.hpp"
#include"groupmodel.hpp"
#include"redis.hpp"
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;
using json = nlohmann::json;

using MsgHandler = function<void(const TcpConnectionPtr &conn, json &js, Timestamp)>;
// 聊天服务器业务类采用单例模式实现
class ChatService
{
public:
    // 获取单例对象的接口函数
    static ChatService *getinstance();
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //添加好友业务
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //创建群组业务
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //加入群组业务
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 处理注销业务
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //从redis的消息队列中获取订阅的消息
    void handleRedisSubscribeMessage(int userid, string msg);
    // 获取消息对应的处理器
    MsgHandler getHandler(int msgid);
    //处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr &conn);
    //处理服务器异常的方法
    void reset();

private:
    ChatService();
    // 存储消息idi和其对应的业务处理方法
    unordered_map<int, MsgHandler> _MsghandlerMap;
    // 数据操作类的对象
    UserModel _userModel;
    // 存储在线用户的通行链接
    unordered_map<int, TcpConnectionPtr> _userConnMap;
    // 定义互斥锁保证userConnMap的线程安全
    mutex _connMutex;
    //离线消息操作类的对象
    offlineMsgModel _offlineMsgModel;
    //好友列表操作类
    friendModel _friendModel;
    //群组聊天的操作类
    groupModel _groupModel;
    //redis的操作对象
    Redis _redis;
};

#endif