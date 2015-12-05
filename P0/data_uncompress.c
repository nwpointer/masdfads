#include <stdio.h>

int main( int argc, char *argv[] ){
	if( argc ==2 ){
		printf("the argument supplied was %s\n", argv[1]);
	}else{
		printf("One argument expected \n");
	}
}