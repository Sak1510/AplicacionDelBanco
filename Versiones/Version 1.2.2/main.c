//Version 1.2.2
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
	AltEnter();
	sizeLetter();
	printfStart();
	
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
	strcpy(stringsC.exit[0], "\tHaz salido del banco!\n");
	strcpy(stringsC.exit[1], "\tGracias por escogernos!!\n");
	strcpy(stringsC.exit[2], "\tSaliendo");
	
	//Login (Case "1")
	strcpy(stringsC.login[0], "\tDame el usuario al que te vas a loggear: ");
	strcpy(stringsC.login[1], "\tDame el password del usuario %s: ");
	
	
	int i, j, k;
	char newUser[100] = "", passwordUser[100] = "";
	
	
	//Ciclo mientras el usuario lo decida
	while(loop) {
		char userComand[100] = "", subUserComand[100] = "", directTemp[100] = "";
		scanf("%s", &userComand);
		
		int opc = mainComandInt(userComand);
		
		switch(opc) {
			case 0: //Salir del banco
				for(i = 1; i < 4; i++) printfSleep(stringsC.exit[i], 10, 500);
				for(i = 0; i < 3; i++) {
					printf(". ");
					Sleep(1000);
				} Sleep(500);
				loop = !loop;
				break;
				
			case 1: //Logearse a una cuenta
				if(!user.login) {
					char user_[100] = "", password[100] = "";
					printfSleep(stringsC.login[0], 10, 100);
					scanf("%s", &user_);
				
					if(existFolder(user_)) {
						printfSleep(stringsC.login[1], 10, 100, user_);
						scanf("%s", &password);
						
						if(loginUser(user_, password)) {
							strcpy(user.actual, user_);
							//printf("\t%s\n", actualUser);
							printf("\tHaz logeado a %s!\n", user.actual);
							user.login = true;
						} else printf("\tEl password de \"%s\" no es correcta\n\a", user_);
					} else printf("\tEl usuario \"%s\" no existe!\n\a", user_);
				} else printf("\tYa estas logeado en %s!\n\a", user.actual);
				break;
			
			case 2: //Deslogearse de una cuenta
				if(user.login) {
					printf("\tHaz salido de \"%s\"!\n", user.actual);				
					user.login = false;
				} else printf("\tNo estas logeado en algun usuario!\n\a");
				break;
					
			case 3: //Crear nuevo usuario
				printf("\tDame el nombre del usuario: ");
				scanf("%s", &newUser);
				printf("\t%s\n", newUser);
				if(!existFolder(newUser)) {
					createFolder(newUser);
					
					printf("\tCrea su password: ");
					scanf("%s", &passwordUser);
					
					createUserArhivs(newUser);
					createPassword(newUser, passwordUser);
				} else printf("\tEl usuario %s ya existe!\n\a", newUser);
				break;
				
			case 4: //Pedir ayuda con los comandos
				help();
				break;
				
			case 5: //Cambiar contraseña a usuario existente
				printf("\tDame el usuario al que le vas a cambiar el password: ");
				scanf("%s", &userComand);
				if(existFolder(userComand)) {
					printf("\tDame la password actual: ");
					scanf("%s", &subUserComand);
					changePassword(userComand, subUserComand);
				} else printf("\tEl usuario \"%s\" no existe.\n\a", userComand);
				break;
				
			case 6: //Depositar dinero a la cuenta
				if(user.login) {
					strcpy(user.direct, user.actual);
					strcat(user.direct, "\\capital.txt");
					user.money = 0;
					
					for(i = 0; i < 3; i++) { user.money += txtToFloat(user.direct, i)*pow(10, -i); }
					printf("\tSaldo actual: %.2f\n", user.money);
					
					printf("\tCuanto dinero vas a depositar? ");
					scanf("%f", &user.moneyTemp);
					
					if(user.moneyTemp > 0) {
						user.money += user.moneyTemp;
						strcpy(user.temp, floatToTxt(user.money, 0));
						
						arch = fopen(user.direct, "w");
						fprintf(arch, user.temp);
						fclose(arch);
						
						printf("\tDinero depositado exitosamente!!\n");
					} else printf("\tNo puedes depositar cantidades negativas!!\n\a");
				} else printf("\tNo estas logeado a alguna cuenta!\n\a");
				break;
			
			case 7: //Retirar dinero de la cuenta
				if(user.login) {
					strcpy(user.direct, user.actual);
					strcat(user.direct, "\\capital.txt");
					user.money = 0;
					
					for(i = 0; i < 3; i++) { user.money += txtToFloat(user.direct, i)*pow(10, -i); }
					
					printf("\tCuanto dinero vas a retirar? ");
					scanf("%f", &user.moneyTemp);
					
					if(user.moneyTemp > 0) {
						user.money -= user.moneyTemp;
				 		printf("\tSaldo actual: %.2f\n", user.money);
						strcpy(user.temp, floatToTxt(user.money, 0));
						
						arch = fopen(user.direct, "w");
						fprintf(arch, user.temp);
						fclose(arch);
						
						printf("\tDinero retirado exitosamente!!\n");						
					} else printf("\tNo puedes depositar cantidades negativas!!\n\a");
				} else printf("\tNo estas logeado a alguna cuenta!\n\a");
				break;
			
			case 8: //Consultar saldo
				if(user.login) {
					strcpy(user.direct, user.actual);
					strcat(user.direct, "\\capital.txt");
					user.money = 0;
					for(i = 0; i < 3; i++) { user.money += txtToFloat(user.direct, i)*pow(10, -i); }
					
					printf("\tSaldo actual: %.2f\n", user.money);					
				} else printf("\tNo estas logeado a alguna cuenta!\n\a");
				break;
			
			default:
				printf("\tSi necesitas ayuda, escribe \"help\"\n");
		}
		//printf("\n");
	}

	return 0;
}


//Pendiente revisar el correcto funcionamiento del floatToTxt();
