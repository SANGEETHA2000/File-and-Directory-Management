#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<ctype.h>
#include<dirent.h>
#include<string.h>
#include<pwd.h>
#include<grp.h>
#include<sys/stat.h>
#include<time.h>

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

void fun_sd(const char *name, int indent, int size)
{
    	DIR *dir;
    	struct dirent *entry;

    	if (!(dir = opendir(name)))
        	return;

    	while ((entry = readdir(dir)) != NULL)
	{
        	if (entry->d_type == DT_DIR)
		{
            		char path[1024];
            		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                		continue;
            		snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            		printf("%*s[%s]\n", indent, "", entry->d_name);
            		fun_sd(path, indent + 2,size);
        	}
		else
		{
			char fname[100];
                	strcpy(fname,entry->d_name);
                	char fname1[100];
                	for(int i=0;i<strlen(fname);i++)
                	{
				if(fname[i]=='.')
                		{
					if(i == size)
                                	{
						printf("%*s- %s\n", indent, "", entry->d_name);
                                        	break;
                                	}
				}
			}
        	}
    	}
    	closedir(dir);
}

void fun_sdg(const char *name, int indent, int size)
{
    	DIR *dir;
    	struct dirent *entry;

    	if (!(dir = opendir(name)))
        	return;

    	while ((entry = readdir(dir)) != NULL)
	{
        	if (entry->d_type == DT_DIR)
		{
            		char path[1024];
            		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                		continue;
            		snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            		printf("%*s[%s]\n", indent, "", entry->d_name);
            		fun_sdg(path, indent + 2,size);
        	}
		else
		{
			char fname[100];
                	strcpy(fname,entry->d_name);
                	char fname1[100];
                	for(int i=0;i<strlen(fname);i++)
                	{
				if(fname[i]=='.')
                		{
					if(i >= size)
                                	{
						printf("%*s- %s\n", indent, "", entry->d_name);
                                        	break;
                                	}
				}
			}
        	}
    	}
    	closedir(dir);
}

void fun_sdl(const char *name, int indent, int size)
{
    	DIR *dir;
    	struct dirent *entry;

    	if (!(dir = opendir(name)))
        	return;

    	while ((entry = readdir(dir)) != NULL)
	{
        	if (entry->d_type == DT_DIR)
		{
            		char path[1024];
            		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                		continue;
            		snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            		printf("%*s[%s]\n", indent, "", entry->d_name);
            		fun_sdl(path, indent + 2,size);
        	}
		else
		{
			char fname[100];
                	strcpy(fname,entry->d_name);
                	char fname1[100];
                	for(int i=0;i<strlen(fname);i++)
                	{
				if(fname[i]=='.')
                		{
					if(i <= size)
                                	{
						printf("%*s- %s\n", indent, "", entry->d_name);
                                        	break;
                                	}
				}
			}
        	}
    	}
    	closedir(dir);
}

void fun_c(const char *name, char c)
{
	DIR *dir;
        struct dirent *entry;

        if (!(dir = opendir(name)))
                return;

        while ((entry = readdir(dir)) != NULL)
        {
                if (entry->d_type == DT_DIR)
                {
                        char path[1024];
                        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                                continue;
                        snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
                        fun_c(path,c);                                                                                                                                 }
        else
        {
                char p[100];
                strcpy(p,entry->d_name);
                if(p[0]==c)
                {
                        printf("%s\n", entry->d_name);
                }
        }
    }
    closedir(dir);
}

void fun_e(const char *name, char c)
{
	DIR *dir;
        struct dirent *entry;

        if (!(dir = opendir(name)))
                return;

        while ((entry = readdir(dir)) != NULL)
        {
                if (entry->d_type == DT_DIR)
                {
                        char path[1024];
                        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                                continue;
                        snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
                        fun_e(path,c);
		}
               	else
                {
                        char p[100];
                        strcpy(p,entry->d_name);
                        int i;
                        for(i=0;i<strlen(p);i++)
                        {
                                if(p[i]=='.')
                                {
                                        if(p[i-1]==c)
                                        {
                                                printf("%s\n", entry->d_name);
                                        }
                                }
                        }
                }
        }
 	closedir(dir);
}

void fun_x(char *str)
{
        char command[200];
        strcpy(command,"find -type f -iname '");
        strcat(command,str);
        strcat(command,"*'");
        system(command);
}


void fun_y(char *str)
{
        char command[200];
        strcpy(command,"find -type f -iname '*");
        strcat(command,str);
        strcat(command,"'");
        system(command);
}


void fun_z(char *str)
{
        char command[200];
        strcpy(command,"find -type f -iname '*");
        strcat(command,str);
        strcat(command,"*'");
        system(command);
}

void fileinfo(char *d_name, char *name)
{
	struct passwd *p;
	struct group *g;
	struct stat filestat;
	stat(d_name,&filestat);

	printf("NAME : %s\n\n",name);

	printf("Type of file:");
	switch(filestat.st_mode & S_IFMT)
	{
           	case S_IFBLK:  printf("Block special file\n"); break;//like a disk
            	case S_IFCHR:  printf("Character special file\n"); break; //like a terminal
            	case S_IFDIR:  printf("Directory\n"); break; //for (sub)directory
            	case S_IFIFO:  printf("FIFO special file\n"); break; //for fifo or pipe
            	case S_IFLNK:  printf("Symbolic link file\n"); break;
		case S_IFREG:  printf("Regular file\n");break;
            	case S_IFSOCK: printf("Socket file\n"); break;
           	//Filetype isn't identified
            	default:       printf("-\n"); break;
	}
	printf("\n");

	printf("Permissions:");
	//user permissions
	printf( (filestat.st_mode & S_IRUSR) ? " r":"-");
	printf( (filestat.st_mode & S_IWUSR) ? "w":"-");
	printf( (filestat.st_mode & S_IXUSR) ? "x":"-");
	//group permissions
	printf( (filestat.st_mode & S_IRGRP) ? "r":"-");
	printf( (filestat.st_mode & S_IWGRP) ? "w":"-");
	printf( (filestat.st_mode & S_IXGRP) ? "x":"-");
	//other permissions
	printf( (filestat.st_mode & S_IROTH) ? "r":"-");
	printf( (filestat.st_mode & S_IWOTH) ? "w":"-");
	printf( (filestat.st_mode & S_IXOTH) ? "x":"-");
	printf("\n\n");

	printf("Number of links : %ld\n\n",filestat.st_nlink);

	p=getpwuid(filestat.st_uid);
	printf("Owner name : %s\n\n",p->pw_name);

	g=getgrgid(filestat.st_gid);
	printf("Group name : %s\n\n",g->gr_name);

	printf("Size of file : %zu\n\n",filestat.st_size);

	printf("Modified time : %s\n",ctime(&filestat.st_mtime));

	printf("Access time : %s\n",ctime(&filestat.st_atime));

	printf("Changed time : %s\n",ctime(&filestat.st_ctime));
}

void deletef(char *f)
{
	char command[100];
	strcpy(command,"rm ");
	strcat(command,f);
	system(command);
        printf("\nFile Deleted");
}

void deleted(char *d)
{
	char command[100];
	strcpy(command,"rmdir ");
	strcat(command,d);
	system(command);
	printf("\nDirectory Deleted");
}

void find_path(char *basePath,char *f,int c)
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
				if(c==1)
				{
					fileinfo(basePath,f);
				}
				else if(c==2)
				{
					struct stat filestat;
					stat(basePath,&filestat);
					switch(filestat.st_mode & S_IFMT)
					{
						case S_IFREG: deletef(basePath);break;
						case S_IFDIR: deleted(basePath);break;
						default: printf("Error");
					}
				}
                	}
                	else
                	{
                		 // Construct new path from our base path
                		strcpy(path, basePath);
                		strcat(path, "/");
                		strcat(path, dp->d_name);

                		find_path(path,f,c);
                	}
        	}
    	}
	closedir(dir);
}

int main(int argc, char *argv[])
{
	if(argc==3)
	{
		if(strcmpi(argv[1],"-sd")==0)		//filter 1: " -sd " displays all files with the given length diretory wise
		{
			fun_sd("/home/",0,atoi(argv[2]));
		}
		else if(strcmpi(argv[2],"-sd")==0)
		{
			fun_sd("/home/",0,atoi(argv[1]));
		}
		else if(strcmpi(argv[1],"-sdg")==0)	//filter 2: " -sdg " displays all files with the name length greater than or equal to the specified size
		{
			fun_sdg("/home/",0,atoi(argv[2]));
		}
		else if(strcmpi(argv[2],"-sdg")==0)
		{
			fun_sdg("/home/",0,atoi(argv[1]));
		}
		else if(strcmpi(argv[1],"-sdl")==0)	//filter 3: "-sdl " displays all files with the name length lesser than or equal to the specified size
		{
			fun_sdl("/home/",0,atoi(argv[2]));
		}
		else if(strcmpi(argv[2],"-sdl")==0)
		{
			fun_sdl("/home/",0,atoi(argv[1]));
		}
		else if(strcmpi(argv[1],"-c")==0)	//filter 4: " -c " displays all files with starting letter as specified
		{
			fun_c("/home/",argv[2][0]);
		}
		else if(strcmpi(argv[2],"-c")==0)
		{
			fun_c("/home/",argv[1][0]);
		}
		else if(strcmpi(argv[1],"-e")==0)	//filter 5: " -e " displays all files with the ending letter as specified
		{
			fun_e("/home/",argv[2][0]);
		}
		else if(strcmpi(argv[1],"-e")==0)
		{
			fun_e("/home/",argv[1][0]);
		}
		else if(strcmpi(argv[1],"-x")==0)	//filter 6: " -x " displays all files starting with the given substring
		{
			fun_x(argv[2]);
		}
		else if(strcmpi(argv[2],"-x")==0)
		{
			fun_x(argv[1]);
		}
		else if(strcmpi(argv[1],"-y")==0)	//filter 7: " -y " displays all files ending with the given substring
		{
			fun_y(argv[2]);
		}
		else if(strcmpi(argv[2],"-y")==0)
		{
			fun_y(argv[1]);
		}
		else if(strcmpi(argv[1],"-z")==0)	//filter 8: " -z " displays all files having that substring
		{
			fun_z(argv[2]);
		}
		else if(strcmpi(argv[2],"-z")==0)
		{
			fun_z(argv[1]);
		}
		else if(strcmpi(argv[1],"-info")==0)	//filter 9: " -info " displays all information about the file specified
		{
			find_path("/home/",argv[2],1);
		}
		else if(strcmpi(argv[2],"-info")==0)
		{
			find_path("/home/",argv[1],1);
		}
		else if(strcmpi(argv[1],"-d")==0)	//filter 10: " -d " deletes the specified file or directory
		{
			find_path("/home/",argv[2],2);
		}
		else if(strcmpi(argv[2],"-d")==0)
		{
			find_path("/home/",argv[1],2);
		}
		else
		{
			printf("\nWrong filter usd, please check");
			return -1;
		}
	}
	else
	{
		printf("\nWrong number of arguments passed");
		return -1;
	}
}

