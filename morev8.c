/*Add the functionality of command 'v', to open current file in vim and afterwards fall back*/


#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include<sys/wait.h>
#include <unistd.h>
#define LINELENGTH 512
#define PAGELENGTH 31

void do_more(FILE *fp,char* argv[],int i,int totalLines,int lineCount);
int getInput(FILE*);

int main(int argc, char *argv[]){
	
	int totalLines = 0;
	char buffer[LINELENGTH];
	if(argc == 1){
		do_more(stdin,argv,0,0,0);
	}
	
	FILE *fp;
	for(int i=1;i<argc;i++){
		fp =  fopen(argv[i],"r");
		if(fp ==  NULL){
			perror("Error:");
			exit(1);
		}
	
		while(fgets(buffer,LINELENGTH,fp)){
			totalLines++;
		}
	
		fseek(fp,0,SEEK_SET);			
		do_more(fp,argv,i,totalLines,0);
		fclose(fp);
	
	}
	return 0;
	
}

void do_more(FILE *fp,char* argv[],int i,int totalLines,int lineCount){
	int numberOfLines = 0;
	
	int percent=0;
	int rv;
	char buffer[LINELENGTH];
	
	
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
			
			else if(rv == 4){
				printf("\033[1A \033[2K \033[1G");
				int position = ftell(fp);
				int cpid = fork();
				if(cpid ==0){
					execl("/usr/bin/vim","/usr/bin/vim",argv[i], NULL);
				}
				else
					wait(NULL);
					fp = fopen(argv[i],"r");
					fseek(fp,position,SEEK_SET);
					do_more(fp,argv,i,totalLines,lineCount);
			
			}		
		}
	}
}

int getInput(FILE* cmdstream){
	int c;
	struct termios info;
        ioctl(0,TCGETS, &info); 
        struct termios save = info;
        info.c_lflag &= ~(ECHO | ICANON);        
        ioctl(0, TCSETS, &info);
	c= getc(cmdstream);
	printf("\n");
	ioctl(0, TCSETS, &save);
	if(c == 'q')
		return 0;
	if(c == ' ')
		return 1;
	if(c == '\n')
		return 2;
	if(c == 'v')
		return 4;
	
	return 3;
}

