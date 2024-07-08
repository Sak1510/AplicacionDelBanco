#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool solicitudPrestamo(float sal, float prest) {
	return sal *3 > prest ? true : false;
}

void saldoActual(float saldo) { 
	printf("Tienes $%0.2f pesos\n", saldo);	
}

void ayuda() {
	printf("Acciones del banco:");
	printf("\n 0) Salir del banco");
	printf("\n 1) Ayuda");
	printf("\n 2) Consultar saldo");
	printf("\n 3) Depositar dinero");
	printf("\n 4) Retirar dinero");
	printf("\n 5) Pedir un prestamo");
	printf("\n 6) Ver deudas");
	printf("\n 7) Pagar deudas\n");
}

float depositoDeSaldo() {
	printf("Para depositar dinero, dame la cantidad a depositar: $");
	float deposito; scanf("%f", &deposito);
	
	if(deposito > 0) {
		printf("Deposito exitoso! Se han depositado $%0.2f pesos\n", deposito);	
		return deposito;				
	} else printf("No puedes depositar cantitades negativas!\n");
}

float retiroDeSaldo(float saldoUsuario) {
	printf("Para retirar el dinero, dime cuanto vas a retirar: $");
	float ret; scanf("%f", &ret);
	
	if(saldoUsuario >= ret) {
		if(ret >= 0) {
			printf("Retiro exitoso! Se han retirado $%0.2f\n", ret);
			return -ret;
		} else printf("No puedes retirar cantidades negativas!\n");
	} else printf("Saldo insuficiente. Asegurate de tener la suficiente capital para retirar!\n");	
}

float efectuarPrestamo(int numDeudas) {
	float returned = -1; 
	
	if(numDeudas < 4) {
		printf("Para pedir un prestamo, danos la cantidad que ganas al mes: $");
		float salario; scanf("%f", &salario);
		
		printf("Cuanto quisieras pedir prestado? $");
		float prestamo; scanf("%f", &prestamo);
		
		if(solicitudPrestamo(salario, prestamo)) {
			if(prestamo >= 0) {
				printf("Prestamo aceptado! El dinero ah sido añadido a tu cuenta\n");
				returned = prestamo;
			} else printf("No puedes pedir cantidades negativas!\n");
		} else printf("Prestamo no aceptado. Dudamos de tus capacidades para poder pagarnos, lo sentimos\n");
	} else printf("Limite de deudas superado! Asegurate de pagar todas tus deudas\n");
	
	return returned;
}

void deudasActuales(int numDeudas, float deudasAct[]) {
	printf("Actualmente tienes %d deudas\n", numDeudas);
	if(numDeudas >= 4) printf("Haz alcanzado el limite de deudas!\n");
	
	int i;
	for(i = 0; i < numDeudas; i++) {
		printf("Deuda No.%d: $%.2f\n", (i +1), deudasAct[i]);
	}
}

struct deudas {
	int numDeudas;
	float deudasAct[4];
};

int main(int argc, char *argv[]) {
	printf("Bienvenvenido al banco de SakMoneyMoney");
	float saldo;
	struct deudas usuario;
	usuario.numDeudas = 0;
	
	int i;
	for(i = 0; i < 4; i++) {
		usuario.deudasAct[i] = 0;
	}
	
	float deudaTemp;
	
	int opc = -1;
	while(opc != 0) {
		printf("\nDime que hacer: ");
		scanf("%d", &opc);
		
		switch(opc) {
			case 0: printf("Haz salido del banco! Gracias por tener tu dinero con nosotros :]\n"); break;		//Salir del banco
			case 1: ayuda(); break;  																			//Ayuda al usuario con las funciones
			case 2: saldoActual(saldo); break;																	//Saber cuanto saldo tienes	
 			case 3:	saldo += depositoDeSaldo(); break;															//Depositar dinero
 			case 4:	saldo += retiroDeSaldo(saldo); break;														//Retirar dinero
			 													
 			case 5:	//Pedir prestamo
 				deudaTemp = efectuarPrestamo(usuario.numDeudas);
 				if(deudaTemp > 0) {
				 	saldo += deudaTemp;
					
				 	usuario.deudasAct[usuario.numDeudas] = deudaTemp;
				 	usuario.numDeudas++;				
				}
				break;
													
 			case 6: //Solicitar deudas actuales
			 	deudasActuales(usuario.numDeudas, usuario.deudasAct); 
			 	break;
			 	
			case 7: //Pagar deudas
				printf("En construccion te vas a quedar endeudado kkkkk\n");
				break;
																			
			default: printf("Opcion no conocida. Escribe '1' para obtener ayuda\n"); 							//Opción no conocida
	}}
	
	system("PAUSE");
	return 0;
}

//Madres creo que la cague y no se que hice xddd x2
