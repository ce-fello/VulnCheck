#include "Analyzer.hpp"
#include <fstream>
#include <regex>

/**
 * @brief Analyzes a file line by line using provided vulnerability patterns.
 * 
 * Each line is scanned for both plain-text and regex-based patterns. When a match is found,
 * the result is recorded with associated metadata including file, line number, severity, and code snippet.
 * 
 * @param filepath Path to the source file to be analyzed.
 * @param patterns List of vulnerability patterns to search for.
 * @return std::vector<MatchResult> List of all found vulnerability matches.
 */
std::vector<MatchResult> Analyzer::analyzeFile(const std::string& filepath, const std::vector<VulnerabilityPattern>& patterns) {
    std::vector<MatchResult> results;
    std::ifstream file(filepath);
    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        ++lineNumber;

        for (const auto& pattern : patterns) {
            std::smatch match;
            bool found = false;
            std::pair<size_t, size_t> highlight = {0, 0};

            if (pattern.type == "regex") {
                std::regex re(pattern.pattern);
                if (std::regex_search(line, match, re)) {
                    found = true;
                    highlight = {static_cast<size_t>(match.position()), static_cast<size_t>(match.position() + match.length())};
                }
            } else {
                size_t pos = line.find(pattern.pattern);
                if (pos != std::string::npos) {
                    found = true;
                    highlight = {pos, pos + pattern.pattern.length()};
                }
            }

            if (found) {
                results.push_back({
                    filepath,
                    lineNumber,
                    pattern.id,
                    pattern.message,
                    pattern.severity,
                    line,
                    highlight
                });
            }
        }
    }

    return results;
}
