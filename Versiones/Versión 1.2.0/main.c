//Version 1.2.0
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int arcg, char *argv[]) {
	printf("Bienvenido al banco del papu Sak!\n");
	bool loop = true, login = false;
	char actualUser[100] = "", directUser[100] = "";
	int i;
	float money;
	
	while(loop) {
		char userComand[100] = "", subUserComand[100];
		scanf("%s", &userComand);

		int opc = mainComandInt(userComand);
		switch(opc) {
			case 0: //Salir del banco
				printf("Haz salido del banco!\n");
				loop = !loop;
				break;
				
			case 1: //Logearse a una cuenta
				if(!login) {
					printf("\tDame el usuario al que te vas a loggear: ");
					scanf("%s", &userComand);
				
					if(existFolder(userComand)) {
						printf("\tDame el password del usuario %s: ", userComand);
						scanf("%s", &subUserComand);
						
						if(loginUser(userComand, subUserComand)) {
							strcpy(actualUser, userComand);
							//printf("\t%s\n", actualUser);
							printf("\tHaz logeado a %s!\n", actualUser);
							login = true;
							
							strcat(directUser, actualUser);
							directUser[strlen(directUser)] = '\\';
						} else printf("\tEl password de %s no es correcta\n", userComand);
					} else printf("\tEl usuario \"%s\" no existe!\n", userComand);
				} else printf("\tYa estas logeado en %s!\n", actualUser);
				break;
			
			case 2: //Deslogearse de una cuenta
				if(login) {
					printf("\tHaz salido de \"%s\"!\n", actualUser);
					
					strcpy(actualUser, "");
					strcpy(directUser, "");
					
					login = false;
				} else printf("\tNo estas logeado en algun usuario!\n");
				break;
					
			case 3: //Crear nuevo usuario
				printf("\tDame el nombre del usuario: ");
				scanf("%s", &userComand);
				if(!existFolder(userComand)) {
					createFolder(userComand);
					
					printf("\tCrea su password: ");
					scanf("%s", &subUserComand);
					
					createUserArhivs(userComand);
					createPassword(userComand, subUserComand);
				} else printf("\tEl usuario %s ya existe!\n", userComand);
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
				} else printf("\tEl usuario \"%s\" no existe.\n", userComand);
				break;
				
			case 6: //Depositar dinero a la cuenta
				if(login) {
					printf("\tCuanto dinero depositaras a la cuenta? ");
					scanf("%f", &money);
					
					strcat(directUser, "capital.txt");
					addSaldo(directUser, money);
					
					strcpy(directUser, "");
					strcat(directUser, actualUser);
					directUser[strlen(directUser)] = '\\';
				} else printf("\tNo estas logeado a alguna cuenta!");
				
				break;
				
			case 7: //Retirar dinero de la cuenta
				if(login) {
					printf("\tCuanto dinero retiraras de la cuenta? ");
					scanf("%f", &money);
					printf("\t%.2f\n", money);
					
					
				} else printf("\tNo estas logeado a alguna cuenta!");
				break;
				
			case 8: //Consultar saldo
				
				break;
				
			default:
				printf("\tSi necesitas ayuda, escribe \"help\"\n");
		}
		
		printf("\n");
	}

	system("PAUSE");
	return 0;
}
