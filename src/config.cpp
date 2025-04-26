#include "kaleido/config.hpp"
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <string>
#include <spdlog/spdlog.h>

namespace kaleido {

std::string getenv(const char* env) {
  auto e = std::getenv(env);
  return e == nullptr ? std::string("") : std::string(e);
}

std::optional<std::filesystem::path> get_config_path() {
  auto _root = getenv("XDG_CONFIG_HOME");
  std::filesystem::path p;
  if (!_root.empty())
    p.append(_root);
  else {
    auto _home = getenv("HOME");
    p.append(_home);
    p.append(".config");
  }
  p.append("kaleido");
  p.append("kaleido.toml");
  if (std::filesystem::exists(p))
    return p;
  else
    return {};
}

Configuration::Configuration() {
  // auto path = get_config_path();
  // if (path) {
  //   std::string name;
  //   std::vector<std::string> shaders;
  //
  //   toml::table conf = toml::parse_file(path.value().string());
  //   conf["preset"].as_array()->for_each([&](auto&& preset) {
  //     toml::table p = *preset.as_table();
  //     name = p["name"].value<std::string>().value();
  //     p["shaders"].as_array()->for_each([&](auto&& shader) {
  //       shaders.push_back(static_cast<std::string>(*shader.as_string()));
  //     });
  //   });
  //
  //   this->presets.add_preset(name, shaders);
  // }
}
} // namespace kaleido
