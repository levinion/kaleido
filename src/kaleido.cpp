#include "kaleido/kaleido.hpp"
#include <mpv/client.h>
#include "kaleido/config.hpp"
#include "spdlog/spdlog.h"
#include "hierro/app.hpp"

namespace kaleido {
Kaleido::Kaleido(Configuration&& conf) {
  // init x window
  this->conf = conf;
  this->display = xwrap::XwrapDisplay(this->conf.display);
  this->window = xwrap::XwrapWindow::from_root(display);
  auto attributes = window.get_attributes();

  // init app window
  app = hierro::Application::get_instance();
  hierro::WindowSettings settings;
  settings.resizable = false;
  settings.floating = true;
  settings.passthrough = false;
  settings.transparent = false;
  settings.decorated = false;
  settings.title = "kaleido";
  settings.size = { (double)attributes.width, (double)attributes.height };
  settings.position = { (double)0, (double)0 };
  settings.fullscreen = true;
  if (!app->init<hierro::SDLBackend>(settings)) {
    spdlog::error("window init failed");
    exit(1);
  }

  // init video widget
  this->video = app->add_child<hierro::Video>();
  this->video->set_size(1, 1);
  this->video->set_position(0, 1);

  // key mapping
  video
    ->on_key([&](hierro::KeyEvent e) {
      if (e.key == hierro::Key::F && e.press) {
        spdlog::info("frame_rate: {}", app->get_frame_rate());
      }
      if (e.key == hierro::Key::M && e.press
          && e.is_pressed(hierro::Key::LCtrl)) {
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
      video->push_frame(im.pixels, im.height * im.width * 4);
      return true;
    })
    ->on_render([&]() { video->render(); })
    ->on_destroy([&]() { window.end_get_image(); });

  window.begin_get_image();
}

void Kaleido::run() {
  if (auto r = app->run(); !r) {
    spdlog::error("{}", r.error());
    exit(1);
  }
}
} // namespace kaleido
