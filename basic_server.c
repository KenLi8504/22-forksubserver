#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;
  while (1){
    from_client = server_setup();
    int f = fork();
    if (f != 0){

    }
    else{
      int to_client = server_connect(from_client);
      while (1){
        char input[10000];
        char intermediate[10000];
        char output [10000];

        int test = read(from_client,input,10000);

        if (test == 0){
          break;
        }

        //printf("Party!\n");
        strcpy(intermediate,input);
        //printf("The child here received here was %s\n",input);
        //printf("The output here was %s\n",intermediate);
        int counter = 0;
        for (int i = 0; intermediate[i]!='\0'; i++) {
          //printf("This char is %c\n",intermediate[i]);
          //printf("The counter is %d",counter);
          if (counter == 0){
            if(intermediate[i] >= 'a' && intermediate[i] <= 'z') {
              intermediate[i] = intermediate[i] - 32;
              counter = counter + 1;
              //printf("OPTION 1");
            }
            else if (intermediate[i] >= 'A' && intermediate[i] <= 'Z'){
              counter = counter + 1;
              //printf("OPTION 2");
            }
          }
          else if (counter == 1){
            if (intermediate[i] >= 'a' && intermediate[i] <= 'z') {
              counter = counter - 1;
              //printf("OPTION 3");
            }
            else if (intermediate[i] >= 'A' && intermediate[i] <= 'Z'){
              intermediate[i] = intermediate[i] + 32;
              counter = counter - 1;
              //printf("OPTION 4");
            }
          }
        //printf("The new string is %s",intermediate);
        }
        strcpy(output,intermediate);
        // printf("The length of the input is %ld\n",strlen(input));
        //printf("The output here was %s\n",intermediate);
        write(to_client,output,10000);
      }
    }
  }
  return 0;
}
