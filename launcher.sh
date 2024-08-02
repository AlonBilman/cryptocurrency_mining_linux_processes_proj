
#!/bin/bash

#Creating the /tmp/mtacoin directory or empty it.

DIR="/tmp/mtacoin"

if [ ! -d "$DIR" ]; then
    echo "\nCreating /tmp/mtacoin....\n"
    mkdir -p "$DIR"
else
    # The directory exists, empty it
    echo "\nEmpying /tmp/mtacoin folder...\n"
    rm -rf "$DIR"/*
fi

cd "$DIR"

echo "Creating mtacoin.conf file\n"
#This will create mtacoin.conf and write to it
echo "DIFFICULTY=16" > "mtacoin.conf"

echo "Pulling the images... \n\n"
#Pull the images
docker pull "alonbilman/coin_server_img"
docker pull "alonbilman/coin_miner_img"
echo "\n-----------------------------------------------------------------------------\n"
echo "\nFinished...!\n\n	Make sure to run the server before the miners.\n"
echo "		The server image name : alonbilman/coin_server_img\n"
echo "		The miner image name : alonbilman/coin_miner_img\n"
echo "--------------------------------------------------------------------------------\n"
sleep 2
clear
echo "\n------------------------------------------\n"
echo "	Running a server and 3 miners...\n"
echo "------------------------------------------\n"
docker run -d -v /tmp/mtacoin/:/mnt/mta alonbilman/coin_server_img
sleep 0.5
docker run -d -v /tmp/mtacoin/:/mnt/mta alonbilman/coin_miner_img
sleep 0.5
docker run -d -v /tmp/mtacoin/:/mnt/mta alonbilman/coin_miner_img
sleep 0.5
docker run -d -v /tmp/mtacoin/:/mnt/mta alonbilman/coin_miner_img

echo "\nFinished. A server and 3 Miners are running..\n"
sleep 0.5
exit 1
