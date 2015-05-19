#!/bin/bash
#
# miniterm.py is in Ubuntu package python-serial
# $ sudo apt-get install python-serial
#
# Adjust USB device as needed

# --lf: do not send CR+LF, send LF only
# This does not work in UEFI shell. Use 'Ctrl+T Ctrl+L' to switch to
# CR+LF mode again.
DEV=${1:-/dev/ttyUSB0}
miniterm.py --lf ${DEV} 115200
