#!/usr/bin/bash

display=:3

# Xvfb $display -nolisten tcp -screen 0 3840x2160x24 &
# >/dev/null
xvfb-run -n 3 --server-args="-screen 0 3840x2160x24" chromium &
>/dev/null
# DISPLAY=$display chromium &

kaleido $display

pkill Xvfb
