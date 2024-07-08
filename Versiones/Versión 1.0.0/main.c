#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
	printf("Bienvenvenido al banco de SakMoneyMoney");
	float saldo;
	int opc = -1;
	while(opc != 0) {
		printf("\nDime que hacer: ");
		scanf("%d", &opc);
		switch(opc) {
			case 0:
				printf("Haz salido del banco! Gracias por tener tu dinero con nosotros :]\n");
				break;
			
			case 1:
				printf("Acciones del banco:\n 0) Salir del banco\n 1) Ayuda\n 2) Consultar saldo\n 3) Depositar dinero\n 4) Retirar dinero\n");
				break;
			
			case 2:
				printf("Tienes $%0.2f pesos\n", saldo);
				break;
				
 			case 3:
 				printf("Para depositar dinero, dame la cantidad a depositar: $");
 				float dep; scanf("%f", &dep);
 				if(dep > 0) {
	  				saldo += dep;
	 				printf("Deposito exitoso! Se han depositado $%0.2f pesos\n", dep);					
				} else printf("No puedes depositar cantitades negativas!\n");

 				break;
 				
 			case 4:
 				printf("Para retirar el dinero, dime cuanto vas a retirar: $");
 				float ret; scanf("%f", &ret);
 				if(saldo >= ret) {
 					if(ret > 0) {
	 					saldo -= ret;
 						printf("Retiro exitoso! Se han retirado $%0.2f\n", ret);
					} else printf("No puedes retirar cantidades negativas!\n");
				} else printf("Saldo insuficiente. Asegurate de tener la suficiente capital para retirar!\n");
 				break;
			
			default:
				printf("Opcion no conocida. Escribe '1' para obtener ayuda\n");
		}
	}
	
	system("PAUSE");
	return 0;
}

//Madres creo que la cague y no se que hice xddd x2
