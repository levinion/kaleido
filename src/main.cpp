#include <CLI/CLI.hpp>
#include <xwrap/xwrap.hpp>
#include <hierro/app.hpp>
#include <hierro/component/block.hpp>
#include <hierro/window.hpp>
#include <hierro/backend/sdl.hpp>
#include <hierro/widget/video.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>
#include "CLI/CLI.hpp"
#include "kaleido/config.hpp"
#include "kaleido/kaleido.hpp"
#include <toml++/toml.hpp>

int main(int argc, char** argv) {
  spdlog::cfg::load_env_levels();
  auto conf = kaleido::Configuration();

  auto cli = CLI::App { "Upscaler GUI for Linux", "kaleido" };
  cli.add_option("display", conf.display, "X11 display")->required();
  cli.add_option("-s,--shader", conf.shaders, "glsl shaders")
    ->check(CLI::ExistingFile);
  cli.add_option("-p,--proset", conf.current_preset, "preset to use");
  CLI11_PARSE(cli, argc, argv);

  if (auto kaleido = kaleido::Kaleido::init(std::move(conf)); !kaleido) {
    spdlog::error("{}", kaleido.error());
    exit(1);
  } else {
    if (auto r = kaleido.value()->run(); !r) {
      spdlog::error("{}", kaleido.error());
      exit(1);
    }
  }
}
