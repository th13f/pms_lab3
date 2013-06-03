#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include "serve_cli.c"

//#define PTHREAD

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[1025];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(listenfd, 10);
    printf("Server started listening...\n");

    while (1) {
    	pid_t forkID;
		pthread_t pt;

		connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

#ifdef PTHREAD
		pthread_create(&pt, NULL, serve_client, (void *) &connfd);
		printf("\nClient connected.\n");
		fflush(stdout);
#else
		forkID = fork();
		if (forkID < 0) {
			printf("\nFork failed.\n");
			fflush(stdout);
			continue;
		} else if (forkID == 0) {
			printf("\nClient connected.\n");
			fflush(stdout);
			close(listenfd);
			serve_client((void *) &connfd);
			return 0;
		}
		close(connfd);
#endif
    }

    return 0;
}
