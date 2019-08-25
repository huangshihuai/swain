#include "interface/i_socket.h"

namespace hyper {
namespace net {
using namespace interface;
class Socket : public ISocket {
public:
    Socket();
    virtual ~Socket();
    SOCKET getFd() const override { return m_socketFd; }; 
    bool getTcpInfo(struct tcp_info* info) const override;
    bool createSocket() override;
    bool bindAddress() override;
    bool listen(int32 backlog) override;
    int  accept() override;
    bool connect() override;
    void shutdown() override;
    inline void shutdownRead() override { ::shutdown(m_socketFd, 0); };
    inline void shutdownWrite() override { ::shutdown(m_socketFd, 1); };

    inline void setTcpNoDelay(bool on) override{ m_tcpNoDelay = on; };
    inline void setReuseAddr(bool on) override{ m_reuseAddr = on; }; 
    inline void setReusePort(bool on) override{ m_reusePort = on; };
    inline void setKeepAlive(bool on) override{ m_keepAlive = on; };
    inline void setIp(const std::string &ip) override{ m_ip = ip; };
    inline void setPort(int32 port) override{ m_port = port; };
    inline void setSocketModel(ESocketModel socketModel) { m_socketModel = socketModel; };
private:
    bool m_tcpNoDelay; // TCP_CORK
    bool m_reuseAddr;
    bool m_reusePort;
    bool m_keepAlive;
    ESocketModel m_socketModel;
    uint32 m_port;
    std::string m_ip;
    SOCKET m_socketFd;
    SocketState m_socketState;
};
}
}