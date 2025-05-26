#include "Analyzer.hpp"
#include <fstream>
#include <regex>

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
