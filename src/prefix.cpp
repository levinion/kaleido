#include "kaleido/prefix.hpp"
#include "kaleido/function.hpp"

namespace kaleido {

void Prefix::add_shader(std::filesystem::path path) {
  this->shaders.push_back(path);
}

void Prefix::toggle(hierro::Video* video) {
  this->selected = this->selected ? false : true;
  for (auto& shader : this->shaders) {
    toggle_shader(video, shader);
  }
}

bool Prefix::is_selected() {
  return this->selected;
}
} // namespace kaleido
