#pragma once

#include <vector>
#include <string>
#include <json.hpp>
#include <MatchResult.hpp>

class JsonReportWriter {
public:
    static void write(const std::vector<MatchResult>& vulns, const std::string& outputPath);
};
