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

exe "cd /projects/delivery-bot && mkdir build";
exe "/usr/bin/cmake -DCMAKE_BUILD_TYPE=Debug -G \"CodeBlocks - Unix Makefiles\" -S /projects/delivery-bot/ -B /projects/delivery-bot/build/";
exe "/usr/bin/cmake --build /projects/delivery-bot/build --target DeliveryBot${target} -- -j 20";
exe "cp config/$1/$1.ini build/$1/$1.ini"
exe "mosquitto -v -p $MQTT_PORT";