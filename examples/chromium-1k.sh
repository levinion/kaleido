#!/usr/bin/bash

display=3

# environment for 1k screen
export GDK_DPI_SCALE=-1
export GDK_SCALE=1
export QT_AUTO_SCREEN_SCALE_FACTOR=1
export QT_ENABLE_HIGHDPI_SCALING=0
export QT_SCALE_FACTOR=1

# Xvfb $display -nolisten tcp -screen 0 3840x2160x24 > /dev/null 2>&1 &
# DISPLAY=:3 chromium > /dev/null 2>&1 &

# or just:
xvfb-run -n $display --server-args="-screen 0 1920x1080x24" chromium >/dev/null 2>&1 &

sleep 5

kaleido :$display \
  --shader "../assets/shaders/Anime4K_v4.0/Anime4K_Clamp_Highlights.glsl" \
  --shader "../assets/shaders/Anime4K_v4.0/Anime4K_Restore_CNN_VL.glsl" \
  --shader "../assets/shaders/Anime4K_v4.0/Anime4K_Upscale_CNN_x2_VL.glsl" \
  --shader "../assets/shaders/Anime4K_v4.0/Anime4K_AutoDownscalePre_x2.glsl" \
  --shader "../assets/shaders/Anime4K_v4.0/Anime4K_AutoDownscalePre_x4.glsl" \
  --shader "../assets/shaders/Anime4K_v4.0/Anime4K_Upscale_CNN_x2_M.glsl"

pkill Xvfb
