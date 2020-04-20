#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<ctype.h>

//function to compare two strings irrespective of case
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

//Function to convert the entire string into lower case
void strlwr(char s[])
{
        int c=0;
        while(s[c]!='\0')
        {
                if(s[c]>='A' && s[c]<='Z')
                {   
			s[c]=s[c]+32;
                }
                c++;
        }
}

int main(int argc, char *argv[])
{
        if(argc==3)
        {
		char basepath[100],command[50];
		char c;
		int d,i=0;
		strcpy(command,"find \"$(cd ; pwd)\" -name ");
		strcat(command,argv[2]);
		strcat(command," > temp.txt");
		system(command);
		int fd1 = open("temp.txt",O_RDONLY);
		if(fd1==-1)
		{
			printf("Cannot open temp.txt!!\n");
			return -1;
		}
		while((d=read(fd1,&c,1)) > 0)
		{
			basepath[i]=c;
			i++;
		}
		basepath[i-1]='\0';
		close(fd1);
		printf("Basepath:%s\n",basepath);
                int fd = open(basepath,O_RDONLY);
		if(fd==-1)
		{
			printf("Cannot open %s file!\n",argv[2]);
			return -1;
		}
                printf("fd : %d\n",fd);
                if(strcmp(argv[1],"-M")==0)	//to convert contents to upper case
                {
			int j;
			char newpath[PATH_MAX];
			for(j=strlen(basepath)-1;basepath[j]!='/';j--);
		        for(int k=0;k<=j;k++)
				strncat(newpath,&basepath[k],1);
			strcat(newpath,"tmp.txt");
			int fd2=open(newpath,O_CREAT | O_WRONLY);
                        while((d=read(fd,&c,1)) > 0)
                        {
                                if(isalpha(c))
                                {
                                        if(islower(c))
                                        {
						c=toupper(c);
						write(fd2,&c,1);
                                                printf("%c",c);
                                        }
                                        else if(isupper(c))
                                        {
						write(fd2,&c,1);
                                                printf("%c",c);
                                        }
                                }
                                else
                                {
					write(fd2,&c,1);
                                        printf("%c",c);
                                }
                        }
			remove(basepath);
			strcpy(basepath,"\0");
			for(j=strlen(newpath)-1;newpath[j]!='/';j--);
			for(int k=0;k<=j;k++)
				strncat(basepath,&newpath[k],1);
			strcat(basepath,argv[2]);
			rename(newpath,basepath);
			close(fd2);
			close(fd);
                }
		else if(strcmp(argv[1],"-m")==0)	//to convert contents to lower case
		{
			int j;
                        char newpath[PATH_MAX];
                        for(j=strlen(basepath)-1;basepath[j]!='/';j--);
                        for(int k=0;k<=j;k++)
                                strncat(newpath,&basepath[k],1);
                        strcat(newpath,"tmp.txt");
                        int fd2=open(newpath,O_CREAT | O_WRONLY);
	                while((d=read(fd,&c,1)) > 0)
			{
                                if(isalpha(c))
				{
					if(isupper(c))
					{
						c=tolower(c);
						write(fd2,&c,1);
						printf("%c",c);
                                        }
					else if(islower(c))
                                        {
						write(fd2,&c,1);
                                                printf("%c",c);
					}
				}
				else
				{
					write(fd2,&c,1);
					printf("%c",c);
				}
                        }
			remove(basepath);
			strcpy(basepath,"\0");
                        for(j=strlen(newpath)-1;newpath[j]!='/';j--);
                        for(int k=0;k<=j;k++)
                                strncat(basepath,&newpath[k],1);
			strcat(basepath,argv[2]);
                        rename(newpath,basepath);
			close(fd2);
                        close(fd);
		}
		else if(strcmp(argv[1],"-T")==0)	//to convert the contents to toggle case
		{
			int j;
			char newpath[PATH_MAX];
                        for(j=strlen(basepath)-1;basepath[j]!='/';j--);
			for(int k=0;k<=j;k++)
				strncat(newpath,&basepath[k],1);
			strcat(newpath,"tmp.txt");
			int fd2=open(newpath,O_CREAT | O_WRONLY);
			while((d=read(fd,&c,1)) > 0)
			{
				if(isalpha(c))
				{
					if(isupper(c))
					{
						c=tolower(c);
						write(fd2,&c,1);
						printf("%c",c);
					}
					else if(islower(c))
					{
						c=toupper(c);
						write(fd2,&c,1);
						printf("%c",c);
					}
				}
				else
				{
					write(fd2,&c,1);
					printf("%c",c);
				}
			}
			remove(basepath);
			strcpy(basepath,"\0");
                        for(j=strlen(newpath)-1;newpath[j]!='/';j--);
                        for(int k=0;k<=j;k++)
                                strncat(basepath,&newpath[k],1);
			strcat(basepath,argv[2]);
                        rename(newpath,basepath);
			close(fd2);
			close(fd);
		}
                else if(strcmp(argv[1],"-nofilter")==0)		//applies no filter
                {
			while((d=read(fd,&c,1)) > 0)
                        {
				printf("%c",c);
			}
			close(fd);
                }
		else if(strcmp(argv[1],"-C")==0)	//counts the  number of words with given length
		{
			int len,k=0,j;
			char word[PATH_MAX];
			struct count{
				char word[PATH_MAX];
				int cnt;
			}*words;
			words=(struct count *)malloc(sizeof(struct count));
			printf("Enter length: ");
			scanf("%d",&len);
			while((d=read(fd,&c,1)) > 0)
			{
				if(isalpha(c))
					strncat(word,&c,1);
				else
				{
					if(strlen(word)==len)
					{
						for(j=0;j<k;j++)
						{
							if(strcmpi(words[j].word,word)==0)
							{
								words[j].cnt++;
								break;
							}
						}
						if(j==k)
						{
							k++;
							words=realloc(words,k*sizeof(struct count));
							strcpy(words[j].word,word);
							words[j].cnt=1;
						}
					}
					strcpy(word,"\0");
				}
			}
			close(fd);
			printf("%d letter words\tCount\n",len);
			for(j=0;j<k;j++)
				printf("%s\t\t%d\n",words[j].word,words[j].cnt);
		}
		else if(strcmp(argv[1],"-R")==0)	//to replace a word with another word
		{
			char old[PATH_MAX],new_[PATH_MAX],newpath[PATH_MAX],word[PATH_MAX];
			int j,cnt=0;
			printf("Enter the word which has to replaced: ");
			scanf("%s",old);
			printf("Enter the new word with which you would like to replace: ");
			scanf("%s",new_);
			for(j=strlen(basepath)-1;basepath[j]!='/';j--);
			for(int k=0;k<=j;k++)
				strncat(newpath,&basepath[k],1);
			strcat(newpath,"tmp.txt");
			int fd2=open(newpath,O_CREAT | O_WRONLY);
			while((d=read(fd,&c,1)) > 0)
			{
				if(isalpha(c))
					strncat(word,&c,1);
				else
				{
					if(strcmpi(word,old)==0)
					{
						cnt++;
						printf("\033[1;31m");	//To print in red colour
						printf("%s",new_);
						printf("\033[0m");	//To reset to default
						write(fd2,new_,strlen(new_));
					}
					else
					{
						printf("%s",word);
						write(fd2,word,strlen(word));
					}
					printf("%c",c);
					write(fd2,&c,1);
					strcpy(word,"\0");
				}
			}
			remove(basepath);
			strcpy(basepath,"\0");
			for(j=strlen(newpath)-1;newpath[j]!='/';j--);
                        for(int k=0;k<=j;k++)
				strncat(basepath,&newpath[k],1);
                        strcat(basepath,argv[2]);
			rename(newpath,basepath);
			printf("Replaced at %d places!\n",cnt);
			close(fd2);
			close(fd);
		}
		else if(strcmp(argv[1],"-P")==0)	//finds the instances of a particular pattern
		{
			char pattern[PATH_MAX],word[PATH_MAX];
			int i,cnt=0;
			printf("Enter a pattern that you would like to find: ");
			scanf("%s",pattern);
			strlwr(pattern);
			while((d=read(fd,&c,1)) > 0)
                        {
				char ch=tolower(c);
				if(ch==pattern[i])
				{
					strncat(word,&c,1);
					i++;
					if(strcmpi(word,pattern)==0)
					{
						printf("\033[1;31m");  //To highlight
						printf("%s",word);
						printf("\033[0m");  //To reset
						i=0;
						strcpy(word,"\0");
						cnt++;
					}
				}
				else
				{
					if(i==0)
						printf("%c",c);
					else
					{
						printf("%s",word);
						printf("%c",c);
						strcpy(word,"\0");
						i=0;
					}
				}
			}
			printf("\n");
			printf("Found %d matches!\n",cnt);
			close(fd);
		}
		else if(strcmp(argv[1],"-D")==0)	//deletes a word
		{
			char d_word[PATH_MAX],word[PATH_MAX],newpath[PATH_MAX];
			int i,j,cnt=0;
			printf("Enter the word that you would like to delete: ");
			scanf("%s",d_word);
			for(j=strlen(basepath)-1;basepath[j]!='/';j--);
			for(int k=0;k<=j;k++)
				strncat(newpath,&basepath[k],1);
                        strcat(newpath,"tmp.txt");
			int fd2=open(newpath,O_CREAT | O_WRONLY);
			while((d=read(fd,&c,1)) > 0)
			{
				if(isalpha(c))
					strncat(word,&c,1);
				else
				{
					if(strcmpi(word,d_word)==0)
						cnt++;
					else
					{
						write(fd2,word,strlen(word));
						printf("%s",word);
					}
					write(fd2,&c,1);
					printf("%c",c);
					strcpy(word,"\0");
				}
			}
			remove(basepath);
			strcpy(basepath,"\0");
			for(j=strlen(newpath)-1;newpath[j]!='/';j--);
			for(int k=0;k<=j;k++)
				strncat(basepath,&newpath[k],1);
			strcat(basepath,argv[2]);
			rename(newpath,basepath);
			printf("Deleted at %d places!\n",cnt);
			close(fd);
		}
                else
                {
			printf("Invalid filter!!\n");
                        return(-1);
                }
        }
        else
        {
		printf("Wrong number of arguments!!\n");
                return(-1);
        }
}
