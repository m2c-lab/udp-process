#include "cli_cmd.h"
#include "global.h"

void cmd_receive(const CLI_Options& opt) {
    auto cfg = cfg_read(opt);
    Pkt_Receive r(cfg);
    Pkt_Parse p(r, payload_queue_mutex);
    std::thread parser(&Pkt_Parse::parse, &p);
    r.startReceiving();

    parser.join();
}

void cmd_convert(const CLI_Options& opt) {}
