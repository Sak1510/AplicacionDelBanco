#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <time.h>

int mainComandInt(char userComand[]) {
	//Siempre cambiar el tamaño del array y size cada vez que se vaya a agregar un nuevo comando
	int size = 9;
	char comands[9][15] = {
		"exit",
		"login", 
		"logout", 
		"createuser",
		"help",
		"changepassword",
		"deposit",
		"remove",
		"consult",
		"request"
	};
	
	int i = 0, j = 0, sum = 0, returned;
	bool loop = true;
	while(loop && i < size) {
		if(strcmp(comands[i], userComand) == 0) { 
			loop = !loop; 
			return i;
		} else i++;
	} return -1;
}
