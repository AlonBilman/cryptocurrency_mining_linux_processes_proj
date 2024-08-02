FROM ubuntu:20.04

WORKDIR /root/app
COPY . /root/app

RUN apt-get update && apt-get install -y \
g++ \
libz-dev

RUN g++ -o coin_server main.cpp server.cpp block.cpp global.cpp -lz

CMD [ "./coin_server" ]