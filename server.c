#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <time.h>


void ctrlc();

typedef struct phrase
{
  char* phrase;
  char* hint;

}phrase;

int main(int args, char* argv[]){
int status = 1;
while(status == 1){

	FILE* fin = fopen("input.txt", "r");
	if(fin == NULL){
		printf("\n The file input.txt could be opened\n");
		exit(1);
	}

	else{

	char* BUFF = (char*)malloc(sizeof(char) * 1024);
	phrase* phrase_string = (phrase*)malloc(sizeof(phrase) * 1024);

	int i = 0;
	char* token;
	while(fgets(BUFF, 1024, fin)){
		token = strtok(BUFF, " ");
		phrase_string[i].phrase = strdup(token);
		token = strtok(NULL, " ");
		phrase_string[i].hint = strdup(token);
		i++;
	}
	fclose(fin);

    struct sigaction new_sig, old_sig;
    new_sig.sa_flags = 0;
    new_sig.sa_handler = ctrlc;
    sigaction(SIGINT, &new_sig, &old_sig);


    int listenf;
    int connectedf;
    int randomI;
    srand(time(NULL));
    randomI = rand() % 12;
        listenf = socket(AF_UNIX, SOCK_STREAM, 0);
	if(listenf == -1){
	printf("ending");
		exit(1);
	}

	struct sockaddr sockaddress = {AF_UNIX, "Server"};
	socklen_t saddrlength = sizeof(struct sockaddr) + 7;
	bind(listenf, &sockaddress, saddrlength);

       	listen(listenf, 10);

        printf("Listening......\n");


	if((connectedf = accept(listenf, NULL, NULL)) != -1){

	write(connectedf, phrase_string[randomI].phrase, strlen(phrase_string[randomI].phrase));
	write(connectedf, " ", strlen(" "));
	write(connectedf, phrase_string[randomI].hint, strlen(phrase_string[randomI].hint));
	close(connectedf);
	unlink("Server");

	sigaction(SIGINT, &old_sig, NULL);

}



}

}//end while
return 0;
}



void ctrlc(){
    system("rm Server");
    exit(0);
    }

