#pragma once
#include <string_view>
namespace network
{

enum NET_TYPE
{
    NET_TCP,
    NET_UDP,
};

using socket_t = int;
class socket
{
public:
    socket_t create_socket(NET_TYPE type, const char* sHost);

    void on_listen();
private:
    socket_t socket_id_ = 0;
    bool is_listen = false;
};


} // namespace networkclass socket