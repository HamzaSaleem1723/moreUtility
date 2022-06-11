/*Add a feature that displays a message in reverse video at the last line --more--(?%)*/


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

int getInput(){
	int c;
	printf("\033[7m --more--(%%) \033[m");
	c= getchar();
	if(c == 'q')
		return 0;
	if(c == ' ')
		return 1;
	if(c == '\n')
		return 2;
	return 3;
}

