#include <print>
#include <string>
#include <xwrap/xwrap.hpp>
#include <hierro/app.hpp>
#include <hierro/component/block.hpp>
#include <hierro/window.hpp>
#include <hierro/backend/sdl.hpp>
#include "kaleido/kaleido.hpp"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::println("invalid params");
  }

  auto display = xwrap::XwrapDisplay(argv[1]);
  auto window = xwrap::XwrapWindow::from_root(display);

  auto app = hierro::Application::get_instance();
  auto attributes = window.get_attributes();

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
  settings.backend = new hierro::SDLBackend;

  app->init(settings).unwrap();

  hierro::Block block;
  block.set_size(1, 1);
  block.set_position(0, 1);
  block.border_thickness = 0;
  block.radius = 0;

  bool upscaling_on = false;

  block
    .on_key([&](hierro::KeyEvent e) {
      if (e.key == hierro::Key::F && e.press) {
        std::println("frame_rate: {}", app->get_frame_rate());
      }

      if (e.key == hierro::Key::O && e.press) {
        upscaling_on ? upscaling_on = false : upscaling_on = true;
        std::println("upscaling: {}", upscaling_on);
      }

      if (static_cast<bool>(e.mod)) {
        std::println("mod: {}, press: {}", (int)e.mod, e.press);
        window.send_key(static_cast<xwrap::Key>(e.mod), e.press);
      }
      std::println("scancode: {}, press: {}", (int)e.key, e.press);
      auto cursor = app->cursor_pos();
      window.send_key(static_cast<xwrap::Key>(e.key), e.press);
    })
    ->on_click([&](hierro::ClickEvent e) {
      window.send_button(static_cast<xwrap::MouseButton>(e.button), e.press);
      std::println(
        "button: {}, press: {} ; cursor: {}:{}",
        (int)e.button,
        (bool)e.press,
        e.position.x,
        e.position.y
      );
    })
    ->on_mouse_move([&](hierro::MouseMoveEvent e) {
      auto [width, height] = app->window_size();
      window.set_cursor_position(
        e.position.x * attributes.width / width,
        e.position.y * attributes.height / height
      );
      // window.set_cursor_relative_position(e.xrel, e.yrel);
    })
    ->on_mouse_wheel([&](hierro::MouseWheelEvent e) {
      std::println("mouse wheel: {}", e.y);
      window.send_mouse_wheel(e.y);
    });

  app->add_child(&block);

  for (auto& child : window.get_children()) {
    auto child_attr = child.get_attributes();
    auto root_attr = window.get_attributes();
    if (child_attr.width != root_attr.width
        || child_attr.height != root_attr.height || child_attr.x != root_attr.x
        || child_attr.y != root_attr.y)
      child.fullscreen(true);
  }

  window.begin_get_image();

  app
    ->on_update([&]() {
      block.free_texture();
      auto src = window.get_image();
      // auto image = upscaling_on ? kaleido::process_image(src, 2) : src;
      block.set_texture(src.pixels, src.width, src.height);
      return true;
    })
    ->on_destroy([&]() { window.end_get_image(); })
    ->run();
}
