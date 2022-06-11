/*Add a feature so that your more command can be used with input redirection symbol (<) as well as with the pipe symbol (|) on the shell*/

#include <stdio.h>
#include <stdlib.h>
#define LINELENGTH 512
#define PAGELENGTH 31

void do_more(FILE *);
int getInput(FILE*);

int main(int argc, char *argv[]){
	
	int lineCount;
	if(argc == 1){
		do_more(stdin);
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
	FILE* fp_tty = fopen("/dev/tty" , "r"); 
	while(fgets(buffer,LINELENGTH,fp)){
		fputs(buffer,stdout);
		numberOfLines++;
		if(numberOfLines == PAGELENGTH){
			rv = getInput(fp_tty);
			if(rv == 0){
				printf("\033[1A \033[2K \033[1G");
				break;
			}
			else if(rv == 1){
				printf("\033[1A \033[2K \033[1G");
				numberOfLines = numberOfLines - PAGELENGTH;
			}
			else if(rv == 2){
				printf("\033[1A \033[2K \033[1G");
				numberOfLines = numberOfLines - 1;
			}
				
			else if(rv == 3){
				printf("\033[1A \033[2K \033[1G");
				break;
			}	
		}
	}
}

int getInput(FILE* cmdstream){
	int c;
	printf("\033[7m --more--(%%) \033[m");
	c= getc(cmdstream);
	if(c == 'q')
		return 0;
	if(c == ' ')
		return 1;
	if(c == '\n')
		return 2;
	return 3;
}

