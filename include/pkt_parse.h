#ifndef _PKT_PARSE_H_
#define _PKT_PARSE_H_

#include "pkt_def.h"
#include "pkt_receive.h"
#include "utils.h"
#include <arrow/io/file.h>
#include <bit>
#include <iostream>
#include <parquet/arrow/writer.h>
#include <parquet/stream_writer.h>
#include <queue>

// TODO: Implement options for parsing.

class Pkt_Parse {
  public:
    Pkt_Parse(Pkt_Receive& pkt_receive, std::mutex& mtx_pkt_receive);

    ~Pkt_Parse() = default;

    bool parse();

  private:
    Pkt_Receive& pkt_receive;
    std::mutex& mtx_pkt_receive;

    struct Data {
        uint32_t timestamp;
        uint32_t noise;
        std::array<uint32_t, CIR_LENGTH> CIR;

        Data() = default;

        Data(const Pkt_Payload& payload);

      private:
        uint32_t bytesToUInt32(const std::array<std::byte, 4>& bytes);

        uint32_t strToUInt32(const std::string& str);

    } data;
};

#endif
