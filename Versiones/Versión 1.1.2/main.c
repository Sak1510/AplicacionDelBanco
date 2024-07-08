//Version 1.1.2
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int arcg, char *argv[]) {
	printf("Bienvenido al banco del papu Sak!\n");
	
	bool loop = true, login = false;
	char actualUser[100] = "", directUser[100] = "";
	int i;
	
	while(loop) {
		char userComand[100] = "", subUserComand[100];
		scanf("%s", &userComand);

		int opc = mainComandInt(userComand);
		switch(opc) {
			case 0:
				printf("Haz salido del banco!\n");
				loop = !loop;
				break;
				
			case 1:
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
						} else printf("\tEl password de %s no es correcta\n", userComand);
					} else printf("\tEl usuario \"%s\" no existe!\n", userComand);
				} else printf("\tYa estas logeado en %s!\n", actualUser);
				break;
			
			case 2:
				if(login) {
					printf("\tHaz salido de \"%s\"!\n", actualUser);
					strcpy(actualUser, "");
					login = false;
				} else printf("\tNo estas logeado en algun usuario!\n");
				break;
					
			case 3:
				printf("\tDame el nombre del usuario: ");
				scanf("%s", &userComand);
				if(!existFolder(userComand)) {
					createFolder(userComand);
					printf("\tCrea su password: ");
					scanf("%s", &subUserComand);
					createPassword(userComand, subUserComand);
				} else printf("\tEl usuario %s ya existe!\n", userComand);
				break;
				
			case 4:
				help();
				break;
				
			case 5:
				printf("\tDame el usuario al que le vas a cambiar el password: ");
				scanf("%s", &userComand);
				if(existFolder(userComand)) {
					printf("\tDame la password actual: ");
					scanf("%s", &subUserComand);
					changePassword(userComand, subUserComand);
				} else printf("\tEl usuario \"%s\" no existe.\n", userComand);
				break;
				
			default:
				printf("\tSi necesitas ayuda, escribe \"help\"\n");
		}
		
		printf("\n");
	}

	system("PAUSE");
	return 0;
}
