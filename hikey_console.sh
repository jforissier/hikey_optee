#!/bin/bash
#
# miniterm.py is in Ubuntu package python-serial
# $ sudo apt-get install python-serial
#
# Adjust USB device as needed

miniterm.py --lf /dev/ttyUSB0 115200
