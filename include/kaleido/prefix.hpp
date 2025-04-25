#pragma once

#include <filesystem>
#include <unordered_map>
#include <vector>
#include <hierro/widget/video.hpp>

namespace kaleido {

class Prefix {
public:
  void add_shader(std::filesystem::path path);
  void toggle(hierro::Video* video);
  inline bool is_selected();

private:
  std::vector<std::filesystem::path> shaders;
  bool selected;
};

class Prefixes {
private:
  std::unordered_map<std::string, Prefix> prefixes;
};

} // namespace kaleido
