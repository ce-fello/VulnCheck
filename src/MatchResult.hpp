#pragma once
#include <string>

struct MatchResult {
    std::string file;
    int line;
    std::string id;
    std::string message;
};
