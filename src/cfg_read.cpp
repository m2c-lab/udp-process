#include "cfg_read.h"

Cfg cfg_read(const CLI_Options& opt) {
    Cfg cfg;
    auto input = opt.input;
    if (!std::filesystem::exists(input)) {
        std::cerr << "File not found: " << input << std::endl;
        exit(1);
    }
    std::ifstream in(input);
    if (!in.is_open()) {
        std::cerr << "Error opening file: " << input << std::endl;
        exit(2);
    }
    std::stringstream buffer;
    buffer << in.rdbuf();

    ryml::Tree tree = ryml::parse_in_arena(ryml::to_csubstr(buffer.str()));
    size_t timeout_n;
    auto r = tree["receive"];
    r["local"]["ip"] >> cfg.r.local_ip;
    r["local"]["port"] >> cfg.r.local_port;
    r["remote"]["ip"] >> cfg.r.remote_ip;
    r["remote"]["port"] >> cfg.r.remote_port;
    if (auto&& to = r["timeout"]; to.has_val()) r["timeout"] >> cfg.r.timeout;
    else cfg.r.timeout = 60 * 1000 * 1000; // 60 seconds

    if (opt.verbose) {
        std::cout << "Configuration:" << std::endl;
        std::cout << "  r.local.ip: " << cfg.r.local_ip << std::endl;
        std::cout << "  r.local.port: " << cfg.r.local_port << std::endl;
        std::cout << "  r.remote.ip: " << cfg.r.remote_ip << std::endl;
        std::cout << "  r.remote.port: " << cfg.r.remote_port << std::endl;
        std::cout << "  r.timeout: " << cfg.r.timeout << std::endl;
    }

    return cfg;
}
