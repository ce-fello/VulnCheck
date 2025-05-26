#include "doctest.h"

#include "JsonReportWriter.hpp"
#include <fstream>
#include <json.hpp>
#include <filesystem>

namespace fs = std::filesystem;
using json = nlohmann::json;

TEST_CASE("JsonReportWriter writes a valid JSON report") {
    std::vector<MatchResult> vulns = {
        {
            "example.py",
            10,
            "eval-usage",
            "Use of eval() is dangerous",
            "high",
            "eval(user_input)",
            {0, 4}
        },
        {
            "example.py",
            25,
            "sql-injection",
            "Possible SQL injection",
            "medium",
            "cursor.execute(\"SELECT * FROM users WHERE name = \" + name)",
            {20, 30}
        }
    };

    std::string outputPath = "test_report.json";

    JsonReportWriter::write(vulns, outputPath);

    CHECK(fs::exists(outputPath));

    std::ifstream in(outputPath);
    json resultJson;
    in >> resultJson;

    CHECK(resultJson.contains("vulnerabilities"));
    CHECK(resultJson["vulnerabilities"].is_array());
    CHECK(resultJson["vulnerabilities"].size() == 2);

    const auto& first = resultJson["vulnerabilities"][0];
    CHECK(first["file"] == "example.py");
    CHECK(first["line"] == 10);
    CHECK(first["id"] == "eval-usage");
    CHECK(first["message"] == "Use of eval() is dangerous");
    CHECK(first["severity"] == "high");
    CHECK(first["code"] == "eval(user_input)");

    const auto& second = resultJson["vulnerabilities"][1];
    CHECK(second["line"] == 25);
    CHECK(second["severity"] == "medium");

    fs::remove(outputPath);
}
