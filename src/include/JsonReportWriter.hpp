#pragma once

#include <vector>
#include <string>
#include <json.hpp>
#include <MatchResult.hpp>

/**
 * @brief Responsible for writing analysis results to a JSON report.
 */
class JsonReportWriter {
public:
    /**
     * @brief Writes the list of vulnerability matches to a JSON file.
     * 
     * @param vulns List of matched vulnerabilities.
     * @param outputPath Path to the output JSON file.
     */
    static void write(const std::vector<MatchResult>& vulns, const std::string& outputPath);
};
