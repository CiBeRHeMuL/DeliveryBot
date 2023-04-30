#!/bin/sh

if [ "$1" = "server" ]; then
    target="Server";
elif [ "$1" = "bot" ]; then
    target="Bot";
else
    echo "Unknown target";
    exit 1;
fi

exe() { echo "$@"; eval "$@"; }

exe "mkdir build";
exe "/usr/bin/cmake -DCMAKE_BUILD_TYPE=Debug -G \"CodeBlocks - Unix Makefiles\" -S . -B ./build";
exe "/usr/bin/cmake --build ./build --target DeliveryBot$target -- -j 20";
exe "cp ./config/$1/$1.ini ./build/$1/$1.ini";

if [ "$1" = "server" ]; then
  exe "mosquitto -v -c ./config/mosquitto/mosquitto.conf";
elif [ "$1" = "bot" ]; then
  exe "cd ./build/$1";
  exe "./DeliveryBot$target";
fi
