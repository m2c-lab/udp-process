#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <mutex>
#include <thread>

extern std::mutex payload_queue_mutex; // defined in src/pkt_receive.cpp

#endif
