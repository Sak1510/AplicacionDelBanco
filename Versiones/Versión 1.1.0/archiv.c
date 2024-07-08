#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

int createFolder(char folderName[]) {
	FILE *arch;
	char comand[100] = "@echo off\nMD ";
	
	int i;
	for(i = 0; i < strlen(folderName); i++) {
		comand[strlen(comand)] += folderName[i];
	}
	
	arch = fopen("comandSystem.bat", "w");
	fprintf(arch, comand);
	fclose(arch);

	system("comandSystem.bat");
	printf("\tUsuario %s creado con exito!\n", folderName);
	return 0;
}
