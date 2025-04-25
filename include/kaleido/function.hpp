#pragma once

#include <filesystem>
#include <hierro/widget/video.hpp>

namespace kaleido {
void toggle_shader(hierro::Video* video, std::filesystem::path path);
}
