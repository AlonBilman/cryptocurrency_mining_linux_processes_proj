#building the binary code
FROM ubuntu:22.04 as builder

WORKDIR /root/mtacoin_server_app
COPY . .

RUN apt-get update && \
    apt-get install -y \
    g++ \
    libz-dev \
    && g++ -std=c++17 -o coin_server main.cpp server.cpp block.cpp global.cpp -lz

#fresh ubuntu with only the binery code
FROM ubuntu:22.04

WORKDIR /root/mtacoin_server_app

COPY --from=builder /root/mtacoin_server_app/coin_server .

CMD ["./coin_server"]
