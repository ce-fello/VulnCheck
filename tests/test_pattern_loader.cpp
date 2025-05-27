#include "doctest.h"

#include "PatternLoader.hpp"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

std::string writeTempYAML(const std::string& name, const std::string& content) {
    std::ofstream out(name);
    out << content;
    out.close();
    return name;
}

TEST_CASE("PatternLoader loads valid YAML patterns") {
    std::string yaml = R"(
- id: "test-eval"
  message: "Use of eval"
  pattern: "eval("
  type: "plain"
  severity: "high"
  tags: ["eval", "code-execution"]

- id: "sql-injection"
  message: "SQL Injection risk"
  pattern: "SELECT.*\" \\+"
  type: "regex"
  severity: "medium"
  tags: ["sql", "injection"]
)";
    std::string path = writeTempYAML("test_patterns.yaml", yaml);

    auto patterns = PatternLoader::loadPatterns(path);
    CHECK(patterns.size() == 2);

    CHECK(patterns[0].id == "test-eval");
    CHECK(patterns[0].type == "plain");
    CHECK(patterns[0].severity == "high");
    CHECK(patterns[0].tags == std::vector<std::string>{"eval", "code-execution"});

    CHECK(patterns[1].id == "sql-injection");
    CHECK(patterns[1].type == "regex");
    CHECK(patterns[1].severity == "medium");

    fs::remove(path);
}

TEST_CASE("PatternLoader assigns default values when optional fields are missing") {
    std::string yaml = R"(
- id: "missing-fields"
  message: "Some message"
  pattern: "something"
)";
    std::string path = writeTempYAML("missing.yaml", yaml);

    auto patterns = PatternLoader::loadPatterns(path);
    REQUIRE(patterns.size() == 1);
    CHECK(patterns[0].type == "plain");
    CHECK(patterns[0].severity == "low");
    CHECK(patterns[0].tags.empty());

    fs::remove(path);
}

TEST_CASE("PatternLoader handles malformed YAML") {
    std::string invalidYaml = R"(
- id: "bad
  message: "Broken YAML
)";
    std::string path = writeTempYAML("broken.yaml", invalidYaml);

    auto patterns = PatternLoader::loadPatterns(path);
    CHECK(patterns.empty());

    fs::remove(path);
}

TEST_CASE("PatternLoader handles non-sequence YAML") {
    std::string notAList = R"(
id: "not-a-list"
message: "Should be top-level list"
)";
    std::string path = writeTempYAML("notalist.yaml", notAList);

    auto patterns = PatternLoader::loadPatterns(path);
    CHECK(patterns.empty());

    fs::remove(path);
}
