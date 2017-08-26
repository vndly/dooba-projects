#!/bin/bash

dbuild
sudo avrdude -c arduino -P /dev/ttyUSB0 -p atmega1284p -U flash:w:out/bin/tetris.hex
rm -rf ./out