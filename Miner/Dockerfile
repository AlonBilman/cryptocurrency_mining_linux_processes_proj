#building the binary code
FROM ubuntu:22.04 as builder

WORKDIR /root/mtacoin_miner_app
COPY . .

RUN apt-get update && \
    apt-get install -y \
    g++ \
    libz-dev \
    && g++ -std=c++17 -o coin_miner main.cpp miner.cpp block.cpp global.cpp -lz 

#fresh ubuntu with only the binery code
FROM ubuntu:22.04

WORKDIR /root/mtacoin_miner_app

COPY --from=builder /root/mtacoin_miner_app/coin_miner .

CMD ["./coin_miner"]
