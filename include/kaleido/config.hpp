#pragma once
#include <toml++/toml.hpp>

namespace kaleido {
class Configuration {
public:
  Configuration();

  std::string display;
  std::vector<std::string> shaders;

private:
};
} // namespace kaleido
