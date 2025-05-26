#include "PatternLoader.hpp"
#include <yaml-cpp/yaml.h>

PatternType parsePatternType(const YAML::Node& node) {
    if (node["pattern_type"] && node["pattern_type"].as<std::string>() == "regex") {
        return PatternType::Regex;
    }
    return PatternType::Plain;
}

std::vector<VulnerabilityPattern> PatternLoader::loadFromFile(const std::string& filepath) {
    YAML::Node root = YAML::LoadFile(filepath);
    std::vector<VulnerabilityPattern> patterns;

    for (const auto& node : root) {
        VulnerabilityPattern p;
        p.id = node["id"].as<std::string>();
        p.message = node["message"].as<std::string>();
        p.pattern = node["pattern"].as<std::string>();
        p.type = parsePatternType(node);
        if (node["severity"]) p.severity = node["severity"].as<std::string>();
        if (node["tags"]) p.tags = node["tags"].as<std::vector<std::string>>();
        patterns.push_back(p);
    }

    return patterns;
}
