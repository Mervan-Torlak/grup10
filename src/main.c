#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/shell.h"

int main (int argc, char **argv, char **envp)
{
	int numberOfCharacterCommands = 90;

	char temp[numberOfCharacterCommands];
	environ=envp;
	char *commands[15];
	int numberOfCommands;
	int situation =1;
	

	while(situation)//Kullanıcının girdiği komutu döngüye alarak kontrol eder
	{
		waitCommand();

		memset(temp, '\0', numberOfCharacterCommands);
		fgets(temp, numberOfCharacterCommands,stdin); //Kullanıcının girdiği değeri tempe aktarır

		if(strlen(temp) > 80){

			printf("Girilen komut maksimum 80 karakterden oluşmalıdır...\n");
			continue;
		};

		if((commands[0] = strtok(temp," \n\t")) == NULL) continue;
		
		numberOfCommands = 1;

		if(temp[0] == ' ' || temp[0] == '\t') { //En sona boşluk ekler

			printf("Komut onunde veya sonunda bosluk olmamalı!\n");
			continue;
		}

		while((commands[numberOfCommands] = strtok(NULL, " \n\t")) != NULL) {
			numberOfCommands++;
		}

		if(numberOfCommands > 10) {
			
			printf("Bir komut boslukla ayrilmis en fazla 10 kelimeden olusabilir!\n");
			continue;
		}
		commandBol(commands);
	}
}
