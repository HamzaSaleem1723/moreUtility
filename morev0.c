/*Get a single file name via command line, display entire contents of file and exits*/


#include <stdio.h>
#include <stdlib.h>
#define LINELENGTH 512

void do_more(FILE *);

int main(int argc, char *argv[]){

	if(argc == 1){
		printf("This is the help page\n");
		exit(0);
	}
	
	FILE *fp;
	fp =  fopen(argv[1],"r");
	if(fp ==  NULL){
		perror("Error:");
		exit(1);
	}
	do_more(fp);
	fclose(fp);
	return 0;
	
}

void do_more(FILE *fp){
	char buffer[LINELENGTH];
	while(fgets(buffer,LINELENGTH,fp)){
		fputs(buffer,stdout);
	}
}
