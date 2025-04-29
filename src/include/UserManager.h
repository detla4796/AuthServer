#pragma once
#include <iostream>
#include "User.h"
#include <vector>
#include <memory>

using namespace std;

class UserManager
{
    private:
    vector<unique_ptr<User>> users;
    public:
    void addUser(unique_ptr<User> user)
    {
        users.push_back(move(user));
    }
    User* findUser(const string& login)
    {
        for (auto& user : users)
        {
            if (user->getLogin() == login)
            {
                return user.get();
            }
        }
        return nullptr;
    }
};