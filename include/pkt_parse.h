#ifndef _PKT_PARSE_H_
#define _PKT_PARSE_H_

#include "pkt_def.h"
#include "pkt_receive.h"
#include "utils.h"
#include <bit>
#include <arrow/io/file.h>
#include <parquet/arrow/writer.h>
#include <parquet/stream_writer.h>
#include <arrow/util/type_fwd.h>
#include <iostream>
#include <queue>

// TODO: Implement options for parsing.

class Pkt_Parse {
  public:
    Pkt_Parse(Pkt_Receive& pkt_receive, std::mutex& mtx_pkt_receive);

    // ~Pkt_Parse();

    bool parse();

  private:
    Pkt_Receive& pkt_receive;
    std::mutex& mtx_pkt_receive;
    std::shared_ptr<parquet::WriterProperties> writer_props;
    std::shared_ptr<parquet::schema::GroupNode> writer_schema;
    std::shared_ptr<arrow::io::FileOutputStream> outfile;

    struct Data {
        uint32_t timestamp;
        uint32_t noise;
        std::array<uint32_t, CIR_LENGTH> CIR;
        
        Data() = default;

        Data(const Pkt_Payload& payload);

    private:
        uint32_t bytesToUInt32(const std::array<std::byte,4>& bytes);

        uint32_t strToUInt32(const std::string& str);

    } data;
};

#endif
