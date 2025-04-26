#!/usr/bin/bash

display=3

xvfb-run -n $display --server-args="-screen 0 3840x2160x24" chromium >/dev/null 2>&1 &

sleep 5

kaleido :$display

pkill Xvfb
