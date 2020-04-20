#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<dirent.h>
#include<unistd.h>
#include<ctype.h>

//funtion to compare two strings
int strcmpi(char* s1, char* s2)
{
	int i;
	if(strlen(s1)!=strlen(s2))
        	return -1;
	for(i=0;i<strlen(s1);i++)
	{
        	if(toupper(s1[i])!=toupper(s2[i]))
        		return s1[i]-s2[i];
    	}
    return 0;
}

int main(int argc,char *argv[])
{
	int size,cnt,d,i;
        char direc[100],word[PATH_MAX],command[PATH_MAX],pattern[PATH_MAX],c;
        struct dirent *dp;
	if(argc==3)
	{
		strcpy(pattern,argv[2]);
		strcpy(command,"find $(cd ; pwd) -name ");
		strcat(command,argv[1]);
		strcat(command," > temp.txt");
		system(command);
		int fd1=open("temp.txt",O_RDONLY);
                if(fd1==-1)
                {
                        printf("Cannot open temp.txt!!\n");
                        return -1;
                }
                while((d=read(fd1,&c,1)) > 0)
                {
                        direc[i]=c;
                        i++;
                }
		direc[i-1]='\0';
                close(fd1);
                printf("Directory path: %s\n",direc);
	}
	else
	{
		printf("Wrong number of arguments!");
		return -1;
	}
        DIR *dir=opendir(direc);
        if(!dir)
	{
		printf("Cannot open the directory %s!\n",direc);
                return -1;
	}
        while((dp=readdir(dir))!=NULL)
        {
                if(dp->d_type==DT_REG)
                {
			cnt=0;
			char name[PATH_MAX];
			strcpy(name,direc);
			strcat(name,"/");
			strcat(name,dp->d_name);
       			int fd=open(name,O_RDONLY);
        		if(fd==-1)
        		{
        			printf("Cannot open %s file!\n",dp->d_name);
        			continue;
			}
			printf("%s:\n",dp->d_name);
        		while(read(fd,&c,1)>0)		//copying character wise and finally comparing the word formed
			{
				if(isalpha(c))
					strncat(word,&c,1);
				else
				{
					if(strcmpi(word,pattern)==0)
					{
						cnt++;
					}
					strcpy(word,"\0");
				}
			}
			printf("%s found at %d places!\n",pattern,cnt);
			close(fd);
		}
	}
	closedir(dir);
	return 0;
}
