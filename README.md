The files are : 
1. Server
2. Miner
3. launcher.sh
---------------------------------------------------------
docker hub links : server image : https://hub.docker.com/repository/docker/alonbilman/coin_server_img/general 
				   miner image : https://hub.docker.com/repository/docker/alonbilman/coin_miner_img/general
				   
The image sizes are 77.9 MB (both)
---------------------------------------------------------
You can run the program with the script provided (launcher.sh)
(!) the script will *create or rewrite* the file /tmp/mtacoin in your mechine. 
	than it will create inside "mtacoin.conf" and write there "DIFFICULTY=16" 
	it will pull the images from the dockerhub and run a server and 3 miners. 
	(!) the docker commands use the same mapping as shown in the screenshots 
	you can kill any miner you want and run new ones 
(!) make sure running the script with sudo in order to change /tmp and run docker-commands.
(!) run the script with sudo (for docker and for /tmp) 


