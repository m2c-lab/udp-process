#include "cli_cmd.h"
#include "global.h"

void cmd_receive(const CLI_Options& opt) {
    auto cfg = cfg_read(opt);
    Pkt_Receive r(cfg);
    r.startReceiving();
    // r.stopReceiving();

    {
        std::unique_lock<std::mutex> lock(payload_queue_mutex);
        auto&& queue = r.getPayloadQueue();
        std::cout << "Number of Payloads: " << queue.size() << std::endl;
    }
}

void cmd_convert(const CLI_Options& opt) {}
