#!/usr/bin/bash

display=3

export GDK_DPI_SCALE=-1
export GDK_SCALE=1
export QT_AUTO_SCREEN_SCALE_FACTOR=1
export QT_ENABLE_HIGHDPI_SCALING=0
export QT_SCALE_FACTOR=1

xvfb-run -n $display --server-args="-screen 0 1920x1080x24" chromium &

sleep 5

kaleido :$display \
  --shader "../assets/shaders/FSRCNNX/FSRCNNX_x2_16-0-4-1.glsl"

pkill Xvfb
