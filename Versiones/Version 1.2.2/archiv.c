#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <time.h>

char createDirect(char carpet[], char archiv_[], int iter) {
	char direct[1000] = "";
	strcat(direct, carpet);
	direct[strlen(direct)] = '\\';
	strcat(direct, archiv_);
	
	return direct[iter];
}

bool existFolder(char folderName[]) {
	FILE *arch;
	char directArch[1000] = "";
	
	strcat(directArch, folderName);
	directArch[strlen(directArch)] = '\\';
	strcat(directArch, folderName);
	strcat(directArch, ".txt");
	
	arch = fopen(directArch, "r");
	return arch == NULL ? false : true;
	fclose(arch);
}

int createFolder(char folderName[]) {
	FILE *arch;
	char comand[1000] = "@echo off\nMD ", directArch[1000] = "";
	int returned = 0;

	//Creación del folder
	strcat(comand, folderName);
	arch = fopen("comandSystem.bat", "w");
	fprintf(arch, comand);
	fclose(arch);
	
	system("comandSystem.bat");
	
	//Creación del archivo de existencia
	//"Sak2024\Sak2024.txt" Ejemplo
	strcat(directArch, folderName);
	directArch[strlen(directArch)] = '\\';
	strcat(directArch, folderName);
	strcat(directArch, ".txt");
	
	//printf("\tDirectorio: %s\n", directArch);
	
	arch = fopen(directArch, "w");
	fprintf(arch, folderName);
	fclose(arch);
	//Comprobación de la creación del folder (debug)
	//printf("\tFolder \"%s\" creado con exito!\n", folderName);

	//printf("\tEl usuario \"%s\" ya existe!\n", folderName);
	return returned;
}

void createUserArhivs(char user[]) {
	FILE *arch; int i, j, limitS;
	char comandS[1000] = "";
	char directArch[1000] = "", txtPoint[4] = ".txt", batPoint[4] = ".bat";
	
	char comand[5][1000] = {
		"", "", "", "", ""
	};
	char archivs[5][1000] = {
		"capital.txt",
		"deuda1.txt",
		"deuda2.txt",
		"deuda3.txt",
		"password.txt"
	};
	
	strcat(comandS, user);
	comandS[strlen(comandS)] = '\\';
	
	for(i = 0; i < 5; i++) {
		strcat(comand[i], comandS);
		strcat(comand[i], archivs[i]);
		
		arch = fopen(comand[i], "w");
		fprintf(arch, "0.0");
		fclose(arch);
		//printf("\t%s\n", comand[i]);
	}
}

void createPassword(char user[], char password[]) {
	FILE *arch;
	char direct[100] = "", temp[100], actualPassword[100]; int i;
	if(existFolder(user)) {
		for(i = 0; i < strlen(user) +1 +strlen("password.txt"); i++) direct[i] = createDirect(user, "password.txt", i);
		arch = fopen(direct, "w");
		fprintf(arch, password);
		fclose(arch);
		printf("\tPassword creada con exito!\n");
	} else printf("\tEl usuario no existe!\n");
}

void changePassword(char user[], char password[]) {
	FILE *arch;
	char direct[100] = "", temp[100], actualPassword[100]; int i;
	for(i = 0; i < strlen(user) +1 +strlen("password.txt"); i++) direct[i] = createDirect(user, "password.txt", i);
	//printf("%s", direct);
	
	arch = fopen(direct, "r");
	fgets(actualPassword, 100, arch);
	//printf("\t%s\n", actualPassword);
	if(strcmp(actualPassword, password) == 0) {
		printf("\tHola %s, dame tu nueva password: ", user);
		scanf("%s", temp);
		
		fclose(arch);
		arch = fopen(direct, "w");
		fprintf(arch, temp);
		fclose(arch);
		printf("\tPassword cambiada a \"%s\"!\n", temp);
	} else printf("\tNo podemos verificar que seas \"%s\"!\n", user);
}

bool loginUser(char *user, char *password) {
	FILE *arch;
	char direct[100] = "", temp[100], actualPassword[100];
	bool returned = true;
	
	strcpy(direct, user);
	strcat(direct, "\\password.txt");
	
	arch = fopen(direct, "r");
	fgets(actualPassword, 100, arch);
	fclose(arch);
	
	if(strcmp(actualPassword, password) != 0) returned = !returned;
	return returned;
}
