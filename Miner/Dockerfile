FROM ubuntu:20.04

WORKDIR /root/app
COPY . /root/app

RUN apt-get update && apt-get install -y \
g++-8 \
libz-dev \
build-essential

RUN g++-8 -std=c++17 -o coin_miner main.cpp miner.cpp block.cpp global.cpp -lz

CMD [ "./coin_miner" ]