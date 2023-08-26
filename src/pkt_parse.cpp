#include "pkt_parse.h"

Pkt_Parse::Pkt_Parse(Pkt_Receive& pkt_receive, std::mutex& mtx_pkt_receive)
    : pkt_receive(pkt_receive), mtx_pkt_receive(mtx_pkt_receive) {}

bool Pkt_Parse::parse() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx_pkt_receive);
        auto&& queue = pkt_receive.getPayloadQueue();
        if (auto queue_size = queue.size(); queue_size > 0) {
            std::cout << "Number of Payloads: " << queue_size << std::endl;
            auto payload = queue.front();
            queue.pop();
            std::cout << "Payload Size: " << payload.size() << std::endl;
        } else if (!pkt_receive.isRunning()) {
            std::cout << "Finished parsing and receiving has stopped." << std::endl;
            return true;
        }
    }
}
