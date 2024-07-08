#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <math.h>

int mainComandInt(char userComand[]) {
	//Siempre cambiar el tamaño del array y size cada vez que se vaya a agregar un nuevo comando
	int size = 9;
	char comands[9][15] = {
		"exit",
		"login", 
		"logout", 
		"createuser",
		"help",
		"changepassword",
		"deposit",
		"remove",
		"consult"
	};
	
	int i, j = 0, sum = 0, returned;
	bool loop = true;
	while(loop && j < size) {
		for(i = 0; i < strlen(comands[j]); i++) {
			if(userComand[i] == comands[j][i]) sum++;
		}
		
		if(sum == strlen(comands[j])) loop = false;
		else { j++; sum = 0; }
	}
	
	if(!loop) returned = j;
	else returned = -1;
	
	return returned;
}

int help() {
	printf("\tlogin\t\t-> Acceder a un usuario\n");
	printf("\tlogout\t\t-> Salir de un usuario\n");
	printf("\tcreateuser\t-> Crear un nuevo usuario\n");
	printf("\tchangepassword\t-> Cambiar la password de un usuario\n\n");
	
	printf("\tconsult\t\t-> Consultar saldo actual\n");
	printf("\tdeposit\t\t-> Depositar dinero a la cuenta\n");
	printf("\tremove\t\t-> Retirar dinero de la cuenta\n");
	
	printf("\texit\t\t-> Salir del banco\n");
	return 0;
}

int txtToFloat(char directArch[], int mode) {
	FILE *arch;
	float floatNum = 0;
	arch = fopen(directArch, "r");
	if(arch != NULL) {
		char floatStr[1000];
		fgets(floatStr, 1000, arch);			
		fclose(arch);
		
		float temp, neg = +1, estb = 0;
		int i, j, limitI = strlen(floatStr), pointUbc;
		
		for(i = 0; i < limitI; i++) { //Identifica la ubicación del punto decimal
			if(floatStr[i] == (int)'.') {
				pointUbc = i;
				i = limitI;
		}}
		
		if(floatStr[0] == (int)'-') {
			neg = -1;
			estb = 1;
		}
		
		j = 0;
		for(i = pointUbc -1; i > -1 +estb; i--) { //Suma los numeros enteros
			temp = floatStr[i] -'0';
			floatNum += temp*pow(10, j);
			j++;
		}
		
		j = -1;
		for(i = pointUbc +1; i < limitI; i++) { //Suma los numeros decimales
			temp = floatStr[i] -'0';
			floatNum += temp*pow(10, j);
			j--;
		} 
		
		if(floatNum > 0) {
			switch(mode) {
				case 1:
					floatNum = 10*(floatNum -floor(floatNum));
					break;
					
				case 2:
					floatNum = 10*(floatNum -floor(floatNum));
					floatNum = 10*(floatNum -floor(floatNum));
					break;
					
				default:
					floatNum = floatNum;
		}} else {
			switch(mode) {
				case 1:
					floatNum = 10*(floatNum -ceil(floatNum));
					break;
					
				case 2:
					floatNum = 10*(floatNum -ceil(floatNum));
					floatNum = 10*(floatNum -ceil(floatNum));
					break;
					
				default:
					floatNum = floatNum;
		}}
	floatNum *= neg;
	} else printf("\tError detectado: Archivo inexistente/faltante\n");
	return floatNum;
}

//Obtiene el tamaño que necesitara el array para almacenar el float en string
int sizeNum10(float num) {
	int i = 0, limitI;
	
	float temp = abs(num);
	//printf("\t %.2f\n\t %.2f\n", num, temp);
	while(temp > 0.9) {
		temp /= 10;
		i++;
	}
	
	if(num < 0) {
		i++;
	} return i +3;
}

//Funcion principal

char *floatToTxt(float floatNum, int iter) {
	int i = 0, limitI, j = 0, k = 0;
	float temp1 = abs(floatNum), temp2 = 0, temp3;
	char txtNum[100] = "";
	
	//Verifica si no es 0 o si el numero es negativo
	if(floatNum == 0) {
		txtNum[j] = (char)0 +'0';
		j++;
	} else if(floatNum < 0) {
		txtNum[j] = '-';
		j++;
	}
	
	//Revisa cuantos casillas de enteros tiene (10 -> 2, 100 -> 3, 1234 -> 4)
	while(temp1 > 0.9) {
		temp1 /= 10;
		
		i++;
	} limitI = i -1;
	
	//Convierte todos los enteros en char para despues almacenarlos en el array string
	temp1 = 0;
	for(i = limitI; i > -1; i--) {
		temp2 = temp1*10;	
		temp1 = floor(abs(floatNum)*pow(10, -i));
		temp3 = temp1 -temp2;
		
		txtNum[j] = (char)temp3 +'0';
		j++;
	} txtNum[j] = '.'; //Agrega el punto decimal
	
	temp3 = floatNum; //Para no modificar "floatNum"
	if(floatNum < 0) { //Metodo para convertir los decimales en char cuando es negativo
		temp1 = floor((1 -(temp3 -floor(temp3)))*10);
		txtNum[strlen(txtNum)] = (char)temp1 +'0';
		
		temp2 = ceil(((1 -(temp3 -floor(temp3)))*10 -floor((1 -(temp3 -floor(temp3)))*10))*10);
		txtNum[strlen(txtNum)] = (char)temp2 +'0';
	} else { //Y para cuando es negativo
		temp1 = floor((temp3 -floor(temp3))*10);
		txtNum[strlen(txtNum)] = (char)temp1 +'0';
		
		temp2 = ceil(((temp3 -floor(temp3))*10 -floor((temp3 -floor(temp3))*10))*10);
		txtNum[strlen(txtNum)] = (char)temp2 +'0';
	}
	
	//Regresa el index del array especificado (se recomienda usar un ciclo for())
	return txtNum;
}
