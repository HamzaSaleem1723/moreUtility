/*Display one page at a time and pause for commands ('q',' ','\n') and act accordingly*/

#include <stdio.h>
#include <stdlib.h>
#define LINELENGTH 512
#define PAGELENGTH 31

void do_more(FILE *);
int getInput();

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
	int numberOfLines = 0;
	int rv;
	char buffer[LINELENGTH];
	while(fgets(buffer,LINELENGTH,fp)){
		fputs(buffer,stdout);
		numberOfLines++;
		if(numberOfLines == PAGELENGTH){
			rv = getInput();
			if(rv == 0)
				break;
			else if(rv == 1)
				numberOfLines = numberOfLines - PAGELENGTH;
			else if(rv == 2)
				numberOfLines = numberOfLines - 1;
			else if(rv == 3)
				break;	
		}
	}
}

int getInput(){
	int c;
	c= getchar();
	if(c == 'q')
		return 0;
	if(c == ' ')
		return 1;
	if(c == '\n')
		return 2;
	return 3;
}

