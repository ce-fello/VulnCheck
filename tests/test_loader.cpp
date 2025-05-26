#include "doctest.h"
#include "PatternLoader.hpp"
#include <fstream>
#include <cstdio>

TEST_CASE("PatternLoader loads YAML patterns correctly") {
    std::string yamlData = R"(
- id: "test-eval"
  message: "Use of eval() is dangerous"
  pattern: "eval("
  severity: "high"
  tags: ["code-execution"]
- id: "test-sql"
  message: "SQL injection"
  pattern: "SELECT.*\" \\+"
  pattern_type: regex
  severity: "high"
  tags: ["sql", "injection"]
)";

    std::string tmpFile = "test_patterns.yaml";
    std::ofstream out(tmpFile);
    REQUIRE(out);
    out << yamlData;
    out.close();

    auto patterns = PatternLoader::loadFromFile(tmpFile);
    CHECK(patterns.size() == 2);
    CHECK(patterns[0].id == "test-eval");
    CHECK(patterns[1].type == PatternType::Regex);
    CHECK(patterns[1].severity == "high");

    std::remove(tmpFile.c_str());
}
