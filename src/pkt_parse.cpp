#include "pkt_parse.h"
// #include <arrow/api.h>
// #include <arrow/io/api.h>
// #include <parquet/arrow/reader.h>
// #include <parquet/arrow/writer.h>
// #include <parquet/exception.h>


// using parquet::ArrowWriterProperties;

Pkt_Parse::Pkt_Parse(Pkt_Receive& pkt_receive, std::mutex& mtx_pkt_receive)
    : pkt_receive(pkt_receive), mtx_pkt_receive(mtx_pkt_receive), writer_props(
        parquet::WriterProperties::Builder()
            .created_by("M2C UDP Process")
            // ->max_row_group_length(10000)
            // ->version(parquet::ParquetVersion::PARQUET_2_6)
            // ->data_page_version(parquet::ParquetDataPageVersion::V2)
            // ->compression(parquet::Compression::SNAPPY)
            ->compression(parquet::Compression::UNCOMPRESSED)
            ->build()
) {
    PARQUET_ASSIGN_OR_THROW(outfile, arrow::io::FileOutputStream::Open("test1.parquet"));
    parquet::schema::NodeVector fields;
    fields.push_back(parquet::schema::PrimitiveNode::Make(
        "timestamp", parquet::Repetition::REQUIRED, parquet::Type::INT32, parquet::ConvertedType::INT_32));
    // fields.push_back(parquet::schema::PrimitiveNode::Make(
        // "noise", parquet::Repetition::REQUIRED, parquet::Type::INT32, parquet::ConvertedType::INT_32));
    // for (size_t i = 0; i != CIR_LENGTH; ++i) {
    //     fields.push_back(parquet::schema::PrimitiveNode::Make(
    //         "CIR" + std::to_string(i), parquet::Repetition::REQUIRED, parquet::Type::INT32, parquet::ConvertedType::UINT_32));
    // }
    writer_schema = std::static_pointer_cast<parquet::schema::GroupNode>(
    parquet::schema::GroupNode::Make("UDP Payload", parquet::Repetition::REQUIRED, fields));
}

bool Pkt_Parse::parse() {
    parquet::StreamWriter os{ parquet::ParquetFileWriter::Open(outfile, writer_schema, writer_props) };
    while (true) {
        std::unique_lock<std::mutex> lock(mtx_pkt_receive);
        auto&& queue = pkt_receive.getPayloadQueue();
        if (auto queue_size = queue.size(); queue_size > 0) {
            std::cout << "Number of Payloads: " << queue_size << std::endl;
            auto payload = queue.front();
            queue.pop();
            Data data(payload);
            // os << data.timestamp << data.noise;
            try {
                // os << int32_t(1) << int32_t(2);
                os << int32_t(1);
                std::cout << data.timestamp << ' ' << data.noise << std::endl;

                // for (auto&& cir : data.CIR) os << cir;
                os << parquet::EndRow;
                // os.EndRow();
            } catch (...) {
                std::cerr << "Error writing to parquet file." << std::endl;
                return false;
            }
        } else if (!pkt_receive.isRunning()) {
            std::cout << "Finished parsing and receiving has stopped." << std::endl;
            break;
        }
    }
    os.EndRowGroup();
    // outfile->CloseAsync();
    if (outfile->Close().ok()) {
        std::cout << "n_cols: " << os.num_columns() << std::endl;
        std::cout << "cu_row: " << os.current_row() << std::endl;
        return true;
    } else {
        std::cerr << "File Close Not OK!" << std::endl;
        return false;
    }
}

Pkt_Parse::Data::Data(const Pkt_Payload& payload) { // payload is an std::array of std::byte.
    // timestamp is the bytes 2-5
    timestamp = strToUInt32(payload.substr(2, 4));
    // noise is the bytes 6-7
    noise = strToUInt32(std::string(2, '\0').append(payload.substr(6, 2)));
    for (size_t i = 0; i != CIR_LENGTH; ++i) {
        CIR[i] = strToUInt32(payload.substr(CIR_BEGIN_BYTE_N + i, 4));
    }
    // std::cout << timestamp << std::endl;
}

uint32_t Pkt_Parse::Data::bytesToUInt32(const std::array<std::byte, 4>& bytes) {
    uint32_t value;
    if constexpr (std::endian::native == std::endian::big) {
        auto reverse = [](const std::array<std::byte, 4>& src, std::array<std::byte, 4>& dst) {
            std::copy(src.rbegin(), src.rend(), dst.begin()); 
        };
        std::array<std::byte, 4> reversed;
        reverse(bytes, reversed);
        std::memcpy(&value, reversed.data(), 4);
    } else {
        std::memcpy(&value, bytes.data(), 4);
    }

    return value;
}

uint32_t Pkt_Parse::Data::strToUInt32(const std::string& str) {
    assert(str.size() == 4); // str must be length of 4
    return str[0] << 24 | str[1] << 16 | str[2] << 8 | str[3];
}
