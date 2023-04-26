FROM ubuntu:latest
LABEL authors="Andrey Gostev"

ENV DEBIAN_FRONTEND=noninteractive TZ=Etc/UTC+03

RUN apt-get update \
    && apt-get --no-install-recommends install -y util-linux gcc g++ clang gdb cmake make \
    autoconf automake dos2unix tar rsync git \
    openssl mosquitto mosquitto-clients libmosquittopp-dev libopencv-dev \
    && rm -rf /var/lib/apt/lists/* && apt autoremove && apt clean

RUN mkdir -p /projects/delivery-bot && cd /projects/delivery-bot
COPY ../../ /projects/delivery-bot

WORKDIR /projects/delivery-bot/

ENV PATH /projects/delivery-bot/build/bot:$PATH