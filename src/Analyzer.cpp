#include "Analyzer.hpp"
#include <fstream>
#include <sstream>

std::vector<MatchResult> Analyzer::analyzeFile(const std::string& filepath, const std::vector<VulnerabilityPattern>& patterns) {
    std::ifstream file(filepath);
    std::vector<MatchResult> results;
    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        ++lineNumber;
        for (const auto& pattern : patterns) {
            if (line.find(pattern.pattern) != std::string::npos) {
                results.push_back({filepath, lineNumber, pattern.id, pattern.message});
            }
        }
    }

    return results;
}
