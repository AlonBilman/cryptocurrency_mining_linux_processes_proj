
FROM ubuntu:22.04


WORKDIR /root/mtacoin_miner_app
COPY . .

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    g++ \
    libz-dev \
    && rm -rf /var/lib/apt/lists/*\
    && g++ -std=c++17 -o coin_miner main.cpp miner.cpp block.cpp global.cpp -lz 


CMD ["./coin_miner"]
