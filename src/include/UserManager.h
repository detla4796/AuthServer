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

	UserManager() :dbmanager("my_data_base.db")
	{
		load_from_db();
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
				return us.password;
		return "";
	}
	bool auth(const string& uname, const string& upass)
	{
		
		return true;
	}
};