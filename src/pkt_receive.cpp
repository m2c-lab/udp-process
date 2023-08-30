#include "pkt_receive.h"
#include "global.h"

std::mutex payload_queue_mutex;

Pkt_Receive::Pkt_Receive(const IP_Addr& local_ip_addr_, const IP_Addr& remote_ip_addr_, Port_N local_port_,
                         Port_N remote_port_, size_t timeout_)
    : local_ip_addr(local_ip_addr_), remote_ip_addr(remote_ip_addr_), local_port(local_port_),
      remote_port(remote_port_), local_endpoint(boost::asio::ip::address::from_string(local_ip_addr_), local_port_),
      remote_endpoint(boost::asio::ip::address::from_string(remote_ip_addr_), remote_port_),
      socket(io_context, local_endpoint), buffer(PKT_BUFFER_SIZE), timeout(timeout_),
      ddl(io_context, Boost_Time_Unit(timeout_)) {
    ddl.expires_from_now(Boost_Time_Unit(timeout_));
    checkDDL();
}

Pkt_Receive::Pkt_Receive(const Cfg& cfg)
    : Pkt_Receive(cfg.r.local_ip, cfg.r.remote_ip, cfg.r.local_port, cfg.r.remote_port, cfg.r.timeout) {}

void Pkt_Receive::startReceiving() {
    if (!is_running) {
        is_running = true;
        std::cout << "Start receiving" << std::endl;
        socket.async_receive_from(
            boost::asio::buffer(buffer), remote_endpoint,
            std::bind(&Pkt_Receive::handleIncomingPacket, this, std::placeholders::_1, std::placeholders::_2));

        processIOContext();
    }
}

void Pkt_Receive::handleIncomingPacket(const boost::system::error_code& error, std::size_t bytes_received) {
    if (is_running) {
        // std::cerr << "Received " << bytes_received << " bytes" << std::endl;
        if (!error) {
            // Process the received packet
            std::string payload(buffer.data(), bytes_received);

            if (bytes_received == PKT_PAYLOAD_LENGTH) {
                // Pkt_Payload bitset_data;
                // std::transform(payload.begin(), payload.end(), bitset_data.begin(),
                //                [](char c) { return std::byte(c); });
                // {
                //     std::unique_lock<std::mutex> lock(payload_queue_mutex);
                //     payload_queue.push(bitset_data);
                // }
                payload_queue.push(payload);
            } else {
                // omit this package
            }
        } else {
            std::cerr << "Error receiving data: " << error.message() << std::endl;
        }

        socket.async_receive_from(
            boost::asio::buffer(buffer), remote_endpoint,
            std::bind(&Pkt_Receive::handleIncomingPacket, this, std::placeholders::_1, std::placeholders::_2));
    }
}

void Pkt_Receive::stopReceiving() { is_running = false; }

bool Pkt_Receive::isRunning() noexcept { return is_running; }

std::queue<Pkt_Payload>& Pkt_Receive::getPayloadQueue() { return payload_queue; }

void Pkt_Receive::processIOContext() {
    while (is_running) {
        // Process a single event from the io_context
        boost::system::error_code ec;
        io_context.run_one(ec);
        if (ec) {
            std::cerr << "Error in io_context: " << ec.message() << std::endl;
            return;
        }
    }

    // If is_running is still true after the loop, continue processing
    if (is_running) {
        // Continue processing IO context asynchronously
        io_context.post([this]() { processIOContext(); });
    }
}

void Pkt_Receive::checkDDL() {
    if (ddl.expires_at() <= boost::asio::deadline_timer::traits_type::now()) {
        socket.cancel();
        ddl.expires_at(boost::posix_time::pos_infin);
        is_running = false;
        std::cout << "Finished receiving" << std::endl;
    }
    ddl.async_wait(std::bind(&Pkt_Receive::checkDDL, this));
}
