#include "doctest.h"

#include "Analyzer.hpp"
#include "VulnerabilityPattern.hpp"

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void writeTempFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
    file.close();
}

TEST_CASE("Analyzer detects regex pattern") {
    std::string testFile = "temp_test_file_regex.py";
    writeTempFile(testFile, "user_input = input()\nsubprocess.Popen(user_input, shell=True)");

    std::vector<VulnerabilityPattern> patterns = {{
        "python-subprocess-shell",
        "Shell=True with user input is dangerous",
        "subprocess\\.Popen\\(user_input.*shell=True",
        "regex",
        "high",
        {"command", "injection"}
    }};

    auto results = Analyzer::analyzeFile(testFile, patterns);

    CHECK(results.size() == 1);
    CHECK(results[0].id == "python-subprocess-shell");
    CHECK(results[0].line == 2);
    CHECK(results[0].severity == "high");

    fs::remove(testFile);
}

TEST_CASE("Analyzer detects plain pattern") {
    std::string testFile = "temp_test_file_plain.py";
    writeTempFile(testFile, "eval('dangerous_code')");

    std::vector<VulnerabilityPattern> patterns = {{
        "python-eval",
        "Use of eval() is dangerous",
        "eval(",
        "plain",
        "high",
        {"eval", "code-execution"}
    }};

    auto results = Analyzer::analyzeFile(testFile, patterns);

    CHECK(results.size() == 1);
    CHECK(results[0].id == "python-eval");
    CHECK(results[0].line == 1);

    fs::remove(testFile);
}

TEST_CASE("Analyzer handles no matches") {
    std::string testFile = "temp_test_file_nomatch.py";
    writeTempFile(testFile, "print('safe')");

    std::vector<VulnerabilityPattern> patterns = {{
        "python-eval",
        "Use of eval() is dangerous",
        "eval(",
        "plain",
        "high",
        {"eval", "code-execution"}
    }};

    auto results = Analyzer::analyzeFile(testFile, patterns);
    CHECK(results.empty());

    fs::remove(testFile);
}

TEST_CASE("Analyzer detects multiple vulnerabilities") {
    std::string testFile = "temp_test_file_multiple.py";
    writeTempFile(testFile,
        "eval('x')\n"
        "exec('y')\n"
        "subprocess.Popen(user_input, shell=True)\n"
    );

    std::vector<VulnerabilityPattern> patterns = {
        {"python-eval", "Use of eval() is dangerous", "eval(", "plain", "high", {"eval"}},
        {"python-exec", "Use of exec() is dangerous", "exec(", "plain", "high", {"exec"}},
        {"python-subprocess", "subprocess shell=true", "subprocess\\.Popen\\(user_input.*shell=True", "regex", "high", {"command"}}
    };

    auto results = Analyzer::analyzeFile(testFile, patterns);

    CHECK(results.size() == 3);
    CHECK(results[0].line == 1);
    CHECK(results[1].line == 2);
    CHECK(results[2].line == 3);

    fs::remove(testFile);
}

TEST_CASE("Analyzer handles empty file") {
    std::string testFile = "temp_test_file_empty.py";
    writeTempFile(testFile, "");

    std::vector<VulnerabilityPattern> patterns = {
        {"python-eval", "Use of eval() is dangerous", "eval(", "plain", "high", {"eval"}}
    };

    auto results = Analyzer::analyzeFile(testFile, patterns);
    CHECK(results.empty());

    fs::remove(testFile);
}
