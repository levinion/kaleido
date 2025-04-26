#include "kaleido/preset.hpp"

namespace kaleido {

void PresetList::add_preset(
  std::string name,
  std::vector<std::string> shaders
) {
  this->prefixes[name] = shaders;
}

std::vector<std::string> PresetList::get_preset(std::string name) {
  return this->prefixes[name];
}
} // namespace kaleido
