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

bool existFolder(char *name) {
	FILE *arch;
	char direct[1000] = "data\\";
	
	strcat(direct, name);
	strcat(direct, "\\folderExist.txt");
	
	arch = fopen(direct, "r");
	return arch == NULL ? false : true;
	fclose(arch);
}

bool existUser(char *user) {
	FILE *arch;
	char direct[1000] = "data\\users\\";
	
	strcat(direct, user);
	strcat(direct, "\\folderExist.txt");
	
	arch = fopen(direct, "r");
	return arch == NULL ? false : true;
	fclose(arch);
}

void createPassword(char *user, char *password) {
	FILE *arch;
	char direct[1000] = "data\\users\\";
	
	strcat(direct, user);
	strcat(direct, "\\password.txt");
	arch = fopen(direct, "w");
	fprintf(arch, password);
	fclose(arch);
}

void createUserArhivs(char *user) {
	char archivs[2][1000] = {"capital.txt"};
	char direct[1000] = "data\\users\\", archiv[1000];
	int i;
	FILE *arch;
	
	strcat(direct, user);
	direct[strlen(direct)] = '\\';
	for(i = 0; i < 2; i++) {
		strcpy(archiv, direct);
		strcat(archiv, archivs[i]);
		
		arch = fopen(archiv, "w");
		fprintf(arch, "0.0");
		fclose(arch);
}}

void createUser(char *user) {
	FILE *arch;
	char comand[100] = "@echo off\ncd data\ncd users\nMD ", direct[100] = "data\\users\\", message[100] = "Este folder si existe\nUsuario: ";
	char password[100] = "";
	
	if(!existFolder(user)) {
		strcat(comand, user);
		arch = fopen("data\\comandSystem.bat", "w");
		fprintf(arch, comand);
		fclose(arch);
		
		system("data\\comandSystem.bat");
		
		strcat(direct, user);
		strcat(direct, "\\folderExist.txt");
		strcat(message, user);
		arch = fopen(direct, "w");
		fprintf(arch, message);
		fclose(arch);
		
		printfSleep(" \tCrea una contraseña: ", 10, 100, "");
		scanf("%s", &password);
		createPassword(user, password);
		
		createUserArhivs(user);
		
		printfSleep(" \tUsuario creado con exito!\n", 10, 100, "");
	} else printfSleep(" \tEl usuario \"&\" ya existe!\n", 10, 100, user);
}

bool loginUser(char *user, char *password) {
	FILE *arch;
	char passwordR[100] = "", direct[1000] = "data\\users\\";
	
	strcat(direct, user);
	strcat(direct, "\\password.txt");
	
	arch = fopen(direct, "r");
	fgets(passwordR, 100, arch);
	fclose(arch);
	
	return strcmp(passwordR, password) == 0 ? true : false;
}

void changePassword(char *user, char *password) {
	FILE *arch;
	char passDir[100] = "data\\users\\", newPass[100];
	if(loginUser(user, password)) {
		printfSleep(" \tDame la nueva contraseña para \"&\": ", 10, 100, user);
		scanf("%s", &newPass);
		
		strcat(passDir, user);
		strcat(passDir, "\\password.txt");
		
		arch = fopen(passDir, "w");
		fprintf(arch, newPass);
		fclose(arch);
		
		printfSleep(" \tSe ah cambiado la contraseña de &\n", 10, 100, user);
	} else printfSleep(" \tLa contraseña esta mal!\n", 10, 100, "");
}
