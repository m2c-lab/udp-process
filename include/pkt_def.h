#ifndef _PKT_DEF_H_
#define _PKT_DEF_H_

#include <array>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstddef>
#include <string>

const inline constexpr static size_t PKT_PAYLOAD_LENGTH = 1040;
const inline constexpr static size_t PKT_HEADER_LENGTH  = 8;
const inline constexpr static size_t PKT_LENGTH         = PKT_HEADER_LENGTH + PKT_PAYLOAD_LENGTH;
const inline constexpr static size_t PKT_BUFFER_SIZE    = PKT_LENGTH + 8;
const inline constexpr static size_t CIR_LENGTH         = 256;
const inline constexpr static size_t CIR_BYTES          = CIR_LENGTH * 2; // for either I or Q
const inline constexpr static size_t CIR_BEGIN_BYTE_N   = 16;

using Pkt_Payload     = std::string;
using IP_Addr         = std::string;
using Port_N          = unsigned short;
using Boost_Time_Unit = boost::posix_time::microseconds;

#endif
