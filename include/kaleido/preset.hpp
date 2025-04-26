#pragma once

#include <vector>
#include <hierro/widget/video.hpp>

namespace kaleido {

class PresetList {
public:
  void add_preset(std::string name, std::vector<std::string> shaders);
  std::vector<std::string> get_preset(std::string name);

private:
  std::unordered_map<std::string, std::vector<std::string>> prefixes;
};

} // namespace kaleido
