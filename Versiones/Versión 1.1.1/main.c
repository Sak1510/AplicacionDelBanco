//Version 1.1.1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int arcg, char *argv[]) {
	printf("Bienvenido al banco del papu Sak!\n");
	
	bool loop = true;
	while(loop) {
		char userComand[15] = "", subUserComand[15];
		scanf("%s", &userComand);
		
		int opc = mainComandInt(userComand);
		switch(opc) {
			case 0:
				printf("\tHaz salido del banco!\n\n");
				loop = !loop;
				break;
				
			case 1:
				printf("\tDame el usuario al que te vas a loggear: ");
				scanf("%s", subUserComand);
				
				printf("\tHaz loggeado en %s\n\n", subUserComand);
				break;
			
			case 2:
				printf("\tHaz desloggeado en %s\n\n", subUserComand);
				break;
					
			case 3:
				printf("\tDame el nombre del usuario: ");
				scanf("%s", &userComand);
				createFolder(userComand);
				
				printf("\tCrea su password: ");
				scanf("%s", &subUserComand);
				
				if(createFolder(userComand) == 0) createPassword(userComand, subUserComand);
				break;
				
			case 4:
				help();
				break;
				
			case 5:
				printf("\tDame el usuario al que le vas a cambiar el password: ");
				scanf("%s", &userComand);
				printf("\tDame la password actual: ");
				scanf("%s", &subUserComand);
				changePassword(userComand, subUserComand);
				break;
				
			default:
				printf("Si necesitas ayuda, escribe \"help\" \n\n");
		}
	}

	system("PAUSE");
	return 0;
}
