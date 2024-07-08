//Version 1.2.3
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
	//Inicialización del ejecutable
	system("color 2");
	//AltEnter();
	//sizeLetter();

	//		ZONA DEBUG		//

	//		ZONA DEBUG		//
	
	//printfStart();
	
	//Inicialización de las variables necesarias
	FILE *arch;
	srand(time(NULL));
	bool loop = true;
	
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
	char newUser[100] = "", passwordUser[100] = "";
	
	//Ciclo mientras el usuario lo decida
	while(loop) {
		char userComand[100] = "", subUserComand[100] = "", directTemp[100] = "";
		scanf("%s", &userComand);
		
		int opc = mainComandInt(userComand);
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
				
					if(existFolder(user_)) {
						printfSleep(" \tDame el password del usuario &: ", 10, 100, user_);
						scanf("%s", &password);
						
						if(loginUser(user_, password)) {
							strcpy(user.actual, user_);
							printfSleep(" \tHaz logeado a &!\n", 10, 100, user_);
							user.login = true;
						} else printfSleep(" \tEl password de \"&\" no es correcta\n\a", 10, 100, user_);
					} else printfSleep(" \tEl usuario \"&\" no existe!\n\a", 10, 100, user_);
				} else printfSleep(" \tYa estas logeado en &!\n\a", 10, 100, user.actual);
				break;
			
			case 2: //Deslogearse de una cuenta
				if(user.login) {
					printfSleep( " \tHaz salido de \"&\"!\n", 10, 100, user.actual);	
					user.login = false;
				} else printfSleep(" \tNo estas logeado en algun usuario!\n\a", 10, 100, "");
				break;
					
			case 3: //Crear nuevo usuario
				printfSleep(" \tDame el nombre del usuario: ", 10, 100, "");
				scanf("%s", &newUser);
				//printfSleep(" \t&\n", 10, 100, newUser);
				if(!existFolder(newUser)) {
					createFolder(newUser);
					
					printfSleep(" \tCrea su password: ", 10, 100, "");
					scanf("%s", &passwordUser);
					
					createUserArhivs(newUser);
					createPassword(newUser, passwordUser);
				} else printfSleep(" \tEl usuario & ya existe!\n\a", 10, 100, newUser);
				break;
				
			case 4: //Pedir ayuda con los comandos
				help();
				break;
				
			case 5: //Cambiar contraseña a usuario existente
				printfSleep(" \tDame el usuario al que le vas a cambiar el password: ", 10, 100, "");
				scanf("%s", &userComand);
				if(existFolder(userComand)) {
					printfSleep(" \tDame la password actual: ", 10, 100, "");
					scanf("%s", &subUserComand);
					changePassword(userComand, subUserComand);
				} else printfSleep(" \tEl usuario \"&\" no existe.\n\a", 10, 100, userComand);
				break;
				
			case 6: //Depositar dinero a la cuenta
				if(user.login) {
					strcpy(user.direct, user.actual);
					strcat(user.direct, "\\capital.txt");
					arch = fopen(user.direct, "r");
					fgets(user.temp, 100, arch);
					fclose(arch);
					
					user.money = atof(user.temp);
					printf("\t%.2f\n", user.money);
					printfSleep(" \tSaldo actual: &\n", 10, 100, user.temp);
					
					printfSleep(" \tCuanto dinero vas a depositar? ", 10, 100, "");
					scanf("%f", &user.moneyTemp);
					
					if(user.moneyTemp > 0) {
						user.money += user.moneyTemp;
						snprintf(user.temp, sizeof(user.temp), "%.2f", user.money);
						
						arch = fopen(user.direct, "w");
						fprintf(arch, user.temp);
						fclose(arch);
						
						printfSleep(" \tDinero depositado exitosamente!!\n", 10, 100, "");
					} else printfSleep(" \tNo puedes depositar cantidades negativas!!\n\a", 10, 100, "");
				} else printfSleep(" \tNo estas logeado a alguna cuenta!\n\a", 10, 100, "");
				break;
			
			case 7: //Retirar dinero de la cuenta
				if(user.login) {
					strcpy(user.direct, user.actual);
					strcat(user.direct, "\\capital.txt");
					arch = fopen(user.direct, "r");
					fgets(user.temp, 100, arch);
					fclose(arch);
					
					user.money = atof(user.temp);
					
					printfSleep(" \tCuanto dinero vas a retirar? ", 10, 100, "");
					scanf("%f", &user.moneyTemp);
					
					if(user.moneyTemp > 0) {
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
				} else printfSleep(" \tNo estas logeado a alguna cuenta!\n\a", 10, 100, "");
				break;
			
			case 8: //Consultar saldo
				if(user.login) {
					strcpy(user.direct, user.actual);
					strcat(user.direct, "\\capital.txt");
					arch = fopen(user.direct, "r");
					fgets(user.temp, 100, arch);
					fclose(arch);
					
					printfSleep(" \tSaldo actual de &: ", 10, 100, user.actual);
					printfSleep(user.temp, 10, 100, "");
					printf("\n");
				} else printfSleep(" \tNo estas logeado a alguna cuenta!\n\a", 10, 100, "");
				break;
			
			default:
				printfSleep(" \tSi necesitas ayuda, escribe \"help\"\n", 10, 100, "");
	}} return 0;
}

//Pendiente revisar el correcto funcionamiento del floatToTxt() <--> Ya lo mandamos a la mrd no te preocupes;
