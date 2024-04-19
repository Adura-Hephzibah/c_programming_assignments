#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080

/**
 * handle_client - to handle client
 * @arg: argument
 * Return: void
 */
void *handle_client(void *arg)
{
	int client_socket = *(int *)arg;
	char buffer[1024] = {0};

	while (1)
	{
		read(client_socket, buffer, 1024);
		printf("Client: %s\n", buffer);
		memset(buffer, 0, sizeof(buffer));
		printf("Enter message for client: ");
		fgets(buffer, 1024, stdin);
		send(client_socket, buffer, strlen(buffer), 0);
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
	int server_socket, client_socket;
	struct sockaddr_in address;
	int addrlen = sizeof(address);

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	bind(server_socket, (struct sockaddr *)&address, sizeof(address));
	listen(server_socket, 3);
	printf("Server listening on port %d\n", PORT);

	while (1)
	{
		client_socket = accept(server_socket, (struct sockaddr *)&address,
									(socklen_t *)&addrlen);
		pthread_t thread_id;

		pthread_create(&thread_id, NULL, handle_client, (void *)&client_socket);
	}

	return (0);
}
