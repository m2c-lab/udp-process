#ifndef _CLI_OPTIONS_H_
#define _CLI_OPTIONS_H_

#include <string>

struct CLI_Options {
    std::string cmd;
    std::string input;
    bool verbose = false;
};

#endif
