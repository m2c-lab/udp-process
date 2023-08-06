#ifndef _CLI_CMD_H_
#define _CLI_CMD_H_

#include "cfg_read.h"
#include "cli_options.h"
#include "pkt.h"

void cmd_receive(const CLI_Options& opt);

void cmd_convert(const CLI_Options& opt);

#endif
