#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

int mainComandInt(char userComand[]) {
	//Siempre cambiar el tamaño del array y size cada vez que se vaya a agregar un nuevo comando
	int size = 6;
	char comands[6][15] = {
		"exit",
		"loggin", 
		"logout", 
		"createuser",
		"help",
		"changepassword"
	};
	
	int i, j = 0, sum = 0, returned;
	bool loop = true;
	while(loop && j < size) {
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
	printf("\tchangepassword\t-> Cambiar la password de un usuario\n");
	return 0;
}
