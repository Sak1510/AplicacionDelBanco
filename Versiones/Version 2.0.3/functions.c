#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int mainComandInt(char userComand[], int mode) {
	//Siempre cambiar el tamaño del array y size cada vez que se vaya a agregar un nuevo comando
	int size = 15;
	char comands[2][15][100] = {{
		//Primera ejecucion
		"login",				//0
		"createUser",			//1
		
		"exit",					//2
		"help",					//3
		"showDataFolder",		//4
		"fullScreen"			//5
	}, {
		//Segunda ejecucion
		"logout",				//0
		"changePassword",		//1
		"deposit",				//2
		"remove",				//3
		"consult",				//4
		"showLoginHistorial",	//5
		
		"exit",					//6
		"help",					//7
		"showDataFolder",		//8
		"fullScreen",			//9
		
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
