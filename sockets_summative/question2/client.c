// Client Side (monitoring_process.c)
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dirent.h>

#define PORT 8080

// Function to add watch to directory and its contents recursively
void add_watch_recursive(int fd, const char *dirname)
{
	int wd = inotify_add_watch(fd, dirname, IN_OPEN | IN_CLOSE);
	if (wd == -1)
	{
		perror("inotify_add_watch");
		return;
	}

	DIR *dir = opendir(dirname);

	if (!dir)
	{
		perror("opendir");
		return;
	}

	struct dirent *entry;

	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == DT_DIR)
		{
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
			{
				char path[1024];

				sprintf(path, "%s/%s", dirname, entry->d_name);
				add_watch_recursive(fd, path);
			}
		} else if (entry->d_type == DT_REG)
		{
			char path[1024];

			sprintf(path, "%s/%s", dirname, entry->d_name);
			int wd = inotify_add_watch(fd, path, IN_OPEN | IN_CLOSE);
			if (wd == -1)
			{
				perror("inotify_add_watch");
			}
		}
	}

	closedir(dir);
}

char *get_event_type(struct inotify_event *event)
{
	if (event->mask & IN_OPEN)
	{
		return ("OPEN");
	} else if (event->mask & IN_CLOSE)
	{
		return ("CLOSE");
	}
	return ("");
}

/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int sockfd;
	struct sockaddr_in servaddr;
	char buffer[1024];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
	{
		perror("Connection to server failed");
		exit(EXIT_FAILURE);
	}

	int fd = inotify_init();

	if (fd == -1)
	{
		perror("inotify_init");
		exit(EXIT_FAILURE);
	}

	/*  Start monitoring the root directory */
	add_watch_recursive(fd, ".");

	while (1)
	{
		ssize_t len = read(fd, buffer, sizeof(buffer));

		if (len == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}

		/*  Parse the inotify_event structure */
		struct inotify_event *event = (struct inotify_event *)buffer;
		char *filename = event->name ? event->name : "";

		char event_type_str[20];

		sprintf(event_type_str, "%s", get_event_type(event));

		if (strcmp(filename, "") == 0)
		{
			sprintf(buffer, "%s, [No filename]\n", event_type_str);
		} else
		{
			sprintf(buffer, "%s, %s\n", event_type_str, filename);
		}

		printf("Sending data: %s", buffer);
		send(sockfd, buffer, strlen(buffer), 0);
	}

	close(sockfd);
	close(fd);

	return (0);
}
