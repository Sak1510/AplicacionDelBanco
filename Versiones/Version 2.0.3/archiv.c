#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

void dataArchivs() {
	FILE *arch;
	char message[100] = "";
	
	//Creacion de la carpeta data
	arch = fopen("data\\dataExist.txt", "r");
	if(arch == NULL) {
		arch = fopen("comandSystem.bat", "w");
		fprintf(arch, "@echo off\nMD data");
		fclose(arch);
		
		system("comandSystem.bat");
		
		strcpy(message, "FOLDER \"DATA\" CREATED ON ");
		strcat(message, fechaActual());
		
		arch = fopen("data\\dataExist.txt", "w");
		fprintf(arch, message);
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
		
		strcpy(message, "FOLDER \"USERS\" CREATED ON ");
		strcat(message, fechaActual());
		
		arch = fopen("data\\users\\usersExist.txt", "w");
		fprintf(arch, message);
		fclose(arch);
	}
	
	//Subcarpeta data\config
	arch = fopen("data\\config\\configExist.txt", "r");
	if(arch == NULL) {
		arch = fopen("data\\comandSystem.bat", "w");
		fprintf(arch, "@echo off\ncd data\nMD config");
		fclose(arch);
		
		system("data\\comandSystem.bat");

		strcpy(message, "FOLDER \"CONFIG\" CREATED ON ");
		strcat(message, fechaActual());
		
		arch = fopen("data\\config\\configExist.txt", "w");
		fprintf(arch, message);
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
	char archivs[10][1000] = {"capital.txt", "loginHistorial.txt", "transtationsHistorial.txt"};
	char dataArc[10][1000] = {"0.0", "", ""};
	
	char direct[1000] = "data\\users\\", archiv[1000];
	int i;
	FILE *arch;
	
	strcat(direct, user);
	direct[strlen(direct)] = '\\';
	for(i = 0; i < 3; i++) {
		strcpy(archiv, direct);
		strcat(archiv, archivs[i]);
		
		arch = fopen(archiv, "w");
		fprintf(arch, dataArc[i]);
		fclose(arch);
}}

bool loginUser(char *user, char password[]) {
	FILE *arch;
	char passwordR[100] = "", direct[1000] = "data\\users\\";
	
	strcat(direct, user);
	strcat(direct, "\\password.txt");
	
	arch = fopen(direct, "r");
	fgets(passwordR, 100, arch);
	fclose(arch);
	
	int N = strcmp(passwordR, password);
	printf("\t%d\n", N);
	return N == 0;
}

char *getActualUser() {
	FILE *arch;
	char user[100] = "";
	
	arch = fopen("data\\config\\actualUser.txt", "r");
	fgets(user, 100, arch);
	fclose(arch);
	
	return user;
}
