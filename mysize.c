#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<dirent.h>
#include<string.h>
#include<fcntl.h>

//Function to compare two strings
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

void fun_se(char *ptr, int s)
{
	struct dirent *dp;
	DIR *dir=opendir(ptr);
        if(!dir)
               	return;

	while ((dp = readdir(dir)) != NULL)
        {
             	if(dp->d_type == DT_REG)
                {
                       	int fd=open(dp->d_name,O_RDONLY);
                       	long int size = lseek(fd, 0, SEEK_END);
			if(size == s)
			{
				printf("Name : %s \t",dp->d_name);
                       		printf("Size: %ld\n",size);
			}
                       	close(fd);
                }
        }
	closedir(dir);
}

void fun_sg(char *ptr,int s)
{
	struct dirent *dp;
	DIR *dir=opendir(ptr);
        if(!dir)
               	return;

	while ((dp = readdir(dir)) != NULL)
        {
                if(dp->d_type == DT_REG)
                {
                     	int fd=open(dp->d_name,O_RDONLY);
                       	long int size = lseek(fd, 0, SEEK_END);
			if(size >= s)
			{
				printf("Name : %s \t",dp->d_name);
                       		printf("Size: %ld\n",size);
			}
                       	close(fd);
                }
        }
	closedir(dir);
}

void fun_sl(char *ptr, int s)
{
	struct dirent *dp;
	DIR *dir=opendir(ptr);
        if(!dir)
               	return;

	while ((dp = readdir(dir)) != NULL)
        {
              	if(dp->d_type == DT_REG)
                {
                     	int fd=open(dp->d_name,O_RDONLY);
                       	long int size = lseek(fd, 0, SEEK_END);
			if(size <= s)
			{
				printf("Name : %s \t",dp->d_name);
                       		printf("Size: %ld\n",size);
			}
                       	close(fd);
                }
        }
	closedir(dir);
}

void fun_fe(char *ptr, int s)
{
	struct dirent *dp;
	DIR *dir=opendir(ptr);
        if(!dir)
               	return;

	while ((dp = readdir(dir)) != NULL)
	{
        	if(dp->d_type == DT_REG)
		{
			int fd=open(dp->d_name,O_RDONLY);
			char fname[100];
			strcpy(fname,dp->d_name);
			char fname1[100];
        		for(int i=0;i<strlen(fname);i++)
        		{
                		if(fname[i]=='.')
                		{
					if(i == s)
					{
						int fd=open(dp->d_name,O_RDONLY);
                       				long int size = lseek(fd, 0, SEEK_END);
						printf("Name : %s \t",dp->d_name);
                                             	printf("Size: %ld\n",size);
						close(fd);
						break;
					}
                		}
                		else
                		{
                        		fname1[i]=fname[i];
                		}
        		}
		}
       }
       closedir(dir);
}

void fun_fg(char *ptr, int s)
{
	struct dirent *dp;
	DIR *dir=opendir(ptr);
        if(!dir)
               	return;

	while ((dp = readdir(dir)) != NULL)
	{
        	if(dp->d_type == DT_REG)
		{
			int fd=open(dp->d_name,O_RDONLY);
			char fname[100];
			strcpy(fname,dp->d_name);
			char fname1[100];
        		for(int i=0;i<strlen(fname);i++)
        		{
                		if(fname[i]=='.')
                		{
					if(i >= s)
					{
						int fd=open(dp->d_name,O_RDONLY);
                     				long int size = lseek(fd, 0, SEEK_END);
						printf("Name : %s \t",dp->d_name);
                                                printf("Size: %ld\n",size);
						close(fd);
						break;
					}
                		}
                		else
                		{
                        		fname1[i]=fname[i];
                		}
        		}
		}
	}
        closedir(dir);
}

void fun_fl(char *ptr, int s)
{
	struct dirent *dp;
	DIR *dir=opendir(ptr);
        if(!dir)
               	return;

	while ((dp = readdir(dir)) != NULL)
	{
                if(dp->d_type == DT_REG)
		{
			int fd=open(dp->d_name,O_RDONLY);
			char fname[100];
			strcpy(fname,dp->d_name);
			char fname1[100];
        		for(int i=0;i<strlen(fname);i++)
        		{
                		if(fname[i]=='.')
                		{
					if(i <= s)
					{
						int fd=open(dp->d_name,O_RDONLY);
                     				long int size = lseek(fd, 0, SEEK_END);
						printf("Name : %s \t",dp->d_name);
                                                printf("Size: %ld\n",size);
						close(fd);
						break;
					}
                		}
                		else
                		{
                        		fname1[i]=fname[i];
                		}
        		}
		}
	}
        closedir(dir);
}

void fun_c(char *ptr)
{
	struct dirent *dp;
	DIR *dir=opendir(ptr);
        if(!dir)
               	return;

	while ((dp = readdir(dir)) != NULL)
	{
        	if(dp->d_type == DT_REG)
		{
			int fd=open(dp->d_name,O_RDONLY);
			char fname[100];
			strcpy(fname,dp->d_name);
			char fname1[100];
       			for(int i=0;i<strlen(fname);i++)
        		{
               			if(fname[i]=='.')
               			{
					if(fname[i+1]=='c')
					{
						int fd=open(dp->d_name,O_RDONLY);
                       				long int size = lseek(fd, 0, SEEK_END);
						printf("Name : %s \t",dp->d_name);
                                              	printf("Size: %ld\n",size);
						close(fd);
						break;
					}
               			}
               			else
               			{
       					fname1[i]=fname[i];
              			}
       			}
		}
	}
	closedir(dir);
}

void fun_txt(char *ptr)
{
	struct dirent *dp;
	DIR *dir=opendir(ptr);
        if(!dir)
               	return;

	while ((dp = readdir(dir)) != NULL)
	{
        	if(dp->d_type == DT_REG)
		{
			int fd=open(dp->d_name,O_RDONLY);
			char fname[100];
			strcpy(fname,dp->d_name);
			char fname1[100];
       			for(int i=0;i<strlen(fname);i++)
        		{
               			if(fname[i]=='.')
               			{
					if(fname[i+1]=='t')
					{
						int fd=open(dp->d_name,O_RDONLY);
                      				long int size = lseek(fd, 0, SEEK_END);
						printf("Name : %s \t",dp->d_name);
                                               	printf("Size: %ld\n",size);
						close(fd);
						break;
					}
               			}
               			else
               			{
                       			fname1[i]=fname[i];
               			}
       			}
		}
	}
	closedir(dir);
}

int main(int argc, char *argv[])
{
	struct dirent *dp;
	long size;
	char *buf;
        char *ptr;
	size = pathconf(".", _PC_PATH_MAX);
       	if ((buf = (char *)malloc((size_t)size)) != NULL)
        {
        	ptr = getcwd(buf, (size_t)size);
        }

	if(argc==3)
	{
		if(strcmpi(argv[1],"-se")==0)		//filter 1: " -se " prints all files with size equal to the specified size
		{
			fun_se(ptr,atoi(argv[2]));
		}
		else if(strcmpi(argv[2],"-se")==0)
		{
			fun_se(ptr,atoi(argv[1]));
		}
		else if(strcmpi(argv[1],"-sg")==0)	//filter 2: " -sg " prints all files with size greater than or equal to the specified size
		{
			fun_sg(ptr,atoi(argv[2]));
		}
		else if(strcmpi(argv[2],"-sg")==0)
		{
			fun_sg(ptr,atoi(argv[1]));
		}
		else if(strcmpi(argv[1],"-sl")==0)	//filter 3: " -sl " prints all files with size lesser than or equal to the specified size
		{
			fun_sl(ptr,atoi(argv[2]));
		}
		else if(strcmpi(argv[2],"-sl")==0)
		{
			fun_sl(ptr,atoi(argv[1]));
		}
		else if(strcmpi(argv[1],"-fe")==0)	//filter 4: " -fe " to print files with their name length equal to the specified size
		{
			fun_fe(ptr,atoi(argv[2]));
		}
		else if(strcmpi(argv[2],"-fe")==0)
		{
			fun_fe(ptr,atoi(argv[1]));
		}
		else if(strcmpi(argv[1],"-fg")==0)	//filter 5: " -fg " for displaying all files with file length greater than or equal to the given size
		{
			fun_fg(ptr,atoi(argv[2]));
		}
		else if(strcmpi(argv[2],"-fg")==0)
		{
			fun_fg(ptr,atoi(argv[1]));
		}
		else if(strcmpi(argv[1],"-fl")==0)	//filter 6: " -fl " displays all files with file name length lesser than or equal to the specified size
		{
			fun_fl(ptr,atoi(argv[2]));
		}
		else if(strcmpi(argv[2],"-fl")==0)
		{
			fun_fl(ptr,atoi(argv[1]));
		}
		else
		{
			printf("\nWrong filter used, please check");
			return -1;
		}
	}
	else if(argc==2)
	{
		if(strcmpi(argv[1],"-c")==0)		//filter 7: " -c " displays list of all c source files and their size
		{
			fun_c(ptr);
		}
		else if(strcmpi(argv[1],"-t")==0)	//filter 8: " -t " displays list of all text files with their sizes
		{
			fun_txt(ptr);
		}
		else
		{
			printf("\nWrong parameters or wrong format");
			return -1;
		}
	}
	else if(argc==1)				//no filter
	{
		struct dirent *dp;
		DIR *dir=opendir(ptr);
        	if(!dir)
               		return -1;

		while ((dp = readdir(dir)) != NULL)
		{
        	        if(dp->d_type == DT_REG)
			{
				printf("Name: %s \t",dp->d_name);
				int fd=open(dp->d_name,O_RDONLY);
				long int size = lseek(fd, 0, SEEK_END);
                                printf("Size: %ld\n",size);
				close(fd);
			}
		}
		closedir(dir);
	}
	else
	{
		printf("\nWrong number of arguments");
	}
}
