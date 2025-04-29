#include "kaleido/kaleido.hpp"
#include <mpv/client.h>
#include "hierro/utils/data.hpp"
#include "hierro/widget/video.hpp"
#include "kaleido/config.hpp"
#include "kaleido/result.hpp"
#include "spdlog/spdlog.h"
#include "hierro/app/app.hpp"

namespace kaleido {
KaleidoResult<std::unique_ptr<Kaleido>> Kaleido::init(Configuration&& conf) {
  if (!conf.current_preset.empty() && conf.shaders.empty()) {
    conf.shaders = conf.presets.get_preset(conf.current_preset);
  }

  auto kaleido = std::make_unique<Kaleido>();

  // init x window
  kaleido->conf = conf;
  kaleido->display = xwrap::XwrapDisplay(kaleido->conf.display);
  kaleido->window = xwrap::XwrapWindow::from_root(kaleido->display);
  auto attributes = kaleido->window.get_attributes();

  kaleido_check(kaleido->init_hierro(attributes.width, attributes.height));
  kaleido->init_video();

  return kaleido;
}

KaleidoResult<void> Kaleido::run() {
  // set fullscreen
  for (auto& child : window.get_children()) {
    auto child_attr = child.get_attributes();
    auto root_attr = window.get_attributes();
    if (child_attr.width != root_attr.width
        || child_attr.height != root_attr.height || child_attr.x != root_attr.x
        || child_attr.y != root_attr.y)
      child.fullscreen(true);
  }

  app
    ->on_update([&]() {
      auto im = window.get_image();
      video->update((unsigned char*)im.pixels, im.height * im.width * 4);
      return true;
    })
    ->on_render([&]() { video->render(); })
    ->on_destroy([&]() {
      video->terminate();
      window.end_get_image();
    });

  window.begin_get_image();
  return app->run();
}

KaleidoResult<void> Kaleido::init_hierro(int width, int height) {
  // init app window
  app = hierro::Application::get_instance();
  hierro::WindowSettings settings;
  settings.resizable = false;
  settings.floating = true;
  settings.passthrough = false;
  settings.transparent = false;
  settings.decorated = false;
  settings.title = "kaleido";
  settings.size = { width, height };
  settings.position = { 0, 0 };
  settings.fullscreen = true;
  settings.frame_limit = this->conf.frame_limit;
  return app->init<hierro::SDLBackend>(settings);
}

void Kaleido::init_video() {
  // init video widget
  auto attr = window.get_attributes();
  video = app->add_child<hierro::Video>();
  hierro::VideoSettings settings;
  settings.flip_y = true;
  settings.gl_format = GL_BGRA;
  settings.format = "bgra";
  settings.frame_size = { attr.width, attr.height };
  video->init(settings);
  this->video->set_size(1, 1);
  this->video->set_position(0, 1);

  // key mapping
  video
    ->on_key([&](hierro::KeyEvent e) {
      if (e.key == hierro::Key::F && e.press) {
        spdlog::info("frame_rate: {}", app->get_frame_rate());
      }
      if (e.match(hierro::Key::LCtrl, hierro::Key::M) && e.press) {
        upscaling_on ? upscaling_on = false : upscaling_on = true;
        spdlog::info("upscaling: {}", upscaling_on);
        video->send_command(
          { "show-text",
            fmt::format("upscaling mode {}", upscaling_on ? "on" : "off"),
            "2000" }
        );
        for (auto& shader : this->conf.shaders) {
          video->send_command(
            { "change-list", "glsl-shaders", "toggle", shader }
          );
        }
      }
      spdlog::debug("scancode: {}, press: {}", (int)e.key, e.press);
      window.send_key(static_cast<xwrap::Key>(e.key), e.press);
    })
    ->on_click([&](hierro::ClickEvent e) {
      window.send_button(static_cast<xwrap::MouseButton>(e.button), e.press);
      spdlog::debug(
        "button: {}, press: {} ; cursor: {}:{}",
        (int)e.button,
        (bool)e.press,
        e.position.x,
        e.position.y
      );
    })
    ->on_mouse_move([&](hierro::MouseMoveEvent e) {
      auto [width, height] = app->window_size();
      auto attributes = window.get_attributes();
      window.set_cursor_position(
        e.position.x * attributes.width / width,
        e.position.y * attributes.height / height
      );
    })
    ->on_mouse_wheel([&](hierro::MouseWheelEvent e) {
      spdlog::debug("mouse wheel: {}", e.y);
      window.send_mouse_wheel(e.y);
    });

  this->app->set_focus(video);
}
} // namespace kaleido
