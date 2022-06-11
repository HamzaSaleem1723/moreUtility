/*Get multiple file names via command line, display contents of all the files and exits*/


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
	for(int i=1;i<argc;i++){
		fp =  fopen(argv[i],"r");
		if(fp ==  NULL){
			perror("Error:");
			exit(1);
		}
		do_more(fp);
		fclose(fp);
	
	}
	return 0;
	
}

void do_more(FILE *fp){
	char buffer[LINELENGTH];
	while(fgets(buffer,LINELENGTH,fp)){
		fputs(buffer,stdout);
	}
}
