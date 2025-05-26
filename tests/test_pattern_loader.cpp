#include "doctest.h"
#include "PatternLoader.hpp"
#include <fstream>
#include <cstdio>

TEST_CASE("PatternLoader loads YAML patterns") {
    std::string yamlContent = R"(
- id: "test-eval"
  message: "Use of eval() is dangerous"
  pattern: "eval("
  severity: "high"
  tags: ["code-execution"]
- id: "test-sql"
  message: "SQL injection"
  pattern: "SELECT.*\\+.*"
  pattern_type: regex
  severity: "high"
  tags: ["sql", "injection"]
)";

    std::string tempFile = "test_patterns.yaml";
    std::ofstream out(tempFile);
    REQUIRE(out.is_open());
    out << yamlContent;
    out.close();

    auto patterns = PatternLoader::loadFromFile(tempFile);
    CHECK(patterns.size() == 2);
    CHECK(patterns[0].id == "test-eval");
    CHECK(patterns[0].type == PatternType::Plain);
    CHECK(patterns[1].id == "test-sql");
    CHECK(patterns[1].type == PatternType::Regex);

    std::remove(tempFile.c_str());
}
