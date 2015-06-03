#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>

using namespace std;

bool sendRawPacket(char *msg, int sockfd){
   int len = strlen(msg);
   int sentbytes = send(sockfd,msg,len,0);
   if(sentbytes == 0){
      return false;
   }else{
      return true;
   }
}

bool charSearch(char *searchIn, char *searchFor)
{
	int len = strlen(searchIn);
	int forLen = strlen(searchFor);
	
	for (int i = 0; i < len;i++){
		if (searchFor[0] == searchIn[i]){
			bool found = true;
			for (int x = 1; x < forLen; x++){
				if(searchIn[i+x]!=searchFor[x]){
					found = false;
				}
			}
			
			if (found == true)
				return true;
		}
	}
}

void sendPong(char *buf, int sockfd) {
    char * toSearch = "PING ";
     for (int i = 0; i < strlen(buf);i++) {
            if (buf[i] == toSearch[0]) {
                bool found = true;
                for (int x = 1; x < 4; x++) {
                    if (buf[i+x]!=toSearch[x]) {
                        found = false;
                    }
                }
                if (found == true) {
                    int count = 0;
                    for (int x = (i+strlen(toSearch)); x < strlen(buf);x++) {
                        count++;
                    }
                    char returnHost[count + 5];
                    returnHost[0]='P';
                    returnHost[1]='O';
                    returnHost[2]='N';
                    returnHost[3]='G';
                    returnHost[4]=' ';
                    count = 0;
                    for (int x = (i+strlen(toSearch)); x < strlen(buf);x++) {
                        returnHost[count+5]=buf[x];
                        count++;
                    }
                    if (sendRawPacket(returnHost, sockfd)) {
                        cout << "Pong sent" << endl;
                    }
 
                    return;
                }
            }
        }
}

void sendMessage( ) {
	char * searchMessage = "!help";
	for(int i = 0; i < strlen(buf);i++) {
		bool found = true;
		for (int x = i; x < 4; x++) {
			if(buf[i+x]!=searchMessage[x]){
				found = false;
			}
		}
		if(found == true) {
			count = 0;
			for (int x = (i+strlen(toSearch)); x < strlen(buf);x++) {
                        count++;
            }
            char sendFuckingMessage[count + 3];
            sendFuckingMessage[0]='N';
            sendFuckingMessage[1]='I';
            sendFuckingMessage[2]='G';
            count = 0;
             for (int x = (i+strlen(toSearch)); x < strlen(buf);x++) {
                        sendFuckingMessage[count+3]=buf[x];
                        count++;
                    }
                    if(sendRawPacket(returnHost, sockfd)) {
                    	cout << "Pong sent" << endl;
                    }
                    return;
		}
	}

}


int main(int argc, const char* argv[]) {
    struct sockaddr_in sock;
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);  
    if (sockfd < 0) {
        perror("Socket");
        return 1;
    }

    sock.sin_family = AF_INET;
    sock.sin_port = htons(6667);
    sock.sin_addr.s_addr = getaddrinfo("irc.rizon.net");

    int k  = connect(sockfd, (struct sockaddr*)&sock, sizeof sock);
    if (k < 0) {
        perror("connect");
        return 1;
    }
    sendRawPacket("USER gay gay.balls lol :gay\r\n", sockfd);
    sendRawPacket("NICK dolabot\r\n", sockfd);
    sendRawPacket("JOIN #niggersack\r\n", sockfd);
    sendRawPacket("PRIVMSG #niggersack :sup niggers?\r\n", sockfd); // join message

    int rc;
    int MAXSIZE = 65535;
    char buf[MAXSIZE];
    while(1){
        rc = recv(sockfd, buf, sizeof(buf), 0);
		if(rc > 0) {
			buf[rc]='\0';
			
			if(charSearch(buf,"PING")) {
				sendPong(buf, sockfd);
			}
			cout << buf;
			
		}
    }

    return 0;
