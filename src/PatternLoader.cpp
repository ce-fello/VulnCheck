#include "PatternLoader.hpp"
#include <yaml-cpp/yaml.h>

std::vector<VulnerabilityPattern> PatternLoader::loadFromFile(const std::string& filepath) {
    YAML::Node root = YAML::LoadFile(filepath);
    std::vector<VulnerabilityPattern> patterns;

    for (const auto& node : root) {
        VulnerabilityPattern p;
        p.id = node["id"].as<std::string>();
        p.message = node["message"].as<std::string>();
        p.pattern = node["pattern"].as<std::string>();
        if (node["severity"]) p.severity = node["severity"].as<std::string>();
        if (node["tags"]) p.tags = node["tags"].as<std::vector<std::string>>();
        patterns.push_back(p);
    }

    return patterns;
}
