#pragma once
#include "VulnerabilityPattern.hpp"
#include "MatchResult.hpp"
#include <string>
#include <vector>

class Analyzer {
public:
    static std::vector<MatchResult> analyzeFile(const std::string& filepath, const std::vector<VulnerabilityPattern>& patterns);
};
