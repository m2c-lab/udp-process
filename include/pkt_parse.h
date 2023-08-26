#ifndef _PKT_PARSE_H_
#define _PKT_PARSE_H_

#include "pkt_def.h"
#include "pkt_receive.h"
#include <iostream>
#include <queue>

// TODO: Implement options for parsing.

class Pkt_Parse {
  public:
    Pkt_Parse(Pkt_Receive& pkt_receive, std::mutex& mtx_pkt_receive);

    bool parse();

  private:
    Pkt_Receive& pkt_receive;
    std::mutex& mtx_pkt_receive;
};

#endif
