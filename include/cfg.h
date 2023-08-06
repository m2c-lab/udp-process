#ifndef _CFG_H_
#define _CFG_H_

#include "pkt_def.h"
#include <chrono>

struct Cfg_Receive {
    IP_Addr local_ip;
    IP_Addr remote_ip;
    Port_N local_port;
    Port_N remote_port;
    size_t timeout;
};

struct Cfg_Convert {
    bool foo;
};

struct Cfg {
    Cfg_Receive r;
    Cfg_Convert c;
};

#endif
