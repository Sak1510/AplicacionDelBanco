//Version 2.0.1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <string.h>

//archiv.c
bool loginUser(char *, char *);
char *getActualUser();

int main(int arcg, char *argv[]) {
	//Carpeta DATA
	FILE *arch;
	dataArchivs();
	system("color 2");
	
	//Inicialización de las variables necesarias
	bool loop = true, welcome = true, fullScreen = false, showDataFolder = false;
	char startMode[100] = "", user[100] = "", comand[100] = "", fullSc[2] = "", showDF[2] = "", correctExit[2] = "";
	
	arch = fopen("data\\config\\startMode.txt", "r");
	fgets(startMode, 2, arch);
	fclose(arch);
	
	int opcS = atof(startMode), opc;
	
	//Comprobación de un cierre del ejecutable correcto
	arch = fopen("data\\config\\correctExit.txt", "r");
	fgets(correctExit, 2, arch);
	fclose(arch);
	
	//printf("mode: %s\n", correctExit);
	if(correctExit[0] == '0') {
		opcS = 0;
		
		arch = fopen("data\\config\\actualUser.txt", "w");
		fprintf(arch, "nobody");
		fclose(arch);
	}
	
	arch = fopen("data\\config\\correctExit.txt", "w");
	fprintf(arch, "0");
	fclose(arch);
	
	//Ciclo mientras el usuario lo decida
	while(loop) {
		arch = fopen("data\\config\\fullScreen.txt", "r");
		fgets(fullSc, 2, arch);
		fclose(arch);
		
		arch = fopen("data\\config\\showDataFolder.txt", "r");
		fgets(showDF, 2, arch);
		fclose(arch);
		
		if(showDataFolder) {
			printf("\tmode: %s\n", showDF);
			
			arch = fopen("data\\comandSystem.bat", "w");
			if(showDF[0] == '0') {
				fprintf(arch, "@echo off\n attrib -s -h \"data\" ");
				printfSleep(" \tAhora se muestra la carpeta \"data\"!\n");
			} else {
				fprintf(arch, "@echo off\n attrib +s +h \"data\" ");
				printfSleep(" \tSe ah ocultado la carpeta \"data\"!\n");		
			} fclose(arch);
			
			system("data\\comandSystem.bat");
			showDataFolder = !showDataFolder;
		}

		if(fullScreen) {
			printf("\tmode: %s\n", fullSc);
			
			if(fullSc[0] == '0') {
				AltEnter();
				//sizeLetter(1);
			} else {
				AltEnter();
				//sizeLetter(0);
			} fullScreen = !fullScreen;
		}
		
		switch(opcS) {
			case 0: //Primera ejecucion del programa
				if(welcome) {
					//printfStart();
					welcome = !welcome;
				}
				
				scanf("%s", &comand);
				opc = mainComandInt(comand, 0);
				switch(opc) {
					case 0: //Logearse a una cuenta
						if(login()) loop = !loop;
						break;
		
					case 1: //Crear nuevo usuario
						createUser();
						break;
						
					case 2: //Salir del banco
						Exit(0); 
						loop = !loop; 
						break; 
		
					case 3: //Pedir ayuda con los comandos
						help(0);
						break;
						
					case 4: //Mostrar carpeta "data"
						changeConfigBool("showDataFolder.txt");
						showDataFolder = !showDataFolder;
						break;
						
					case 5: //Cambiar pantalla completa
						changeConfigBool("fullScreen.txt");
						fullScreen = !fullScreen;
						break;
						
					default: printfSleep(" \tSi necesitas ayuda, escribe \"help\"\n", 10, 100, "");
			} break;
			
			
			case 1: //Segunda ejecucion del programa
				strcpy(user, getActualUser());
				
				if(welcome) {	
					printfSleep("Bienvenido \"&\"!\nQue vamos a hacer?\n", 10, 100, user);
					welcome = !welcome;
				}
				
				scanf("%s", &comand);
				opc = mainComandInt(comand, 1);
				
				switch(opc) {
					case 0: //Deslogearse de una cuenta
						logout();
						loop = !loop;
						break;
					
					case 1: //Cambiar contraseña del usuario actual
						changePassword();
						loop = !loop;
						break;
						
					case 2: //Depositar dinero a la cuenta
						deposit();
						break;
					
					case 3: //Retirar dinero de la cuenta
						remove_();
						break;
					
					case 4: //Consultar saldo
						consult();
						break;
		
					case 5: //Salir del banco
						Exit(1);
						loop = !loop;
						break;
						
					case 6: //Pedir ayuda
						help(1);
						break;
						
					default: printfSleep(" \tRecuerda & que si necesitas ayuda, escribe \"help\"!\n", 10, 100, user);
			} break;
			
			default: printfSleep(" \tjsjsjs valio camote", 10, 10, "");
		}
	}
	
	arch = fopen("data\\config\\correctExit.txt", "w");
	fprintf(arch, "1");
	fclose(arch);
	return 0;
}
