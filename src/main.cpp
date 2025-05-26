#include "Analyzer.hpp"
#include "PatternLoader.hpp"
#include "utils/AnsiColor.hpp"
#include "Report/JsonReportWriter.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: sast-analyzer <pattern_file> <source_file_or_dir> [--json|-j] [--output <filename>] [--recursive|-r]\n";
        return 1;
    }

    std::string patternFile = argv[1];
    std::string sourcePath = argv[2];
    bool jsonOutput = false;
    bool recursive = false;
    std::string outputFile = "report.json";

    for (int i = 3; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--json" || arg == "-j") {
            jsonOutput = true;
        } else if (arg == "--output") {
            if (i + 1 < argc) {
                outputFile = argv[++i];
            } else {
                std::cerr << "Error: --output requires a filename\n";
                return 1;
            }
        } else if (arg == "--recursive" || arg == "-r") {
            recursive = true;
        }
    }

    try {
        auto patterns = PatternLoader::loadPatterns(patternFile);
        std::vector<MatchResult> allResults;

        if (fs::is_directory(sourcePath)) {
            if (!recursive) {
                std::cerr << "Error: source path is a directory, use --recursive to analyze recursively.\n";
                return 1;
            }

            for (const auto& entry : fs::recursive_directory_iterator(sourcePath)) {
                if (entry.is_regular_file() && entry.path().extension() == ".py") {
                    auto results = Analyzer::analyzeFile(entry.path().string(), patterns);
                    allResults.insert(allResults.end(), results.begin(), results.end());
                }
            }
        } else if (fs::is_regular_file(sourcePath)) {
            allResults = Analyzer::analyzeFile(sourcePath, patterns);
        } else {
            std::cerr << "Error: invalid source path.\n";
            return 1;
        }

        std::cout << "Found " << allResults.size() << " vulnerabilities\n\n";

        for (const auto& result : allResults) {
            std::cout << AnsiColor::colorSeverity(result.severity)
                      << "[" << result.severity << "] "
                      << AnsiColor::RESET
                      << result.file << ":" << result.line << " ["
                      << result.id << "] "
                      << result.message << "\n";

            std::cout << "    "
                      << AnsiColor::highlightMatch(result.codeLine, result.highlightRange)
                      << "\n\n";
        }

        if (jsonOutput) {
            JsonReportWriter::write(allResults, outputFile);
            std::cout << "JSON report written to " << outputFile << "\n";
        }

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
