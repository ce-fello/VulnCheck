#include "Analyzer.hpp"
#include "PatternLoader.hpp"
#include <iostream>
#include "utils/AnsiColor.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: sast-analyzer <pattern_file> <source_file>\n";
        return 1;
    }

    try {
        auto patterns = PatternLoader::loadPatterns(argv[1]);
        auto results = Analyzer::analyzeFile(argv[2], patterns);
        std::cout << "Found " << results.size() << " vulnerabilities\n" << "\n";
        for (const auto& result : results) {
            std::cout << AnsiColor::colorSeverity(result.severity)
                      << "[" << result.severity << "] "
                      << AnsiColor::RESET
                      << result.file << ":" << result.line << " [ "
                      << result.id << " ] "
                      << result.message << "\n";
        
            std::cout << "    "
                      << AnsiColor::highlightMatch(result.codeLine, result.highlightRange)
                      << "\n\n";
        }

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
