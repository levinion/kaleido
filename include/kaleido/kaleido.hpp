#include <X11/Xlib.h>
#include "kaleido/config.hpp"
#include "kaleido/result.hpp"
#include <hierro/app/app.hpp>
#include <xwrap/xwrap.hpp>

namespace kaleido {
class Kaleido {
public:
  static KaleidoResult<std::unique_ptr<Kaleido>> init(Configuration&& conf);
  KaleidoResult<void> run();

private:
  hierro::Video* video;
  xwrap::XwrapWindow window;
  Display* display;
  hierro::Application* app;
  bool upscaling_on = false;
  Configuration conf;

  KaleidoResult<void> init_hierro(int width, int height);
  void init_video();
};
} // namespace kaleido
