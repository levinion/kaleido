#pragma once
#include <toml++/toml.hpp>
#include "kaleido/preset.hpp"

namespace kaleido {
class Configuration {
public:
  Configuration();

  std::string display;
  std::vector<std::string> shaders;
  PresetList presets;
  std::string current_preset;

private:
};
} // namespace kaleido
