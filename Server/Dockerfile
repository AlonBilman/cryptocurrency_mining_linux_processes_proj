
FROM ubuntu:22.04

WORKDIR /root/mtacoin_server_app
COPY . .

RUN apt-get update && \
    apt-get install -y --no-install-recommends \ 
    g++ \
    libz-dev \
    && rm -rf /var/lib/apt/lists/* \
    && g++ -std=c++17 -o coin_server main.cpp server.cpp block.cpp global.cpp -lz

CMD ["./coin_server"]
