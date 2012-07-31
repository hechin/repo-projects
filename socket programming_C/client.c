/* Herman Chin
   CE150L
   Final Lab Project
   client.c 

   Description:

The client side of the project, this program creates a socket and binds it to a port then sends the packets of the ID and Nominee taken from the command line in the form: client Nominee HostIP UserID. 
Then the client will listen on port 1337 for the preparation packet from the server to prepare for a certain amount of recv. The client then recv and prints the results to the terminal.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#define PORT "1337" // the port client will be connecting to 

#define MAXDATASIZE 100 // max number of bytes we can get at once 

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
    int sockfd, numbytes;  
    char buf[MAXDATASIZE];
    char recvbuf[MAXDATASIZE];
    char votebuf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    int prep = 0;
    int counter = 0;
    int thevote;

    if (argc != 4) {
        fprintf(stderr,"usage: client nominee hostname userID\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[2], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

// send nominee/ID
    if (send(sockfd,argv[1] , MAXDATASIZE-1, 0) == -1)
            perror("send");
    if (send(sockfd,argv[3] , MAXDATASIZE-1, 0) == -1)
            perror("send");
// recieve num of recv to prepare for 
    if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
        perror("recv");
        exit(1);
    }

    buf[numbytes] = '\0';
    prep = atoi(buf);
    printf("client: received '%d'\n",prep);
// accept recv
    printf("Results: \n");
    for(counter = 0;counter<prep+1;counter++){
	for(rv = 0;rv<MAXDATASIZE-1;rv++){recvbuf[rv] = 0;}
	if(counter == 0){
	        if ((numbytes = recv(sockfd, recvbuf, MAXDATASIZE-1, 0)) == -1) {
	                perror("recv");
	                exit(1);
	        }
	}else{	
		if ((numbytes = recv(sockfd, recvbuf, MAXDATASIZE-1, 0)) == -1) {
	        perror("recv");
	        exit(1);
        	}
		recvbuf[numbytes] = '\0';
		printf("  %s",recvbuf);
		if ((numbytes = recv(sockfd, votebuf, MAXDATASIZE-1, 0)) == -1) {
                	perror("recv");
                	exit(1);
        	}
                votebuf[numbytes] = '\0';
		thevote = atoi(votebuf);
		printf("  %d\n",thevote);
	}
    }
    close(sockfd);

    return 0;
}
