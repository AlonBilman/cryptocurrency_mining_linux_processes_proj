
FROM ubuntu:22.04


WORKDIR /root/mtacoin_miner_app
COPY . .

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    g++ \
    libz-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*\
    && g++ -std=c++17 -o coin_miner main.cpp miner.cpp block.cpp global.cpp -lz \
    && rm -f main.cpp miner.cpp block.cpp global.cpp Dockerfile serverMessage.h miner.h global.h block.h

CMD ["./coin_miner"]
