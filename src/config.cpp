#include "kaleido/config.hpp"
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <spdlog/spdlog.h>

namespace kaleido {

std::string getenv(const char* env) {
  auto e = std::getenv(env);
  return e == nullptr ? std::string("") : std::string(e);
}

std::optional<std::filesystem::path> get_config_path() {
  auto _root = getenv("XDG_CONFIG_HOME");
  auto _home = getenv("HOME");
  std::filesystem::path p;
  if (!_root.empty())
    p.append(_root);
  else {
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
  //   toml::table conf = toml::parse_file(path.value().string());
  //   auto presets = conf["presets"];
  //   // spdlog::info("{}", presets);
  //   std::cout << presets << std::endl;
  // }
}
} // namespace kaleido
