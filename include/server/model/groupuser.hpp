#ifndef GROUPUSER_H
#define GROUPUSER_H
#include "user.hpp"
//群组用户信息类，比普通User用户多了个role信息
class groupUser : public User
{
public:
    void setRole(string role){this->role=role;}
    string getRole(){return this->role;}
private:
    string role;
};

#endif