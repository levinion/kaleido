# Kaleido

> **Kaleido** is a real‑time window upscaler that applies GPU‑accelerated GLSL shaders to any application window, delivering crisp, high‑fidelity visuals.

---

## 📖 Table of Contents

1. [Features](#-features)
2. [Prerequisites](#-prerequisites)
3. [Installation](#-installation)
4. [Usage (X11)](#-usage-x11)
5. [Virtual Display Example](#virtual-display-example)
6. [Future Plans](#-future-plans)
7. [License](#-license)

---

## ⚙️ Features

- **Universal Shader Support**: Load any [MPV](https://github.com/mpv-player/mpv)-compatible GLSL shader (e.g., [Anime4K](https://github.com/bloc97/Anime4K), [ArtCNN](https://github.com/lltcggie/waifu2x-caffe), [FSRCNN](https://github.com/HighVoltageRocknRoll/FSRCNN-TensorFlow)).
- **X11 Compatibility**: To ensure correct full-screen behavior without interference from the window manager, Kaleido requires either a second physical monitor or a virtual display (e.g., via [Xvfb](https://www.x.org/releases/X11R7.6/doc/man/man1/Xvfb.1.xhtml)).
- **Extensible Platform Support**: Planned Windows and Wayland backends, plus headless streaming via [SPICE](https://www.spice-space.org), VNC, etc.\

## 📋 Prerequisites

Before building Kaleido, install the following dependencies on your distribution:

```bash
sudo pacman -S --needed \
  cli11 spdlog mpv freetype2 glfw sdl3 just cmake
```

You also need a C++26‑compliant compiler and an OpenGL‑capable GPU.

---

## 🔧 Installation

1. **Clone the repository**

   ```bash
   git clone https://github.com/levinion/kaleido.git
   cd kaleido
   ```

2. **Build with Just**

   ```bash
   just init
   just install
   ```

---

## 🖥 Usage (X11)

Kaleido requires a display that bypasses your window manager. You can use a physical second monitor or create a virtual one with Xvfb.

```bash
sudo pacman -S xorg-server-xvfb
```

### Virtual Display Example

```bash
#!/usr/bin/env bash

# 1. Choose a display number
display=3

# 2. (Optional) High‑DPI environment tweaks
export GDK_DPI_SCALE=-1
export GDK_SCALE=1
export QT_AUTO_SCREEN_SCALE_FACTOR=1
export QT_ENABLE_HIGHDPI_SCALING=0
export QT_SCALE_FACTOR=1

# 3. Launch Chromium on a virtual screen
xvfb-run -n $display --server-args="-screen 0 1920x1080x24" chromium &

# 4. Wait for Xvfb
sleep 5

# 5. Start Kaleido with shaders
kaleido :$display \
  --shader ../assets/shaders/Anime4K_v4.0/Anime4K_Clamp_Highlights.glsl \
  --shader ../assets/shaders/Anime4K_v4.0/Anime4K_Restore_CNN_VL.glsl \
  --shader ../assets/shaders/Anime4K_v4.0/Anime4K_Upscale_CNN_x2_VL.glsl

# 6. Cleanup
pkill Xvfb
```

> **Tip:** Adjust `--shader` paths and display resolution as needed.

---

## 🔮 Future Plans

- **Windows & Wayland**: Native backends for broader OS support.
- **Headless & VM Streams**: Direct integration with SPICE, VNC, QEMU.

---

## 📄 License

Kaleido is released under the GNU General Public License (GPL). See the [LICENSE](LICENSE) file for details.
