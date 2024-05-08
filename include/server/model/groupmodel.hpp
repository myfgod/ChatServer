#ifndef GROUPMODEL_H
#define GROUPMODEL_H
#include "group.hpp"
#include <vector>
#include <string>
using namespace std;
// 维护群组信息操作的接口方法
class groupModel
{
public:
    // 创建群组
    bool createGroup(Group &group);
    // 加入群组
    void addGroup(int userid, int groupid, string role);
    // 查询用户所在的群组信息
    vector<Group> queryGroup(int userid);
    // 根据指定的groupid查询群组用户的id列表，除了userid自己，主要用于群聊业务
    vector<int> queryGroupUsers(int userid, int groupid);
};

#endif