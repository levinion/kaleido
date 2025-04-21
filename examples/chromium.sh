#!/usr/bin/bash

display=:3

# Xvfb $display -nolisten tcp -screen 0 3840x2160x24 &
# >/dev/null

# xvfb-run -n 3 --server-args="-screen 0 3840x2160x24" chromium &
# >/dev/null

export GDK_DPI_SCALE=-1
export GDK_SCALE=1
export QT_AUTO_SCREEN_SCALE_FACTOR=1
export QT_ENABLE_HIGHDPI_SCALING=0
export QT_SCALE_FACTOR=1

xvfb-run -n 3 --server-args="-screen 0 1920x1080x24" chromium &
>/dev/null

sleep 5

kaleido $display

pkill Xvfb
