#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int mainComandInt(char userComand[], int mode) {
	//Siempre cambiar el tama�o del array y size cada vez que se vaya a agregar un nuevo comando
	int size = 9;
	char comands[2][9][15] = {{
		//Primera ejecucion
		"login",			//0
		"createUser",		//1
		
		"exit",				//2
		"help",				//3
		"showDataFolder",	//4
		"fullScreen"		//5
	}, {
		//Segunda ejecucion
		"logout",			//0
		"changePassword",	//1
		"deposit",			//2
		"remove",			//3
		"consult",			//4
		
		"exit",				//5
		"help",				//6
		"showDataFolder",	//7
		"fullScreen"		//8
	}};
	
	
	int i = 0, j = 0, sum = 0, returned;
	bool loop = true;
	while(loop && i < size) {
		if(strcmp(comands[mode][i], userComand) == 0) { 
			loop = !loop;
			return i;
		} else i++;
	} return -1;
}
