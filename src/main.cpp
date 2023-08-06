#include "cli_cmd.h"
#include <boost/exception/diagnostic_information.hpp>
#include <boost/program_options.hpp>
#include <iostream>

#ifdef _MSC_VER
#    define _CRT_SECURE_NO_WARNINGS
#    pragma warning(disable : 4244)
#endif

int main(int argc, char* argv[]) {
    namespace po = boost::program_options;

    CLI_Options opt; // command line options

    // clang-format off
    po::options_description generic("Generic options");
    generic.add_options()
        ("version,v", "print version string")
        ("help,h", "produce help message")
    ;

    po::options_description config("Configuration");
    config.add_options()
        ("verbose,V", "print additional information")
    ;

    po::options_description hidden("Hidden options");
    hidden.add_options()
        ("command", po::value<std::string>(&opt.cmd)->required(), "command")
        ("input", po::value<std::string>(&opt.input)->required(), "input")
    ;
    // clang-format on

    po::options_description cmdline_options;
    cmdline_options.add(generic).add(config).add(hidden);

    po::options_description config_file_options;
    config_file_options.add(config).add(hidden);

    po::options_description visible("Allowed options");
    visible.add(generic).add(config);

    po::positional_options_description p;
    p.add("command", 1);
    p.add("input", -1);
    po::variables_map vm;
    try {
        po::store(po::command_line_parser(argc, argv).options(cmdline_options).positional(p).run(), vm);
        if (vm.count("help")) {
            std::cout << "M2C UDP Process\n";
            std::cout << std::string(60, '=') << "\n\n";
            std::cout << "Usage: " << argv[0] << " <command> <input> [options]\n\n";
            std::cout << visible << std::endl;
            return 0;
        }
        if (vm.count("version")) { std::cout << "0.1.0" << std::endl; }
        po::notify(vm);
    } catch (const std::exception& e) {
        std::string s = e.what();
        if (s == "the option '--command' is required but missing") s = "command is missing";
        else if (s == "the option '--input' is required but missing") s = "input is missing";
        std::cerr << s << std::endl;
        std::cerr << "Use '" << argv[0] << " -h' for help." << std::endl;
        return 1;
    }

    if (vm.count("verbose")) opt.verbose = true;

    if (opt.cmd == "receive" || opt.cmd == "r") {
        cmd_receive(opt);
    } else if (opt.cmd == "convert" || opt.cmd == "c") {
        cmd_convert(opt);
    } else {
        std::cerr << "Unknown command: " << opt.cmd << std::endl;
    }

    return 0;
}
