#!/bin/bash
#
# miniterm.py is in Ubuntu package python-serial
# $ sudo apt-get install python-serial
#
# Adjust USB device as needed

# --eol LF: do not send CR+LF, send LF only
# This does not work in UEFI shell. Use 'Ctrl+T Ctrl+L' to switch to
# CR+LF mode again.
DEV=${1:-/dev/ttyUSB0}
miniterm.py --eol LF ${DEV} 115200
