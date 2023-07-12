#include <net/socket.h>
#include <netinet/tcp.h>

#include <common/string.h>
namespace network
{

socket_t socket::create_socket(NET_TYPE type, const char* sHost)
{
    auto hosts = common_work::split(sHost);
    if (hosts.size() < 2)
    {
        return 0;
    }

    if (NET_TCP == type)
    {
        socket_id_ = socket(SOCK_STREAM, AF_INET, IPPROTO_TCP);
    }
    else if (NET_UDP == type)
    {
        socket_id_ = socket(SOCK_DGRAM, AF_INET, IPPTOTO_UDP);
    }
    if (0 == socket_id_)
    {
        return 0;
    }
    

    sockaddr *addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(std::stoi(hosts[1]));

    bind(socket_id_, );
    return 0;
}

void socket_t socket::on_listen()
{
    is_listen = true;
    listen(socket_id_, )
}
}