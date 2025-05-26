#pragma once
#include "VulnerabilityPattern.hpp"
#include <string>
#include <vector>

class PatternLoader {
public:
    static std::vector<VulnerabilityPattern> loadFromFile(const std::string& filepath);
};
