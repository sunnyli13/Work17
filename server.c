#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

void reverse(char *buffer){
	int len = strlen(buffer);

	for (int i = 0, j = len - 1; i < j; i++, j--) {
		char ch = buffer[i];
		buffer[i] = buffer[j];
		buffer[j] = ch;
	}
}

int main() {
	while (1) {
		mkfifo("toServer", 0644);
		printf("Server created\n");
		printf("Waiting for client...\n");

		int toServer = open("toServer", O_RDONLY);
		printf("Connecting...\n");

		char name[100];
		read(toServer, name, sizeof(name));
		printf("Received client name: %s\n", name);

		remove("toServer");
		printf("toServer removed\n");

		int toClient = open("toClient", O_WRONLY);
		printf("Connected to client\n");

		write(toClient, "Hello!", 7);
		printf("Confirmation sent\n");

		char confirm[100];
		read(toServer, confirm, sizeof(confirm));
		printf("Received Confirmation: %s\n", confirm);

		char stuff[100];

		while (read(toServer, &stuff, sizeof(stuff))) {
			reverse(stuff);
			write(toClient, &stuff, sizeof(stuff));
		}
	}
}