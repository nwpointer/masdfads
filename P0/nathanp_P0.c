#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readCharAsInt(char c){
	return c-'0';
}

void readWordFromStdioOfSize(int size){
	char *word;
	word = (char*)calloc(size, sizeof(char));
	for(int j=0;j<=size; j++){
		char s = getchar();
		if(!s || s== -1){
			printf("Input error: not enough chars\n");
		}
		word[j] = s;
	}
	printf("%s ", word);
	free(word);
}
void readInteger(){
	int a[0];
	size_t t = fread(a, 1, 4, stdin);
	if(t!=4){
		printf("Input error: not enough ints\n");
	}
	printf("%d ", a[0]);
}

void readDouble(){
	double a[0];
	size_t t= fread(a, 1, 8, stdin);
	if(t!=8){
		printf("Input error: not enough doubles\n\n");
	}
	printf("%.5f ", a[0]);
}

void readNStringFromStdio(int n){
	for(int i=0;i<=n;i++ ){
		int size = getchar();
		if(!size || size== -1){
			printf("Input error: no string size\n");
		}
		readWordFromStdioOfSize(size);
	}
}

void readNIntegerFromStdio(n){
	for(int i=0;i<=n;i++ ){
		readInteger();
	}
}
void readNDoubleFromStdio(n){
	//printf("%d\n", n);
	for(int i=0;i<=n;i++ ){
		readDouble();
	}
}

void process(char c){
	int n;
	switch(c){
		case 100:
			n=getchar();
			if(n == -1){
				printf("Input error: no size\n");
			}
			readNDoubleFromStdio(n);
			break;
		case 105 : 
			n=getchar();
			if(n == -1){
				printf("Input error: no size\n");
			}
			readNIntegerFromStdio(n);
			break;
		case 115:
			n=getchar();
			if(n == -1){
				printf("Input error: no size\n");
			}
			readNStringFromStdio(n);
			break;
		case 110 :
			printf("\n");
			break;
		default :
			printf("Input error: bad type\n");
			exit(-1);
	}
}

int main(){
	char ch;

	while (1==1){
		ch = getchar();
		if(ch != -1){
			//printf("%c |\n", ch);
			process(ch);		
		}else{
			break;
		}
	}

	return 0;
	
}