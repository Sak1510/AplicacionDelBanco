//Version 1.1.0 (temp)
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
				printf("Haz salido del banco!\n");
				loop = !loop;
				break;
				
			case 1:
				printf("Haz loggeado!\n\n");
				break;
			
			case 2:
				printf("Haz deslogeado!\n\n");
					break;
					
			case 3:
				printf("\tDame el nombre del usuario: ");
				scanf("%s", &subUserComand);
				createFolder(subUserComand);
				break;
				
			case 4:
				help();
				break;
				
			default:
				printf("Si necesitas ayuda, escribe \"help\" \n\n");
		}
	}

	system("PAUSE");
	return 0;
}
