#pragma once
#include <string>

struct MatchResult {
    std::string file;
    int line;
    std::string id;
    std::string message;
    std::string severity;
    std::string codeLine;
    std::pair<size_t, size_t> highlightRange;
};
