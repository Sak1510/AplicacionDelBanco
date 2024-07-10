#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

char *fechaActual() {
	//Codigo origina:
	//https://parzibyte.me/blog/2019/07/31/c-obtener-formatear-fecha-actual/
	
	time_t t = time(NULL);
	struct tm tiempoLocal = *localtime(&t);
	char fechaHora[70];
	char *formato = "%d-%m-%Y %H:%M"; // %H:%M:%S
	int bytesEscritos = strftime(fechaHora, sizeof fechaHora, formato, &tiempoLocal);
	
	if (bytesEscritos != 0) {
		return fechaHora;
	} else {
		return '0';
	}
}

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
	int i; char temp[100] = " \n\nIniciado el dia ";
	
	printfSleep(" Iniciando", 10, 500, ""); //Iniciando
	for(i = 0; i < 3; i++) { printf(". "); Sleep(500); }
	
	printfSleep(" \nCargando base de datos", 10, 500, ""); //Cargando base de datos
	for(i = 0; i < 3; i++) { printf(". "); Sleep(500); }
	
	printfSleep(" \nComprobando", 10, 500, ""); //Comprobando
	for(i = 0; i < 3; i++) { printf(". "); Sleep(500); }
		
	int numRand = rand()%7;
	if(numRand == 0) {
		printfSleep(" \n\nERROR\nCorrigiendo", 10, 500, ""); //ERROR\nCorrigiendo"
		for(i = 0; i < 3; i++) { printf(". "); Sleep(500); } printf("\n");
	} Sleep(3000);
	
	strcat(temp, fechaActual());
	printfSleep(temp, 10, 100, "");
	printfSleep(" \nBienvenido al banco del PapuSak! Hoy dia que vamos a hacer?\n", 10, 0, ""); //Bienvenido!
	//mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -WHEEL_DELTA, 0);
}

void help(int mode) {
	char helpA[2][8][1000] = {{
		" \tlogin\t\t-> Acceder a un usuario\n",
		" \tcreateUser\t-> Crear un nuevo usuario\n\n",
		
		" \texit\t\t-> Salir del banco\n",
		" \tfullScreen\t-> Cambia el modo de pantalla completa\n",
		//" \tshowDataFolder\t-> Muestra la carpeta \"data\"\n"
	}, {
		" \tlogout\t\t\t-> Salir del usuario actual\n",
		" \tchangePassword\t\t-> Cambiar la contraseña del usuario actual\n",
		" \tconsult\t\t\t-> Consultar saldo actual\n",
		" \tdeposit\t\t\t-> Depositar dinero a la cuenta\n",
		" \tremove\t\t\t-> Retirar dinero de la cuenta\n",
		" \tshowLoginHistorial\t-> Muestra los inicios de sesión hasta la fecha actual\n\n"
		
		" \texit\t\t\t-> Salir del banco\n",
		" \tfullScreen\t\t-> Cambia el modo de pantalla completa\n",
		//" \tshowDataFolder\t-> Muestra la carpeta \"data\"\n"
	}}; int i;
	for(i = 0; i < 8; i++) printfSleep(helpA[mode][i], 10, 0, "");
}

void AltEnter() { 
	//Codigo obtenido de: 
	//https://www.programacionenc.net/index.php?option=com_content&view=article&id=134:ejecutar-un-programa-de-consola-a-pantalla-completa&catid=31:general&Itemid=41
	
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

void sizeLetter(int mode) {
	int i, neg = 1;
	if(mode == 1) neg = -1;
	
	Sleep(500);
	for(i = 0; i < 10; i++) {
		keybd_event(VK_CONTROL, 0, 0, 0);
		mouse_event(MOUSEEVENTF_WHEEL, 0, 0, neg*WHEEL_DELTA, 0);
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
}}
