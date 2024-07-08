#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

void dataArchivs() {
	FILE *arch;
	
	//Creacion de la carpeta data
	arch = fopen("data\\dataExist.txt", "r");
	if(arch == NULL) {
		arch = fopen("comandSystem.bat", "w");
		fprintf(arch, "@echo off\nMD data");
		fclose(arch);
		
		system("comandSystem.bat");
		
		arch = fopen("data\\dataExist.txt", "w");
		fprintf(arch, "FOLDER \"DATA\" CREATED");
		fclose(arch);
		
		//Creacion de las subcarpetas
		arch = fopen("data\\comandSystem.bat", "w");
		fprintf(arch, "@echo off\nDEL comandSystem.bat\nattrib +h +s \"data\"");
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
	}
	
	//Creacion de los archivos de data\config
	char archivs[10][20] = {"startMode.txt", "actualUser.txt", "fullScreen.txt", "showDataFolder.txt", "correctExit.txt"};
	char dataArc[10][10] = {"0", "nobody", "1", "0", "1"};
	char temp[100] = "";
	
	int i;
	for(i = 0; i < 5; i++) {
		strcpy(temp, "data\\config\\");
		strcat(temp, archivs[i]);
		//printf("%s\n", temp);
		
		arch = fopen(temp, "r");
		if(arch == NULL) {
			arch = fopen(temp, "w");
			fprintf(arch, dataArc[i]);
			fclose(arch);
	}}
}

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

char *getActualUser() {
	FILE *arch;
	char user[100] = "";
	
	arch = fopen("data\\config\\actualUser.txt", "r");
	fgets(user, 100, arch);
	fclose(arch);
	
	return user;
}
