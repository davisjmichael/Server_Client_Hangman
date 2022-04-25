#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>


int main(int args, char* argv[]){
 
   int connectfd;
   int client;
   char BUFFER[200];

  struct sockaddr server_name = {AF_UNIX, "Server"};
  socklen_t server_length = sizeof(struct sockaddr) + 6;

  client = socket(AF_UNIX, SOCK_STREAM, 0);

  connectfd = connect(client, &server_name, server_length);

  read(client, BUFFER, sizeof(BUFFER));
  char* token;
  char* word;
  char* hint;
  char input[5];

  token = strtok(BUFFER, " ");
  hint  = strdup(token);
  token = strtok(NULL, " \n");
  word  = strdup(token);


  printf("Hint: %s\n", hint);


  int wordl = strlen(word);

 char* hidden = (char*)malloc(sizeof(char) * wordl);
 int question;

  for(question = 0; question <= wordl; question++){
	if(question == wordl){
	   hidden[question] = '\0';
	}else{
	   hidden[question] = '?';
}
}

char* current = strdup(hidden);


while(strcmp(current, word) != 0){
  printf("\nCommon Phrase\n");
  printf("-------------\n");
  printf(" %s\n", current);

do{
        printf("Enter a single character guess:");
	scanf(" %s", input);
}while((strlen(input) > 1));

int i;

     for(i = 0; i < wordl; i++){
        if(word[i] == input[0]){
           current[i] = input[0];
          }
       }


}//end while

if(strcmp(current, word) == 0){
printf("\nCommon Phrase\n");
printf("-------------\n");
printf(" %s\n", current);
printf("\nCongradulations!! You got the word! \n");
}

  close(connectfd);

  close(client);

  unlink("Server");
  free(hidden);
  return 0;

}
