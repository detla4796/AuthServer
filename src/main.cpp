#include <iostream>
#include <User.h>
#include <UserManager.h>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;

class Session
{
    tcp::socket sock;
    UserManager& manager;
    void readRequest() {}
    public:
    enable_shared_from_this<Session> {
    Session(tcp::socket sckt, UserManager& usmng) : sock(move(sckt)).manager(usmng) {}
    void Start() { readRequest(); }
    private:
    void readRequest() { auto self(shared_from_this()) }
    }
};

int main()
{
    Admin a("tiirin", "AdminPass");
    UserManager userList;
    userList.addUser(a);
    cout << userList.findUser("tiirin") << endl;
    RegularUser u("reguser", "UserPass");
    userList.addUser(u);
    cout << userList.findUser("reguser") << endl;
}