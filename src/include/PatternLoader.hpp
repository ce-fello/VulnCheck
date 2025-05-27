#pragma once
#include <string>
#include <vector>
#include "VulnerabilityPattern.hpp"

/**
 * @brief Loads vulnerability patterns from a YAML file.
 */
class PatternLoader {
public:
    /**
     * @brief Loads vulnerability patterns from the given file path.
     * 
     * @param filepath Path to the YAML file containing vulnerability patterns.
     * @return std::vector<VulnerabilityPattern> List of loaded patterns.
     */
    static std::vector<VulnerabilityPattern> loadPatterns(const std::string& filepath);
};
