/* Herman Chin
   CE150L
   Final Lab Project
   server.c 

   Description: 

   This file creates a socket and binds it to port 1337. It then takes in the ID and Nominee from the client and adds it to nominee.txt file. It does this to store the values so that the program can access the data outside of the fork child process loop. 
The program opens up the votelist.txt and appends it to an array. The program then compares the nominee name to the names from nomlist.txt, if it exists then it will increment the votes associated with the name, if it does not exist then it will add it to the list and increment its votes. 
The program then exits its fork loop and draws data from nomlist.txt and votelist.txt to send to the client. The program sends an initial packet to the client to notify it of how many recv to prepare for, then, delivers the packets.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define PORT "1337"  // the port users will be connecting to
#define MAXBUFLEN 100
#define BACKLOG 10     // how many pending connections queue will hold

void sigchld_handler(int s)
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;
    char nomineebuf[MAXBUFLEN];
    char IDbuf[MAXBUFLEN];
    char *nominees[MAXBUFLEN];
    int votes[MAXBUFLEN];
    int IDs[MAXBUFLEN];
    int IDconversion = 0; // convert ID to this and check IDlist
    int listcounter = 0; // run through nominee/votes list and append
    int resultscounter = 0; // run through list and send
    int IDcounter = 0; // run through IDlist and append
    int IDcheck = 0; // run through IDlist to check for duplicates
    int IDused = 0; // boolean 0 free 1 used
    int existing = 0; // 1 for existng nominee
    FILE *fs, *ft, *fi, *fir, *snl, *votefile;
    int len;//len counter

// clear arrays
    for(listcounter = 0; listcounter<MAXBUFLEN-1;listcounter++){
	nominees[listcounter] = " ";
	votes[listcounter] = 0;
	IDs[listcounter] = 0;
    }
    listcounter = 0;
    remove("nomlist.txt");
    fs = fopen("nomlist.txt","w");
    fclose(fs);
    fs = fopen("votelist.txt","w");
    fclose(fs);

// set hints to getaddrinfo
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        return 2;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);
        printf("server: got connection from %s\n", s);

        if (!fork()) { // this is the child process
            close(sockfd); // child doesn't need the listener
// receive nominee

	    IDused = 0;
	    if ((recv(new_fd,nomineebuf,MAXBUFLEN-1,0)) == -1){
		perror("Nominee_recv");
		exit(1);
	    }
            printf("nominee: %s\n",nomineebuf);
// receive user ID
	    if ((recv(new_fd,IDbuf,MAXBUFLEN-1,0)) == -1){
                perror("ID_recv");
                exit(1);
            }
	    IDconversion = atoi(IDbuf);
	    printf("userID: %d\n",IDconversion);
// write data to temporary file
            fs = fopen("nominee.txt","w");
	    fi = fopen("nomlist.txt","a");
            if (fs == NULL){
                puts ( "Cannot open nominee.txt file");
                exit(0);
            }
            fprintf(fs,"%s\n%d\n",nomineebuf,IDconversion);

// check ID list
	    for(IDcheck = 0;IDcheck < MAXBUFLEN-1;IDcheck++){
		if(IDconversion == IDs[IDcheck]){
			printf("ID: %d has already voted\n",IDconversion);
			fclose(fs);
			exit(0);
		}
	    }
// set votes array
                snl = fopen("nomlist.txt","r");
                if (snl == NULL){
                        puts ( "Cannot read nomlist.txt file");
                        exit(0);
                }
                votefile = fopen("votelist.txt","r");
                if (votefile == NULL){
                        puts ( "Cannot read votefile.txt file");
                        exit(0);
                }
                resultscounter = 0;
                IDcheck = 0;
		while(fgets(IDbuf,MAXBUFLEN-1,votefile) != NULL){
			if( IDbuf[len-1] == '\n') IDbuf[len-1] = 0;
			votes[IDcheck] = atoi(IDbuf);
			IDcheck++;
		}
		fclose(votefile);
		IDcheck = 0;
// compare and add to files 
                while(fgets(IDbuf,MAXBUFLEN-1,snl) != NULL){
                        len = strlen(IDbuf);
                        if( IDbuf[len-1] == '\n') IDbuf[len-1] = 0;
printf("  checking: %s with %s\n",IDbuf,nomineebuf);
                        if( strcmp(nomineebuf,IDbuf)==0){
                                IDcheck++;
				if(IDcheck == 1){
					votes[resultscounter]++;
				}
printf("--dupe detected--\n");
                        }
                        resultscounter++;
                }
                if(IDcheck == 0){
	                fprintf(fi,"%s\n",nomineebuf);
			votes[resultscounter]++;
                }
		IDcheck = 0;
		votefile = fopen("votelist.txt","w");
                if (votefile == NULL){
                        puts ( "Cannot read votefile.txt file");
                        exit(0);
                }
		while(votes[IDcheck] != 0){
			fprintf(votefile,"%d\n",votes[IDcheck]);
			IDcheck++;
		}
		fclose(votefile);
		fclose(snl);
                fclose(fs);
	        fclose(fi);
	        exit(0);
        }
// after loop resetting data

// read data from temporary file
	sleep(1);
	ft = fopen("nominee.txt","r");
	if (ft == NULL){
                puts ( "Cannot read nominee.txt file");
                exit(0);
        }
	fgets(nomineebuf,MAXBUFLEN-1,ft);
	len = strlen(nomineebuf);
	if( nomineebuf[len-1] == '\n') nomineebuf[len-1] = 0;
        fgets(IDbuf,MAXBUFLEN-1,ft);
        if( IDbuf[len-1] == '\n') IDbuf[len-1] = 0;
	IDconversion = atoi(IDbuf);
	fclose(ft);

// add to ID list
	IDs[IDcounter] = IDconversion;
	IDcounter++; 

// check existing nominee and increment votes

// open nomlist and count preparation to receive
        fir = fopen("nomlist.txt","r");
        if (fir == NULL){
                puts ( "Cannot read nominee.txt file");
                exit(0);
        }
// IDconversion = how many times to recieve to client
	IDconversion = 0;
	while(fgets(IDbuf,MAXBUFLEN-1,fir) != NULL){
		IDconversion++;
	}
	sprintf(nomineebuf,"%d",IDconversion);
// send preparation
        if (send(new_fd, nomineebuf,sizeof(nomineebuf), 0) == -1)
             perror("send");
	fclose(fir);
	fir = fopen("nomlist.txt","r");
        if (fir == NULL){
                puts ( "Cannot read nominee.txt file");
                exit(0);
        }
	snl = fopen("votelist.txt","r");
        if (snl == NULL){
                puts ( "Cannot read votelist.txt file");
                exit(0);
        }
	IDcheck = 0;
        while(fgets(IDbuf,MAXBUFLEN-1,snl) != NULL){
                if( IDbuf[len-1] == '\n') IDbuf[len-1] = 0;
                votes[IDcheck] = atoi(IDbuf);
                IDcheck++;
        }

// send 
	IDcheck = 0;
	while(fgets(IDbuf,MAXBUFLEN-1,fir) != NULL){
		len = strlen(IDbuf);
		if( IDbuf[len-1] == '\n') IDbuf[len-1] = 0;
		printf("IDbuf: %s ",IDbuf);
		sleep(1);
		if (send(new_fd, IDbuf,strlen(IDbuf), 0) == -1)
	             perror("send");
		sleep(1);
		sprintf(IDbuf,"%d",votes[IDcheck]);
                printf("%s\n",IDbuf);
                if (send(new_fd, IDbuf,strlen(IDbuf), 0) == -1)
                     perror("send");
		IDcheck++;
	}
	fclose(fir);
	fclose(snl);
        close(new_fd);  // parent doesn't need this
    }

    return 0;
}
