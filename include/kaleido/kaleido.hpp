#include <X11/Xlib.h>
#include "kaleido/config.hpp"
#include "kaleido/prefix.hpp"
#include <hierro/app.hpp>
#include <xwrap/xwrap.hpp>

namespace kaleido {
class Kaleido {
public:
  Kaleido(const Configuration& conf);
  void run();

private:
  Prefixes prefixes;
  hierro::Video* video;
  xwrap::XwrapWindow window;
  Display* display;
  hierro::Application* app;
  bool upscaling_on = false;
};
} // namespace kaleido
