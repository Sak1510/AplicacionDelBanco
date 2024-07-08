#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <math.h>

char createDirect(char carpet[], char archiv_[], int iter) {
	char direct[1000] = "";
	strcat(direct, carpet);
	direct[strlen(direct)] = '\\';
	strcat(direct, archiv_);
	
	return direct[iter];
}

bool existFolder(char folderName[]) {
	FILE *arch;
	char directArch[1000] = "", txtPoint[4] = ".txt";
	
	strcat(directArch, folderName);
	directArch[strlen(directArch)] = '\\';
	strcat(directArch, folderName);
	strcat(directArch, txtPoint);
	
	arch = fopen(directArch, "r");
	return arch == NULL ? false : true;
}

int createFolder(char folderName[]) {
	FILE *arch;
	char comand[1000] = "@echo off\nMD ", directArch[1000] = "";
	int returned = 0;
	if(!existFolder(folderName)) {
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
	} else {
		printf("\tEl usuario \"%s\" ya existe!\n", folderName);
		returned = 1;
	}
	return returned;
}

int createUserArhivs(char user[]) {
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
		fclose(arch);
		//printf("\t%s\n", comand[i]);
	}
}

int createPassword(char user[], char password[]) {
	FILE *arch;
	char direct[100] = "", temp[100], actualPassword[100]; int i;
	if(existFolder(user)) {
		for(i = 0; i < strlen(user) +1 +strlen("password.txt"); i++) direct[i] = createDirect(user, "password.txt", i);
		arch = fopen(direct, "w");
		fprintf(arch, password);
		fclose(arch);
		printf("\tPassword creada con exito!");
	} else printf("\tEl usuario no existe!\n");
}

int changePassword(char user[], char password[]) {
	FILE *arch;
	char direct[100] = "", temp[100], actualPassword[100]; int i;
	for(i = 0; i < strlen(user) +1 +strlen("password.txt"); i++) direct[i] = createDirect(user, "password.txt", i);
	arch = fopen(direct, "r");
	if(arch == NULL) {
		fclose(arch);
		arch = fopen(direct, "w");
		fprintf(arch, password);
		fclose(arch);
		
		printf("\tPassword creada!\n");
	} else {
		arch = fopen(direct, "r");
		fgets(actualPassword, 100, arch);
		if(strcmp(actualPassword, temp) == 0) {
			printf("\tLas dos passwords son iguales!\n");
		} else printf("\tNo\n");
	}
	
	return 0;
}

float txtToFloat(char directArch[]) {
	FILE *arch;
	
	
	
	/*
	archivo = fopen("num.txt", "r");
	char string[1000];
	fgets(string, 1000, archivo);
	int stringL = strlen(string);
	
	printf("%s\n\n", string);
	
	int i, j = 0;
	float stringFloat, temp1, temp2;;
	
	for(i = stringL -1; i > -1; i--) {
		temp1 = string[i] -'0';
		
		
		if(temp1 < 10) {
			temp2 = temp1*pow(10, j);
			j++;
			
			stringFloat = stringFloat +temp2;
			//printf("%d, %d, %.2f\n", temp2, stringInt, (float)stringInt);
		}
	}
	
	printf("%.2f\n", stringFloat);
	//printf("Texto: %s\nEntero: %d\n", string, stringInt);
	fclose(archivo);
	*/
}
