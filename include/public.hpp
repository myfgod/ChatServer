#ifndef PUBLIC_H
#define PUBLIC_H

/*
server和client的公共文件
*/
enum
{
    LOGIN_MSG = 1,  // 登入消息
    LOGIN_MSG_ACK,
    REG_MSG,        // 注册消息
    REG_MSG_ACK,    
    ONE_CHAT_MSG,   //点对点聊天消息
    ADD_FRIEND_MSG,  //添加好友消息

    CREATE_GROUP_MSG, //创建群聊
    ADD_GROUP_MSG,    //加入群聊
    GROUP_CHAT_MSG,    //群聊天
    LOGINOUT_MSG      //客户端退出
};

#endif