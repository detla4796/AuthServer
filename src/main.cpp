#include <iostream>
#include "Usermanager.h"
#include <boost/asio.hpp>
#include <string>
using namespace std;
using boost::asio::ip::tcp;
// class Session
// {
//     tcp::socket socket;
// 	UserManager manager;
//     public:
// 	enable_shared_from_this<Session> {
// 	Session(tcp::socket sckt, UserManager & usmng) : socket(move(sckt)), manager(usmng) {}
//     void Start() { readRequest(); } 
//     private:
// 	void readRequest() 
//     {
//         auto self{shared_from_this()}
//         socket.async_read_some(boost::asio::bufer(data,max_length),[this,self])
//         {
//             if (!er)
//             {
//             }
//         }
//     }
//     void processRequest(int length, string request(data, length), string response) 
//     {
//         if (request.find("login:") == 0)
//         {
//             int pos_first = request.find(":", 6);
//             int pos_second = request.find(":", pos_first + 1);
//             string username = request.substr(6, pos_first - 1); 
//             string password = request.substr(pos_first + 1, pos_second - pos_first - 1);
//             bool auth = manager.auth(username, password);
//             response = auth ? "Auth_success" : "Auth_failed";
//         }
//         else if (request.find("access:") == 0)
//         {
//             int pos_first = request.find(":", 7);
//             int pos_second = request.find(":", pos_first + 1);
//             string username = request.substr(7, pos_first - 1);
//             string password = request.substr(pos_first + 1, pos_second - pos_first - 1);
//             bool auth = manager.auth(username, password);
//             response = auth ? "Access_granted" : "Access_denied";
//         }
//     }
// };

int main()
{
	UserManager user_list;
    Admin admin("admin", "admin");
    user_list.addUser(admin);
    RegularUser user("user", "password");
    user_list.addUser(user);
    user_list.users_info();
    string request;
    getline(cin, request);
    if (request.find("login:") == 0)
    {
        int pos_first = request.find(":", 6);
        int pos_second = request.find(":", pos_first + 1);
        string username = request.substr(6, pos_first - 6); 
        string password = request.substr(pos_first + 1, pos_second - pos_first - 1);
        bool auth = user_list.auth(username, password);
        if (!username.empty() && !password.empty())
        {
            cout << (auth ? "Auth_success" : "Auth_failed") << endl;
        }
    }
    else if (request.find("access:") == 0)
    {
        int pos_first = request.find(":", 7);
        int pos_second = request.find(":", pos_first + 1);
        string username = request.substr(7, pos_first - 7);
        string password = request.substr(pos_first + 1, pos_second - pos_first - 1);
        if (!username.empty() && !password.empty()) 
        {
            bool auth = user_list.auth(username, password);
            cout << (auth ? "Access_granted" : "Access_denied") << endl;
        }
        else 
        {
            cout << "Invalid" << endl;
        }
    }
    else
    {
        cout << "Invalid" << endl;
    }
}