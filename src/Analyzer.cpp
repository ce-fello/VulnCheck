#include "Analyzer.hpp"
#include <fstream>
#include <regex>

std::vector<MatchResult> Analyzer::analyzeFile(
    const std::string& filepath,
    const std::vector<VulnerabilityPattern>& patterns) 
{
    std::ifstream file(filepath);
    std::vector<MatchResult> results;
    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        ++lineNumber;
        for (const auto& pattern : patterns) {
            bool match = false;
            if (pattern.type == PatternType::Plain) {
                match = line.find(pattern.pattern) != std::string::npos;
            } else {
                try {
                    std::regex expr(pattern.pattern);
                    match = std::regex_search(line, expr);
                } catch (...) {
                    
                }
            }

            if (match) {
                results.push_back({filepath, lineNumber, pattern.id, pattern.message});
            }
        }
    }

    return results;
}
