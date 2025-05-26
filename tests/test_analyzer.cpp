#include "doctest.h"
#include "Analyzer.hpp"
#include "VulnerabilityPattern.hpp"
#include <fstream>
#include <cstdio>

TEST_CASE("Analyzer detects both plain and regex patterns") {
    std::string testFile = "test_sample.py";
    std::ofstream file(testFile);
    REQUIRE(file);
    file << "eval(user_input)\n";
    file << "query = \"SELECT * FROM users WHERE name = \" + user_input\n";
    file.close();

    std::vector<VulnerabilityPattern> patterns = {
        {"test-eval", "Dangerous eval", "eval(", "plain", "high", {"code-execution"}},
        {"test-sql", "SQL injection", "SELECT.*\\+.*", "regex", "high", {"sql"}}
    };

    auto results = Analyzer::analyzeFile(testFile, patterns);
    CHECK(results.size() == 2);
    CHECK(results[0].id == "test-eval");
    CHECK(results[1].id == "test-sql");

    std::remove(testFile.c_str());
}
