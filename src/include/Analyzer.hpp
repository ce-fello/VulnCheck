#pragma once
#include "VulnerabilityPattern.hpp"
#include "MatchResult.hpp"
#include <string>
#include <vector>

/**
 * @brief Responsible for analyzing source files for known vulnerability patterns.
 */
class Analyzer {
public:
    /**
     * @brief Analyzes the specified file against a list of vulnerability patterns.
     * 
     * @param filepath Path to the file to analyze.
     * @param patterns List of vulnerability patterns to search for.
     * @return std::vector<MatchResult> List of matched vulnerabilities found in the file.
     */
    static std::vector<MatchResult> analyzeFile(const std::string& filepath, const std::vector<VulnerabilityPattern>& patterns);
};
