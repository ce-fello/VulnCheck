#pragma once
#include <string>

/**
 * @brief Represents a single vulnerability match result in a source file.
 */
struct MatchResult {
    std::string file;                ///< Path to the source file.
    int line;                        ///< Line number of the match.
    std::string id;                  ///< Vulnerability ID.
    std::string message;            ///< Description of the vulnerability.
    std::string severity;           ///< Severity level (e.g., "low", "critical").
    std::string codeLine;           ///< Full line of source code where the match occurred.
    std::pair<size_t, size_t> highlightRange; ///< Range of characters to highlight in the codeLine.
};
