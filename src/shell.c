#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>

#include "shell.h"

int Array[100] = {0};

char *builtin_str[]={
	"cd",
	"exit",
	"showpid"
};

int (*builtin_func[])(char**) = {
	&cDirectory,
	&exit1,
	&showpid
};

int size()//Boyutu döndürmemizi sağlayan fonksiyon
{
	return sizeof(builtin_str)/sizeof(char *);
}

int cDirectory(char **command)
{
	if (command[1]==NULL)
	{
		fprintf(stderr,"Dizin belirtilmedi. \"cd\"\n");
	}
	else //2. değişken boş değilse içeri girer
	{
		if (chdir(command[1])!=0) //2.değişken 0 değilse içeri girer
		{
			perror("Hata");
		}
	}
	return 1;
}

int exit1(char **command)
{
	int situation;
	while (!waitpid(-1,&situation,WNOHANG)){}
	exit(0);
}

int showpid(char **command)
{
	int i = 0;
	while(Array[i] != 0) {
		printf("%d\n", Array[i]);
		i++;
	}
}

int commandBol(char * command[])
{
	int pipeIn = -1;
	int bagKo = -1;
	int standartOut;
	int situation;
	int backGround = 0;
	int i=0,j=0,k;
	int file;
	char *commands[256];


	while(command[j] != NULL)
	{
		if ((strcmp(command[j],"|") == 0) || (strcmp(command[j],">") == 0) || (strcmp(command[j],"<") == 0) || (strcmp(command[j],"&") == 0))
		{
			break;
		}
		commands[j] = command[j];
		j++;
	}

	commands[j]=NULL;

	int m;
	if (command[0] == NULL)//Gönderilen komut değeri NULL ise 1 değeri döner
	{
		printf ("Bos komut.\n");
		return 1; 
	}

	for (m = 0 ; m < size() ; m++)//cd,showpid veya exit komutları girildiğinde fonksiyonda gerekli olan işlemleri yapar
	{
		
		if (strcmp(command[0],builtin_str[m])==0)
		{
			(*builtin_func[m])(command);
			return 1;
		}
	}
	
	commands[i]==NULL;
	run(commands, backGround);

	return 1;
}

int run(char **command,int backGround)
{
	if (backGround ==0) //Komutun arkaplan olup olmadığına bakar
	{
		int pid;
		int durum;
		pid=fork();

		for(int i = 0; i < 100; i++){
			if(Array[i] == 0){
				Array[i] = pid;
				break;
			}
		}

		if (pid == 0) 
		{
			if (execvp(command[0],command) == -1)
			{
				printf("Hata: Komut bulunamadı.\n");
				kill(getpid(),SIGTERM);
			}
		}

		else if (pid < 0)
		{
			perror("Hata: Process olusturulamadi.\n");
		}

		else //Çocuk proses bittiği zaman buraya girer
		{
			waitpid(pid, NULL, 0);
		}

		return 1;
	}

	return 1;
}

void waitCommand()
{
	char hostn[1204] = "";
	gethostname(hostn, sizeof(hostn));
	printf(MAG "%s/: " RESET YEL "sau > " RESET, getcwd(bulunanDizin, 1024));
}