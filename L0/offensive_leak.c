#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>

int main(){

  while(1){ 
      malloc(1024); //memory leak!
      sleep(1); //slow down the leak by sleeping for a second.
    }

}
