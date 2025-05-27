#pragma once
#include <string>

/**
 * @brief Provides ANSI escape codes for terminal text coloring and formatting.
 */
namespace AnsiColor {
    const std::string RESET   = "\033[0m";   ///< Reset all attributes.
    const std::string RED     = "\033[31m";  ///< Red color.
    const std::string GREEN   = "\033[32m";  ///< Green color.
    const std::string YELLOW  = "\033[33m";  ///< Yellow color.
    const std::string BLUE    = "\033[34m";  ///< Blue color.
    const std::string MAGENTA = "\033[35m";  ///< Magenta color.
    const std::string CYAN    = "\033[36m";  ///< Cyan color.
    const std::string BOLD    = "\033[1m";   ///< Bold text.

    /**
     * @brief Returns an ANSI color sequence based on severity level.
     * 
     * @param severity Severity level ("critical", "high", etc.).
     * @return std::string Corresponding ANSI escape sequence.
     */
    inline std::string colorSeverity(const std::string& severity) {
        if (severity == "critical") return RED + BOLD;
        if (severity == "high")     return RED;
        if (severity == "medium")   return YELLOW + BOLD;
        if (severity == "low")      return CYAN;
        return RESET;
    }

    /**
     * @brief Highlights a range in a line of code using red bold color.
     * 
     * @param line The full line of code.
     * @param range Pair indicating start and end positions of the highlight.
     * @return std::string Highlighted string.
     */
    inline std::string highlightMatch(const std::string& line, std::pair<size_t, size_t> range) {
        if (range.first >= line.size() || range.second > line.size() || range.first >= range.second)
            return line;

        return line.substr(0, range.first) +
               RED + BOLD + line.substr(range.first, range.second - range.first) + RESET +
               line.substr(range.second);
    }
}
