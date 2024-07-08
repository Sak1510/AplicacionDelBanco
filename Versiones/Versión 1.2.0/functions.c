#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

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
		"consult"
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
	printf("\tlogin\t\t-> Acceder a un usuario\n");
	printf("\tlogout\t\t-> Salir de un usuario\n");
	printf("\tcreateuser\t-> Crear un nuevo usuario\n");
	printf("\tchangepassword\t-> Cambiar la password de un usuario\n\n");
	
	printf("\tconsult\t\t-> Consular saldo actual\n");
	printf("\tdeposit\t\t-> Depositar dinero a la cuenta\n");
	printf("\tremove\t\t-> Retirar dinero de la cuenta\n");
	
	printf("\texit\t\t-> Salir del banco\n");
	return 0;
}



void addSaldo(char userDirect[], float dinero) {
	FILE *arch;
	arch = fopen(userDirect, "w");
	fprintf(arch, (char)dinero);
	fclose(arch);
}

int consultSaldo(char userDirect[]) {
	
	return 0;
}
