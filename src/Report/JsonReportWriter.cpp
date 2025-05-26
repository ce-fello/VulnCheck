#include "JsonReportWriter.hpp"
#include <fstream>

using json = nlohmann::json;

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
