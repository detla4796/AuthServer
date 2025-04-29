#pragma once
#include <iostream>

using namespace std;

class User
{
    protected:
    string login;
    string password;
    string role;
    public:
    User(const string& login, const string& password, const string& role) : login(login), password(password), role(role) {}
    virtual ~User() = default;
    virtual bool hasAccess(string& resource) 
    {
        return false;
    }
    bool auth(string& inputPass)
    {
        return inputPass == password;
    }
    string getLogin()
    {
        return login;
    }
    string getRole()
    {
        return role;
    }
};

class Admin : public User
{
    public:
    Admin(string& login, string& password) : User(login, password, "Admin") {}
    bool hasAccess(string& resource) override
    {
        return true;
    }
};

class RegularUser : public User
{
    public:
    RegularUser(string& login, string& password) : User(login, password, "User") {}
    bool hasAccess(string& resource) override
    {
        return resource == "profile";
    }
};

class Guest : public User
{
    public:
    Guest() : User("Guest", "", "Guest") {}
    bool hasAccess(string& resource) override
    {
        return resource == "home";
    }
};