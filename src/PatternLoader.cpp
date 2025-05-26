#include "PatternLoader.hpp"
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <iostream>

std::vector<VulnerabilityPattern> PatternLoader::loadPatterns(const std::string& filepath) {
    std::vector<VulnerabilityPattern> patterns;

    try {
        YAML::Node config = YAML::LoadFile(filepath);
        if (!config.IsSequence()) {
            std::cerr << "Invalid pattern file format: expected a sequence\n";
            return patterns;
        }

        for (const auto& node : config) {
            VulnerabilityPattern pattern;
            pattern.id = node["id"] ? node["id"].as<std::string>() : "";
            pattern.message = node["message"] ? node["message"].as<std::string>() : "";
            pattern.pattern = node["pattern"] ? node["pattern"].as<std::string>() : "";
            pattern.type = node["type"] ? node["type"].as<std::string>() : "plain";
            pattern.severity = node["severity"] ? node["severity"].as<std::string>() : "low";

            if (node["tags"] && node["tags"].IsSequence()) {
                for (const auto& tag : node["tags"]) {
                    pattern.tags.push_back(tag.as<std::string>());
                }
            }

            patterns.push_back(pattern);
        }
    } catch (const YAML::Exception& e) {
        std::cerr << "Error parsing YAML file: " << e.what() << std::endl;
    }

    return patterns;
}
