#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080

/**
 * handle_server - to handle the server
 * @arg: argument
 * Return: void
 */
void *handle_server(void *arg)
{
	int server_socket = *(int *)arg;
	char buffer[1024] = {0};

	while (1)
	{
		read(server_socket, buffer, 1024);
		printf("Server: %s\n", buffer);
		memset(buffer, 0, sizeof(buffer));
	}
	return (NULL);
}

/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int server_socket;
	struct sockaddr_in address;
	char buffer[1024] = {0};

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);

	connect(server_socket, (struct sockaddr *)&address, sizeof(address));
	pthread_t thread_id;

	pthread_create(&thread_id, NULL, handle_server, (void *)&server_socket);

	while (1)
	{
		printf("Enter message for server: ");
		fgets(buffer, 1024, stdin);
		send(server_socket, buffer, strlen(buffer), 0);
		memset(buffer, 0, sizeof(buffer));
	}

	return (0);
}
