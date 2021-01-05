#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
	mkfifo("toClient", 0644);
	printf("Client created pipe\n");

	int toServer = open("toServer", O_WRONLY);
	printf("Client connected to server\n");

	//client sends to server
	write(toServer,"toClient", 10);
	printf("Sent toClient pipe\n");
	printf("Waiting for Connection...\n");
	int toClient = open("toClient", O_RDONLY);
	printf("Server connected\n");

	remove("toClient");
	printf("Removed pipe\n");

	//client reads from server
	char confirm[100];
	read(toClient, confirm, sizeof(confirm));
	printf("Received confirmation: %s\n", confirm);

	//client sends to server
	write(toServer, confirm, sizeof(confirm));
	printf("Sent confirmation\n");
	printf("Done\n");

	char in[100];
	char out[100];

	printf("I Am Reverse9000!\n");

	while (1) {
		printf("Feed  me: ");

		scanf("%s", &in);
		write(toServer, &in, sizeof(in));
		read(toClient, &out, sizeof(out));

		printf("Reversed: %s\n\n", out);
	}

	return 0;
}