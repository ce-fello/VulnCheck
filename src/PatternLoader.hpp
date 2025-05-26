#pragma once
#include <string>
#include <vector>
#include "VulnerabilityPattern.hpp"

class PatternLoader {
public:
    static std::vector<VulnerabilityPattern> loadPatterns(const std::string& filepath);
};
