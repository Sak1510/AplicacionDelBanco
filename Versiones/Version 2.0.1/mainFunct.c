#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>

//Sin distincion
void Exit(int mode) {
	FILE *arch;
	char exit_[3][30] = {
		" \tHaz salido del banco!\n",
		" \tGracias por escogernos!!\n",
		" \tSaliendo"
	};
	
	int i;
	
	for(i = 1; i < 4; i++) printfSleep(exit_[i], 10, 500, "");
	for(i = 0; i < 3; i++) {
		printf(". ");
		Sleep(1000);
	} Sleep(500);
	
	if(mode == 1) {
		arch = fopen("data\\config\\startMode.txt", "w");
		fprintf(arch, "0");
		fclose(arch);
	}
}

void changeConfigBool(void *archiv) {
	FILE *arch;
	char D[2], direct[100] = "data\\config\\";
	strcat(direct, archiv);
	
	arch = fopen(direct, "r");
	if(arch != NULL) {
		fgets(D, 2, arch);
		fclose(arch);
		
		arch = fopen(direct, "w");
		
		if(D[0] == '0') fprintf(arch, "1");
		else fprintf(arch, "0");
	} else printf("\tAh sucedido un error!\n");
	
	fclose(arch);
}

//Primera ejecucion del programa
void createUser() {
	FILE *arch;
	char comand[100] = "@echo off\ncd data\ncd users\nMD ", direct[100] = "data\\users\\", message[100] = "Este folder si existe\nUsuario: ";
	char password[100] = "", user[100] = "";
	
	printfSleep(" \tDame el nombre del usuario: ", 10, 100, "");
	scanf("%s", &user);
	
	if(!existUser(user)) {
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

bool login() {
	FILE *arch;
	char user[100] = "", password[100] = "";
	int i;
	
	printfSleep(" \tDame el usuario al que te vas a loggear: ", 10, 100, "");
	scanf("%s", &user);

	if(existUser(user)) {
		printfSleep(" \tDame el password del usuario &: ", 10, 100, user);
		scanf("%s", &password);
		
		if(loginUser(user, password)) {
			printfSleep(" \tHaz logeado a &!\n", 10, 100, user);
			
			arch = fopen("data\\config\\startMode.txt", "w");
			fprintf(arch, "1");
			fclose(arch);
			
			arch = fopen("data\\config\\actualUser.txt", "w");
			fprintf(arch, user);
			fclose(arch);
			
			arch = fopen("data\\comandSystem.bat", "w");
			fprintf(arch, "@echo off \nstart AplicacionDelBanco.exe");
			fclose(arch);
			
			printfSleep(" \tEl ejecutable se cerrara en unos segundos para poder loggearse en el usuario actual\n", 10, 100, "");
			printfSleep(" \tLoggeando", 10, 100, "");
			for(i = 0; i < 3; i++) {
				printf(". ");
				Sleep(1000);
			}
			
			system("data\\comandSystem.bat");
			return true;
		} else {
			printfSleep(" \tEl password de \"&\" no es correcta\n\a", 10, 100, user);
			return false;
		}
	} else {
		printfSleep(" \tEl usuario \"&\" no existe!\n\a", 10, 100, user);
		return false;
	}
}

//Segunda ejecucion
void logout() {
	FILE *arch;
	char user[100] = "";
	int i;
	
	strcpy(user, getActualUser());
	
	printfSleep( " \tHaz salido de \"&\"!\n", 10, 100, user);
	arch = fopen("data\\config\\actualUser.txt", "w");
	fprintf(arch, "nobody");
	fclose(arch);
	
	printfSleep(" \tVolveras a la pagina de inicio en unos segundos!\n\tSaliendo", 10, 100, "");
	for(i = 0; i < 3; i++) {
		printf(". ");
		Sleep(1000);
	}
	
	arch = fopen("data\\config\\startMode.txt", "w");
	fprintf(arch, "0");
	fclose(arch);
	
	arch = fopen("data\\comandSystem.bat", "w");
	fprintf(arch, "@echo off\n start AplicacionDelBanco.exe");
	fclose(arch);
	
	system("data\\comandSystem.bat");
}

void changePassword() {
	FILE *arch;
	int i;
	char passDir[100] = "data\\users\\", newPass[100] = "", user[100] = "", password[100] = "";
	strcpy(user, getActualUser());
	
	printfSleep(" \tDame la contraseña del usuario: ", 10, 100, "");
	scanf("%s", &password);
	
	if(loginUser(user, password)) {
		printfSleep(" \tDame la nueva contraseña para \"&\": ", 10, 100, user);
		scanf("%s", &newPass);
		
		strcat(passDir, user);
		strcat(passDir, "\\password.txt");
		
		arch = fopen(passDir, "w");
		fprintf(arch, newPass);
		fclose(arch);
		
		printfSleep(" \tSe ah cambiado la contraseña de &\n", 10, 100, user);
		
		arch = fopen("data\\config\\startMode.txt", "w");
		fprintf(arch, "0");
		fclose(arch);
		
		arch = fopen("data\\comandSystem.bat", "w");
		fprintf(arch, "@echo off\n start AplicacionDelBanco.exe");
		fclose(arch);
		
		arch = fopen("data\\config\\actualUser.txt", "w");
		fprintf(arch, "nobody");
		fclose(arch);
		
		printfSleep(" \tVolveras a la pagina de inicio en unos segundos!\n\tDeberas volverte a loggear a tu usuario con la nueva contraseña!\n", 10, 100, "");
		printfSleep(" \tSaliendo", 10, 100, "");
		for(i = 0; i < 3; i++) {
			printf(". ");
			Sleep(1000);
		}
		
		system("data\\comandSystem.bat");
	} else printfSleep(" \tLa contraseña esta mal!\n", 10, 100, "");
}

void deposit() {
	FILE *arch;
	char direct[100] = "data\\users\\", temp[100];
	float money, moneyTemp;
	
	strcat(direct, getActualUser());
	strcat(direct, "\\capital.txt");
	
	arch = fopen(direct, "r");
	fgets(temp, 100, arch);
	fclose(arch);
	
	money = atof(temp);
	printfSleep(" \tSaldo actual: &\n", 10, 100, temp);
	
	printfSleep(" \tCuanto dinero vas a depositar? ", 10, 100, "");
	scanf("%f", &moneyTemp);
	
	if(moneyTemp >= 0) {
		money += moneyTemp;
		snprintf(temp, sizeof(temp), "%.2f", money);
		
		arch = fopen(direct, "w");
		fprintf(arch, temp);
		fclose(arch);
		
		printfSleep(" \tDinero depositado exitosamente!!\n", 10, 100, "");
	} else printfSleep(" \tNo puedes depositar cantidades negativas!!\n\a", 10, 100, "");
}

void remove_() {
	FILE *arch;
	char direct[1000] = "data\\users\\", temp[100];
	float money, moneyTemp;
	
	strcat(direct, getActualUser());
	strcat(direct, "\\capital.txt");
	//printf("\tdirect: %s\n", direct);
	
	arch = fopen(direct, "r");
	fgets(temp, 100, arch);
	fclose(arch);
	//printf("\ttemp: %s\n", temp);
	
	money = atof(temp);
	//printf("\tmoney: %.2f\n", money);
	
	printfSleep(" \tCuanto dinero vas a retirar? ", 10, 100, "");
	scanf("%f", &moneyTemp);
	
	if(moneyTemp >= 0) {
		if(money -moneyTemp > 0) {
			money -= moneyTemp;
			snprintf(temp, sizeof(temp), "%.2f\n", money);
			//printfSleep(" \tSaldo actual: &\n", 10, 100, temp);
			
			arch = fopen(direct, "w");
			fprintf(arch, temp);
			fclose(arch);
			
			printfSleep(" \tDinero retirado exitosamente!!\n", 10, 100, "");							
		} else printfSleep(" \tNo tienes el saldo suficiente!!\n\a", 10, 100, "");
	} else printfSleep(" \tNo puedes retirar cantidades negativas!!\n\a", 10, 100, "");	
}

void consult() {
	FILE *arch;
	char direct[100] = "data\\users\\", money[100];
	
	strcat(direct, getActualUser());
	strcat(direct, "\\capital.txt");
	arch = fopen(direct, "r");
	fgets(money, 100, arch);
	fclose(arch);
	
	printfSleep(" \tTu saldo actual es de $&\n", 10, 100, money);
}
