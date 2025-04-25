#include "kaleido/function.hpp"

namespace kaleido {
void toggle_shader(hierro::Video* video, std::filesystem::path path) {
  video->send_command({ "change-list", "glsl-shaders", "toggle", path });
}
} // namespace kaleido
