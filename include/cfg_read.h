#ifndef _CFG_READ_H_
#define _CFG_READ_H_

#include "cfg.h"
#include "cli_options.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ryml.hpp>
#include <ryml_std.hpp>

Cfg cfg_read(const CLI_Options& opt);

#endif
