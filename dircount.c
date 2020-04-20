#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<dirent.h>
#include<string.h>

int file=0;		//Number of files in directory
int dir_=0;		//Number of directories in directory

//Function to count the number of directories and files in the given directory
void count_and_display(char *basePath)
{
	int i;
	char path[1000];
    	struct dirent *dp;
    	DIR *dir = opendir(basePath);

    	if (!dir)
        	return;

    	while ((dp = readdir(dir)) != NULL)
    	{
		printf("%s\n",dp->d_name);
		if(dp->d_type == DT_REG)
		{
			file++;
		}
		else if(dp->d_type == DT_DIR)
		{
			dir_++;
		}
		else
		{
		}
    	}

	printf("\nFiles: %d",file);
	printf("\nDirectories: %d\n",dir_);

    	closedir(dir);
}

//Function to find the path of the sub-directory
void find_path_of_directory(char *basePath,char *f)
{
    	char path[1000];
    	struct dirent *dp;
    	DIR *dir = opendir(basePath);

    	// Unable to open directory stream
    	if (!dir)
        	return;

    	while ((dp = readdir(dir)) != NULL)
    	{
        	if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        	{
			if(strcmp(dp->d_name,f)==0)
                	{
				strcat(basePath, "/");
                                strcat(basePath, dp->d_name);
				count_and_display(basePath);
                	}
                	else
                	{
                		 // Construct new path from our base path
                		strcpy(path, basePath);
                		strcat(path, "/");
                		strcat(path, dp->d_name);

                		find_path_of_directory(path,f);
                	}
        	}
    	}
	closedir(dir);
}

//Function to compare two strings irrespective of the case
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
	long size;
        char *buf;
        char *ptr;
	char ptr1[100];

        size = pathconf(".", _PC_PATH_MAX);

	if(argc==1)
	{

		if ((buf = (char *)malloc((size_t)size)) != NULL)
		{
        		ptr = getcwd(buf, (size_t)size);		//getcwd() gets the current working directory
		}
		count_and_display(ptr);
	}
	else if(argc==2)
	{
		if(strcmpi(argv[1],"-i")==0)
		{
			system("tree");
		}
		else if(strcmpi(argv[1],"-d")==0)
		{
			system("tree -d");
		}
		else
		{
			strcpy(ptr1,argv[1]);
			find_path_of_directory("/home/",ptr1);
		}
	}
	else
	{
		return -1;
	}
	//return -1;
}

