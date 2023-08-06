#ifndef _PKT_RECEIVE_H_
#define _PKT_RECEIVE_H_

#include "cfg.h"
#include "pkt_def.h"
#include <algorithm>
#include <boost/asio.hpp>
#include <iostream>
#include <queue>
#include <string>
#include <sys/time.h>
#include <thread>

class Pkt_Receive {
  public:
    Pkt_Receive(const IP_Addr& local_ip_addr, const IP_Addr& remote_ip_addr, Port_N local_port, Port_N remote_port,
                size_t timeout);
    Pkt_Receive(const Cfg& cfg);
    void startReceiving();
    void stopReceiving();
    std::queue<Pkt_Payload>& getPayloadQueue(); // Return a reference

  private:
    void handleIncomingPacket(const boost::system::error_code& error, std::size_t bytes_received);
    void processIOContext();
    void checkDDL();

    IP_Addr local_ip_addr;
    IP_Addr remote_ip_addr;
    Port_N local_port;
    Port_N remote_port;

    boost::asio::io_context io_context;
    boost::asio::ip::udp::endpoint local_endpoint;
    boost::asio::ip::udp::endpoint remote_endpoint;
    boost::asio::ip::udp::socket socket;
    std::vector<char> buffer;
    bool is_running = false;
    size_t timeout;
    boost::asio::deadline_timer ddl;

    std::queue<Pkt_Payload> payload_queue;
};

#endif
