#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <random>
#include <ctime>
#include <openssl/sha.h>

using namespace std;

class User
{
    protected:
    static string generateSalt()
    {
        string slt;
        srand(time(0));
        for (int i = 0; i < 8; i++)
        {
            slt += char(rand() % 10 + 48);
        }
        for (int i = 0; i < 8; i++)
        {
            slt += char(rand() % 26 + 65);
        }
        cout << slt << endl;
        return slt;
    }
    public:
    string login;
    string password;
    string role;
    string salt;
    User(const string& login, const string& pass, const string& role) : login(login),  salt(generateSalt()), role(role)
    {
        password = sha256(pass, salt);
    }
    virtual ~User() = default;
    static string sha256(const string& password, const string& salt)
    {
        string saltedPassword = password + salt;
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, saltedPassword.c_str(), saltedPassword.size());
        SHA256_Final(hash, &sha256);

        stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        {
            ss << hex << setw(2) << setfill('0') << (int)hash[i];
        }
        return ss.str();
    }
    virtual bool hasAccess(const string& resource) 
    {
        return false;
    }
    bool auth(const string& inputPass)
    {
        return sha256(inputPass, salt) == password;
    }
    string getLogin()
    {
        return login;
    }
    string getRole()
    {
        return role;
    }
    string getPassword()
    {
        return password;
    }
    string getPassHash()
    {
        return sha256(password, salt);
    }
};

class Admin : public User
{
    public:
    Admin(const string& login, const string& password) : User(login, password, "Admin") {}
    bool hasAccess(const string& resource) override
    {
        return true;
    }
};

class RegularUser : public User
{
    public:
    RegularUser(const string& login, const string& password) : User(login, password, "User") {}
    bool hasAccess(const string& resource) override
    {
        return resource == "home" || resource == "profile";
    }
};

class Guest : public User
{
    public:
    Guest() : User("Guest", "", "Guest") {}
    bool hasAccess(const string& resource) override
    {
        return resource == "home";
    }
};