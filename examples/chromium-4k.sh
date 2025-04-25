#!/usr/bin/bash

display=:3

xvfb-run -n 3 --server-args="-screen 0 3840x2160x24" chromium &
>/dev/null

sleep 5

kaleido $display

pkill Xvfb
