#include "JsonReportWriter.hpp"
#include <fstream>

using json = nlohmann::json;

/**
 * @brief Writes a list of detected vulnerabilities to a JSON file.
 * 
 * This function iterates over a vector of `MatchResult` objects and creates a JSON
 * structure containing relevant information about each vulnerability, such as:
 * - File path
 * - Line number
 * - Pattern ID
 * - Message
 * - Severity
 * - Code line
 * 
 * The final output is formatted and saved to the file specified by `outputPath`.
 * 
 * @param vulns A vector of `MatchResult` entries representing detected vulnerabilities.
 * @param outputPath The path to the output file where the JSON data will be written.
 */

void JsonReportWriter::write(const std::vector<MatchResult>& vulns, const std::string& outputPath) {
    json j;

    for (const auto& vuln : vulns) {
        json item;
        item["file"] = vuln.file;
        item["line"] = vuln.line;
        item["id"] = vuln.id;
        item["message"] = vuln.message;
        item["severity"] = vuln.severity;
        item["code"] = vuln.codeLine;

        j["vulnerabilities"].push_back(item);
    }

    std::ofstream out(outputPath);
    out << j.dump(4);
}
