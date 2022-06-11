/*Add a feature to compute and display %age of file contents displayed --more--(54%)*/


#include <stdio.h>
#include <stdlib.h>
#define LINELENGTH 512
#define PAGELENGTH 31

void do_more(FILE *);
int getInput(FILE*);

int main(int argc, char *argv[]){
	
	char buffer[LINELENGTH];
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
	int totalLines=0;
	int lineCount=0;
	int percent=0;
	int rv;
	char buffer[LINELENGTH];
	
	while(fgets(buffer,LINELENGTH,fp)){
			totalLines++;
	}
	
	fseek(fp,0,SEEK_SET);
	
	FILE* fp_tty = fopen("/dev/tty" , "r"); 
	while(fgets(buffer,LINELENGTH,fp)){
		fputs(buffer,stdout);
		numberOfLines++;
		lineCount++;
		if(numberOfLines == PAGELENGTH){
		
			percent = (lineCount/(float)totalLines)*100;
			printf("\033[7m --more--(%d%%) \033[m", percent);
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
	
	c= getc(cmdstream);
	if(c == 'q')
		return 0;
	if(c == ' ')
		return 1;
	if(c == '\n')
		return 2;
	return 3;
}

