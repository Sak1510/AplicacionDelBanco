//Version 2.0.3
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <string.h>

//archiv.c
bool loginUser(char *, char *);
char *getActualUser();

int main(int arcg, char *argv[]) {
	//		ZONA DEBUG	 	//
	char horaActual[100] = " ";
	strcat(horaActual, fechaActual());
	
	//		ZONA DEBUG		//
	
	//Carpeta DATA
	FILE *arch;
	dataArchivs();
	system("color 2");
	
	//Inicialización de las variables necesarias
	bool loop = true, welcome = true, fullScreen = false, showDataFolder = false;
	char startMode[100] = "", user[100] = "", comand[100] = "", fullSc[2] = "", showDF[2] = "", correctExit[2] = "", tempDir[100] = "", tempStr[100] = "";
	
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
		arch = fopen("data\\config\\actualUser.txt", "r");
		fgets(user, 100, arch);
		fclose(arch);
		
		strcpy(tempDir, "data\\users\\");
		strcat(tempDir, user);
		strcat(tempDir, "\\loginHistorial.txt");
		
		strcpy(tempStr, "logout: forzado\t\tfecha: ");
		strcat(tempStr, fechaActual());
		strcat(tempStr, "\n");
		
		arch = fopen(tempDir, "a");
		fprintf(arch, tempStr);
		fclose(arch);
		
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
			//printf("\tmode: %s\n", showDF);
			arch = fopen("data\\comandSystem.bat", "w");
			if(showDF[0] == '1') {
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
			//printf("\tmode: %s\n", fullSc);
			if(fullSc[0] == '0') {
				AltEnter();
				printfSleep(" \tAhora estas en pantalla completa!\n", 10, 100, "");
				//sizeLetter(1);
			} else {
				AltEnter();
				printfSleep(" \tAhora estas en modo ventana!\n", 10, 100, "");
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
					
					//Sin distinción
					case 3: help(0); break; //Pedir ayuda con los comandos
					case 4: changeConfigBool("showDataFolder.txt"); showDataFolder = !showDataFolder; 	break; //Mostrar carpeta "data"
					case 5: changeConfigBool("fullScreen.txt"); 	fullScreen = !fullScreen; 			break; //Cambiar pantalla completa
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
						if(changePassword()) loop = !loop;
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
						
					case 5: //Mostrar inicios de sesión
						showLoginHistorial();
						break;
					
					//Sin distinción
					case 6: Exit(1); loop = !loop; 	break; //Salir del banco
					case 7: help(1); break; //Pedir ayuda
					case 8: changeConfigBool("showDataFolder.txt"); showDataFolder = !showDataFolder; 	break; //Mostrar carpeta "data"
					case 9: changeConfigBool("fullScreen.txt"); 	fullScreen = !fullScreen; 			break; //Cambiar pantalla completa
					default: printfSleep(" \tRecuerda & que si necesitas ayuda, escribe \"help\"!\n", 10, 100, user);
			} break; default: printfSleep(" \tjsjsjs valio camote", 10, 10, "");
	}}
	
	arch = fopen("data\\config\\correctExit.txt", "w");
	fprintf(arch, "1");
	fclose(arch);
	return 0;
}
