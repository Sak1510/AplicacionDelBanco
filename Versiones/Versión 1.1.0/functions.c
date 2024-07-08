#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

int mainComandInt(char userComand[]) {
	//Siempre cambiar el tamaño del array para y la segunda condicion del while
	//al añadir nuevos comandos
	
	char comands[5][15] = {
		"exit",
		"loggin", 
		"logout", 
		"createuser",
		"help"
	};
	
	int i, j = 0, sum = 0, returned;
	bool loop = true;
	while(loop && j < 5) {
		for(i = 0; i < strlen(comands[j]); i++) {
			if(userComand[i] == comands[j][i]) sum++;
		}
		
		if(sum == strlen(comands[j])) loop = false;
		else { j++; sum = 0; }
	}
	
	if(!loop) returned = j;
	else returned = -1;
	
	return returned;
}

int help() {
	printf("\tloggin\t\t-> Acceder a un usuario\n");
	printf("\tlogout\t\t-> Salir de un usuario\n");
	printf("\tcreateuser\t-> Crear un nuevo usuario\n");
	printf("\texit\t\t-> Salir del banco\n");
	
	return 0;
}
