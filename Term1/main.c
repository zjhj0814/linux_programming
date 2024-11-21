#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

char  entries[100][30];
const int max_entries = 100;

void printOut(char* pathname){
 	//feature 1
	memset(entries, 0, sizeof(entries));

	DIR* dirp;
	struct dirent* entry;
	int count = 0;
	if((dirp=opendir(pathname))==NULL){
		perror("Directory cannot be opened\n");
	       	exit(1);
	}
  	
	while((entry=readdir(dirp))!=NULL){
    		if(count<max_entries){
      			strcpy(entries[count], entry->d_name);
     			printf("%d %s\n", count, entries[count]);
      			count++;
		}
    		else{
      			perror("Entry limit reached.\n");
      			exit(1);
		}
  	}
  	closedir(dirp);
	chdir(pathname);
	printf("\n");
}

void printDetail(char* pathname){
	//feature 2
	struct stat statbuf;

	char descrip[10];
	short octarray[9]={0400,0200,0100,0040,0020,0010,0004,0002,0001};
	char perms[10]="rwxrwxrwx";

	if(stat(pathname, &statbuf)==-1){
		perror("Couldn't stat\n");
		exit(1);
	}
	for(int j=0;j<9;j++){
		if(statbuf.st_mode&octarray[j]){
			descrip[j] = perms[j];
		}
		else{
			descrip[j]='-';
		}
	}
	descrip[9]='\0';
	printf("%s\t%ld\t%s\n\n",descrip,statbuf.st_size,pathname);
}

int main(){
	while(1){
		printOut("./");
		
		char command[3];
		scanf("%s",command);
		
		if(strcmp(command,"c") == 0){		
			//feature 3
			char filename[30];
			scanf("%s",filename);
			if(access(filename,F_OK)==0){
				if(remove(filename)==-1){
					perror("Failed to remove file");
					exit(1);
				}
			}
			else{
				int filedes;
				if((filedes=open(filename, O_CREAT|O_WRONLY,0644))==-1){
					perror("Failed to create file");
					exit(1);
				}
				else close(filedes);
			}
		}
		else if(strcmp(command,"q") == 0){
			return 0;
		}
		else if(atoi(command)>0&&atoi(command)<100){
			struct stat buf;
			char name[30];
		       	strcpy(name, entries[atoi(command)]);
			if(stat(name, &buf)==-1){
				perror("Couldn't stat\n");
				exit(1);
			}
			if(S_ISDIR(buf.st_mode)) printOut(name);
			else if(S_ISREG(buf.st_mode)) printDetail(name);
		}		
	}
}
