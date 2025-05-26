#include "Analyzer.hpp"
#include "PatternLoader.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: sast-analyzer <pattern_file> <source_file>\n";
        return 1;
    }

    try {
        auto patterns = PatternLoader::loadFromFile(argv[1]);
        auto results = Analyzer::analyzeFile(argv[2], patterns);

        for (const auto& res : results) {
            std::cout << res.file << ":" << res.line << " [" << res.id << "] " << res.message << "\n";
        }

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
