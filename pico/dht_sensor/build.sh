#!/bin/bash
mkdir -p build
cd build || return
cmake ..
make -j$(nproc)

cp dht_sensor.uf2 /run/media/narat/RPI-RP2/.
sync
