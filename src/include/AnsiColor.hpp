#pragma once
#include <string>

namespace AnsiColor {
    const std::string RESET   = "\033[0m";
    const std::string RED     = "\033[31m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";
    const std::string BLUE    = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN    = "\033[36m";
    const std::string BOLD    = "\033[1m";

    inline std::string colorSeverity(const std::string& severity) {
        if (severity == "critical") return RED + BOLD;
        if (severity == "high")     return RED;
        if (severity == "medium")   return YELLOW + BOLD;
        if (severity == "low")      return CYAN;
        return RESET;
    }

    inline std::string highlightMatch(const std::string& line, std::pair<size_t, size_t> range) {
        if (range.first >= line.size() || range.second > line.size() || range.first >= range.second)
            return line;

        return line.substr(0, range.first) +
               RED + BOLD + line.substr(range.first, range.second - range.first) + RESET +
               line.substr(range.second);
    }
}
