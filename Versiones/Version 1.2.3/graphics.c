#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <time.h>

void printfSleep(char array[], int SleepC /*Sleep Corto*/, int SleepL /*Sleep Largo*/, char string[]) {
	int i, j, load;
	for(i = 0; i < strlen(array); i++) if(array[i] == '&') load = i;
	
	for(i = 0; i < strlen(array); i++) {
		if(i != load) printf("%c", array[i]);
		else for(j = 0; j < strlen(string); j++) printf("%c", string[j]);
		
		Sleep(SleepC);
	} Sleep(SleepL);
}

void printfStart() {
	char inicio[5][1000] = {
		" Iniciando",
		" \nCargando base de datos",
		" \nComprobando",
		" \n\nERROR\nCorrigiendo",
		" \nBienvenido al banco del PapuSak! Hoy dia que vamos a hacer?\n"
	}; int i;
	
	printfSleep(inicio[0], 10, 500, ""); //Iniciando
	for(i = 0; i < 5; i++) {
		printf(". ");
		Sleep(500);
	} Sleep(1000);
	
	printfSleep(inicio[1], 10, 500, ""); //Cargando base de datos
	for(i = 0; i < 5; i++) { 
		printf(". ");
		Sleep(500);
	} Sleep(1000);
	
	printfSleep(inicio[2], 10, 500, ""); //Comprobando
	for(i = 0; i < 5; i++) { 
		printf(". ");
		Sleep(500);
	} Sleep(1000);
		
	int numRand = rand()%70;
	if(numRand%7 == 0) {
		printfSleep(inicio[3], 10, 500, ""); //ERROR\nCorrigiendo"
		for(i = 0; i < 5; i++) { 
			printf(". ");
			Sleep(500);
		} printf("\n");
	} Sleep(3000);
	
	printfSleep(inicio[4], 10, 0, ""); //Bienvenido!
	mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -WHEEL_DELTA, 0);
}

void help() {
	char helpA[8][1000] = {
		"\tlogin\t\t-> Acceder a un usuario\n",
		"\tlogout\t\t-> Salir de un usuario\n",
		"\tcreateuser\t-> Crear un nuevo usuario\n",
		"\tchangepassword\t-> Cambiar la password de un usuario\n\n",
		
		"\tconsult\t\t-> Consultar saldo actual\n",
		"\tdeposit\t\t-> Depositar dinero a la cuenta\n",
		"\tremove\t\t-> Retirar dinero de la cuenta\n",
		
		"\texit\t\t-> Salir del banco\n"
	};
	
	int i;
	for(i = 0; i < 8; i++) printfSleep(helpA[i], 10, 0, "");
}

void AltEnter() { 
	//Codigo obtenido de: 
	//https://www.programacionenc.net/index.php?option=com_content&view=article&id=134:ejecutar-un-programa-de-consola-a-pantalla-completa&catid=31:general&Itemid=41
	
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

void sizeLetter() {
	int i;
	Sleep(100);
	for(i = 0; i < 25; i++) {
		keybd_event(VK_CONTROL, 0, 0, 0);
		mouse_event(MOUSEEVENTF_WHEEL, 0, 0, WHEEL_DELTA, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);	
}}
