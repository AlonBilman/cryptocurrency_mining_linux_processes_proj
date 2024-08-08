Hey! This is a summary for the program in this repository. Thank you for reading! :)
--------------------------------------------------------------------------------------------


Building upon the foundation established in https://github.com/AlonBilman/cryptocurrency_mining_linux_thread_proj, 

Ive enhanced the simulation by containerizing the server and miner applications using Docker, transitioning from a multithreaded to a multiprocess architecture. 
Each component now operates in a separate container, utilizing named pipes for inter-process communication. This upgrade introduced both blocking and non-blocking approaches, improving data handling and mining efficiency.

The system's deployment is fully automated with a custom bash script (launcher.sh). This script handles everything from creating necessary directories and pulling Docker images from DockerHub to launching the server and miner containers. 
It also configures the system's mining difficulty.

Server Image: Manages miner subscriptions and block validation. It reads configuration data, such as block difficulty, from a mounted configuration file, ensuring a seamless and consistent setup.

Miner Image: Contains the mining process, which subscribes to the server and listens for the current block data. It continuously checks for new blocks and submits mined blocks back to the server, using a non-blocking approach.

The Docker images are lightweight, ensuring quick deployment and efficient resource use. 

Docker Hub links : 
 - Server image : https://hub.docker.com/repository/docker/alonbilman/coin_server_img/general 
 - Miner image : https://hub.docker.com/repository/docker/alonbilman/coin_miner_img/general
				   
The image sizes are 77.9 MB (both)

You can run the program with the script provided (launcher.sh)

(!) The script will *create or rewrite* the file /tmp/mtacoin in your mechine. 
	than it will create inside "mtacoin.conf" and write there "DIFFICULTY=16" 
	it will pull the images from the dockerhub and run a server and 3 miners. 
 
(!) You can kill any miner you want and run new ones 
 
(!) Make sure running the script with sudo in order to change /tmp and run docker-commands.



