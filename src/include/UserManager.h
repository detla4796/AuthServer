#pragma once
#include<iostream>
#include "User.h"
#include <vector>
#include <memory>
#include <sstream>
#include <iomanip>
#include "DatabaseManager.h"
using namespace std;
class UserManager
{
	vector<User> users;
	DatabaseManager dbmanager;

public:

	UserManager() : dbmanager("my_data_base.db")
	{
		load_from_db();
	}
	void users_info()
	{
		for (auto& user : users)
		{
			cout << user.getLogin() << " " << user.getPassword() << " " << user.getRole() << endl;
		}
	}
	void load_from_db()
	{
		auto users_db = dbmanager.load_from_db();

		for ( auto& user : users_db)
		{
			if (user.role == "Admin")
			{
				
				users.push_back(user);
			}
			else
				if (user.role == "User")
				{
				
					users.push_back(user);
				}
		}
	}
	void addUser(User& usr)
	{
		users.push_back(usr);
	}
	string findUser(const string& uname)
	{
		for (auto& us : users)
			if (uname == us.getLogin())
				return us.salt;
		return "";
	}
	string findUserPass(const string& uname)
	{
		for (auto& us : users)
			if (uname == us.getLogin())
				return us.password;
		return "";
	}
	bool findUserRole(const string& uname, const string& resource)
	{
		for (auto& us : users)
		{
			if (uname == us.getLogin())
			{
				if (us.getRole() == "Admin")
				{
					return true;
				}
				else
				{
					return us.hasAccess(resource);
				}
			}
		}
		return false;
	}
	bool auth(const string& uname, const string& upass, const string& resource = "")
	{
		if (size(findUser(uname)) != 0)
		{
			if (User::sha256(upass, findUser(uname)) == findUserPass(uname))
			{
				if (resource.empty())
				{
					return true;
				}
				return findUserRole(uname, resource);
			}
		}
		return false;
	}
};