//Version 1.2.4
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <time.h>

struct mode {
	bool login;
	
	char actual[100];
	char direct[100];
	char temp[100];
	
	float money;
	float moneyTemp;
};

struct stringC {
	char exit[100][1000];
	char login[1000][1000];
};

//archiv.c
bool loginUser(char *, char *);

//functions.c
int *floatToTxt(float, int);
float txtToFloat(char[], int);
int sizeNum10(float);

//Función ejecutadora principal
int main(int arcg, char *argv[]) {
	//Carpeta DATA
	FILE *arch;
	arch = fopen("data\\dataExist.txt", "r");
	if(arch == NULL) {
		//Creacion de la carpeta data
		arch = fopen("comandSystem.bat", "w");
		fprintf(arch, "@echo off\nMD data");
		fclose(arch);
		
		system("comandSystem.bat");
		
		arch = fopen("data\\dataExist.txt", "w");
		fprintf(arch, "FOLDER \"DATA\" CREATED");
		fclose(arch);
		
		//Creacion de las subcarpetas
		arch = fopen("data\\comandSystem.bat", "w");
		fprintf(arch, "@echo off\nDEL comandSystem.bat\nattrib +s +h \"data\"");
		fclose(arch);
		
		system("data\\comandSystem.bat");
	}
	
	//Subcarpeta data\users
	arch = fopen("data\\users\\usersExist.txt", "r");
	if(arch == NULL) {
		arch = fopen("data\\comandSystem.bat", "w");
		fprintf(arch, "@echo off\ncd data\nMD users");
		fclose(arch);
		
		system("data\\comandSystem.bat");
		
		arch = fopen("data\\users\\usersExist.txt", "w");
		fprintf(arch, "FOLDER \"CONFIG\" CREATED");
		fclose(arch);
	}
	
	//Subcarpeta data\config
	arch = fopen("data\\config\\configExist.txt", "r");
	if(arch == NULL) {
		arch = fopen("data\\comandSystem.bat", "w");
		fprintf(arch, "@echo off\ncd data\nMD config");
		fclose(arch);
		
		system("data\\comandSystem.bat");
		
		arch = fopen("data\\config\\configExist.txt", "w");
		fprintf(arch, "FOLDER \"CONFIG\" CREATED");
		fclose(arch);
		
		//Creacion de los archivos de data\config	
		arch = fopen("data\\config\\startMode.txt", "w");
		fprintf(arch, "0");
		fclose(arch);
		
		arch = fopen("data\\config\\actualUser.txt", "w");
		fprintf(arch, "nobody");
		fclose(arch);
		
		arch = fopen("data\\config\\completScreen.txt", "w");
		fprintf(arch, "1");
		fclose(arch);
		
		arch = fopen("data\\config\\showDataFolder.txt", "w");
		fprintf(arch, "1");
		fclose(arch);
	}
	
	//Inicialización del ejecutable
	system("color 2");
	AltEnter();
	sizeLetter();

	//		ZONA DEBUG		//

	//		ZONA DEBUG		//
	//Inicialización de las variables necesarias
	srand(time(NULL));
	bool loop = true, welcome = true;
	
	struct mode user;
	user.login = false;
	strcpy(user.actual, "");
	strcpy(user.direct, "");
	strcpy(user.temp, "");
	user.money = 0;
	user.moneyTemp = 0;
	
	//Mejora grafica (para la 2.0.0 terminar)
	struct stringC stringsC;
	
	//Exit (Case "0")
	strcpy(stringsC.exit[0], " \tHaz salido del banco!\n");
	strcpy(stringsC.exit[1], " \tGracias por escogernos!!\n");
	strcpy(stringsC.exit[2], " \tSaliendo");
	
	int i, j, k;
	char newUser[100] = "", passwordUser[100] = "", temp12[100] = "";
	
	arch = fopen("data\\config\\startMode.txt", "r");
	fgets(temp12, 100, arch);
	fclose(arch);
	int opcS = atof(temp12), opc;
	
	//Ciclo mientras el usuario lo decida
	while(loop) {
	char userComand[100] = "", subUserComand[100] = "", directTemp[100] = "";
	
	switch(opcS) {
		case 0: //Primera ejecucion del programa
		if(welcome) {
			//printfStart();
			welcome = !welcome;
		}
		scanf("%s", &userComand);
		opc = mainComandInt(userComand);		
		
		switch(opc) {
			case 0: //Salir del banco
				for(i = 1; i < 4; i++) printfSleep(stringsC.exit[i], 10, 500, "");
				for(i = 0; i < 3; i++) {
					printf(". ");
					Sleep(1000);
				} Sleep(500);
				loop = !loop;
				break;

			case 1: //Logearse a una cuenta
				if(!user.login) {
					char user_[100] = "", password[100] = "";
					printfSleep(" \tDame el usuario al que te vas a loggear: ", 10, 100, "");
					scanf("%s", &user_);
				
					if(existUser(user_)) {
						printfSleep(" \tDame el password del usuario &: ", 10, 100, user_);
						scanf("%s", &password);
						
						if(loginUser(user_, password)) {
							strcpy(user.actual, user_);
							printfSleep(" \tHaz logeado a &!\n", 10, 100, user_);
							
							arch = fopen("data\\config\\startMode.txt", "w");
							fprintf(arch, "1");
							fclose(arch);
							
							arch = fopen("data\\config\\actualUser.txt", "w");
							fprintf(arch, user_);
							fclose(arch);
							
							arch = fopen("data\\comandSystem.bat", "w");
							fprintf(arch, "@echo off \nstart AplicacionDelBanco.exe");
							fclose(arch);
							
							printfSleep(" \tEl ejecutable se cerrara en unos segundos para poder loggearse en el usuario actual\n", 10, 100, "");
							printfSleep(" \tLoggeando", 10, 100, "");
							for(i = 0; i < 3; i++) {
								printf(". ");
								Sleep(1000);
							} loop = !loop;
							
							system("data\\comandSystem.bat");
						} else printfSleep(" \tEl password de \"&\" no es correcta\n\a", 10, 100, user_);
					} else printfSleep(" \tEl usuario \"&\" no existe!\n\a", 10, 100, user_);
				} else printfSleep(" \tYa estas logeado en &!\n\a", 10, 100, user.actual);
				break;
				
			case 3: //Crear nuevo usuario
				printfSleep(" \tDame el nombre del usuario: ", 10, 100, "");
				scanf("%s", &newUser);
				createUser(newUser);
				break;
					
			case 4: //Pedir ayuda con los comandos
				help(1);
				break;
				
			default:
				printfSleep(" \tSi necesitas ayuda, escribe \"help\"\n", 10, 100, "");
		} break;
		
		
		case 1: //Segunda ejecucion del programa	
		if(welcome) {
			arch = fopen("data\\config\\actualUser.txt", "r");
			fgets(user.actual, 100, arch);
			fclose(arch);
			
			printfSleep("Bienvenido \"&\"!\nQue vamos a hacer?\n", 10, 100, user.actual);
			welcome = !welcome;
		}
		
		scanf("%s", &userComand);
		opc = mainComandInt(userComand);
		
		switch(opc) {
			case 0: //Salir del banco
				for(i = 1; i < 4; i++) printfSleep(stringsC.exit[i], 10, 500, "");
				for(i = 0; i < 3; i++) {
					printf(". ");
					Sleep(1000);
				} Sleep(500);
				loop = !loop;
				
				arch = fopen("data\\config\\startMode.txt", "w");
				fprintf(arch, "0");
				fclose(arch);
				break;

			case 2: //Deslogearse de una cuenta
				printfSleep( " \tHaz salido de \"&\"!\n", 10, 100, user.actual);
				arch = fopen("data\\config\\actualUser.txt", "w");
				fprintf(arch, "nobody");
				fclose(arch);
				
				printfSleep(" \tVolveras a la pagina de inicio en unos segundos!\n\tSaliendo", 10, 100, "");
				for(i = 0; i < 3; i++) {
					printf(". ");
					Sleep(1000);
				} loop = !loop;
				
				arch = fopen("data\\config\\startMode.txt", "w");
				fprintf(arch, "0");
				fclose(arch);
				
				arch = fopen("data\\comandSystem.bat", "w");
				fprintf(arch, "@echo off\n start AplicacionDelBanco.exe");
				fclose(arch);
				
				system("data\\comandSystem.bat");
				break;			
				
			case 4: //Pedir ayuda con los comandos
				help(2);
				break;
			
			case 5: //Cambiar contraseña del usuario actual
				printfSleep(" \tDame la contraseña del usuario: ", 10, 100, "");
				scanf("%s", &subUserComand);
				
				changePassword(user.actual, subUserComand);
				
				arch = fopen("data\\config\\startMode.txt", "w");
				fprintf(arch, "0");
				fclose(arch);
				
				arch = fopen("data\\comandSystem.bat", "w");
				fprintf(arch, "@echo off\n start AplicacionDelBanco.exe");
				fclose(arch);
				
				arch = fopen("data\\config\\actualUser.txt", "w");
				fprintf(arch, "nobody");
				fclose(arch);
				
				printfSleep(" \tVolveras a la pagina de inicio en unos segundos!\n\tDeberas volverte a loggear a tu usuario con la nueva contraseña!\n", 10, 100, "");
				printfSleep(" \tSaliendo", 10, 100, "");
				for(i = 0; i < 3; i++) {
					printf(". ");
					Sleep(1000);
				} loop = !loop;
				
				system("data\\comandSystem.bat");
				break;
				
			case 6: //Depositar dinero a la cuenta
				strcpy(user.direct, "data\\users\\");
				strcat(user.direct, user.actual);
				strcat(user.direct, "\\capital.txt");
				
				arch = fopen(user.direct, "r");
				fgets(user.temp, 100, arch);
				fclose(arch);
				
				user.money = atof(user.temp);
				printf("\t%.2f\n", user.money);
				printfSleep(" \tSaldo actual: &\n", 10, 100, user.temp);
				
				printfSleep(" \tCuanto dinero vas a depositar? ", 10, 100, "");
				scanf("%f", &user.moneyTemp);
				
				if(user.moneyTemp >= 0) {
					user.money += user.moneyTemp;
					snprintf(user.temp, sizeof(user.temp), "%.2f", user.money);
					
					arch = fopen(user.direct, "w");
					fprintf(arch, user.temp);
					fclose(arch);
					
					printfSleep(" \tDinero depositado exitosamente!!\n", 10, 100, "");
				} else printfSleep(" \tNo puedes depositar cantidades negativas!!\n\a", 10, 100, "");
				break;
			
			case 7: //Retirar dinero de la cuenta
				strcpy(user.direct, "data\\users\\");
				strcat(user.direct, user.actual);
				strcat(user.direct, "\\capital.txt");
				arch = fopen(user.direct, "r");
				fgets(user.temp, 100, arch);
				fclose(arch);
				
				user.money = atof(user.temp);
				
				printfSleep(" \tCuanto dinero vas a retirar? ", 10, 100, "");
				scanf("%f", &user.moneyTemp);
				
				if(user.moneyTemp >= 0) {
					if(user.money -user.moneyTemp > 0) {
						user.money -= user.moneyTemp;
						snprintf(user.temp, sizeof(user.temp), "%.2f", user.money);
				 		printfSleep(" \tSaldo actual: &\n", 10, 100, user.temp);
						
						arch = fopen(user.direct, "w");
						fprintf(arch, user.temp);
						fclose(arch);
						
						printfSleep(" \tDinero retirado exitosamente!!\n", 10, 100, "");							
					} else printfSleep(" \tNo tienes el saldo suficiente!!\n\a", 10, 100, "");
				} else printfSleep(" \tNo puedes retirar cantidades negativas!!\n\a", 10, 100, "");
				break;
			
			case 8: //Consultar saldo
				strcpy(user.direct, "data\\users\\");
				strcat(user.direct, user.actual);
				strcat(user.direct, "\\capital.txt");
				arch = fopen(user.direct, "r");
				fgets(user.temp, 100, arch);
				fclose(arch);
				
				printfSleep(" \tSaldo actual de &: ", 10, 100, user.actual);
				printfSleep(user.temp, 10, 100, "");
				printf("\n");
				break;

			default:
				printfSleep(" \tSi necesitas ayuda, escribe \"help\"\n", 10, 100, "");
		} break;
	}} return 0;
}
