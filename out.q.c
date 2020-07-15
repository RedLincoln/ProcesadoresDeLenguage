#include "Qlib.h"
#include "Q.h"

#define INI 0
BEGIN
L 8:
		R6=R7;		 # Nuevo marco
		R7=R7-0;		 # Reservamos espacio para variables locales
		R0 = 0; 		# Guardamos valor de constante numerica
		R0 = R0 * 4;		 # multiplicamos indice por bytes del tipo
		R1 = R6+16; 		 # Almacenamos dirección relativa de acceso de array
		R0 = R1+R0;
		R0 = P(R0);
		R1 = I(R6+8);		 # Copiamos valor en memoria relativa a registro;
		R2 = I(R6+12);		 # Copiamos valor en memoria relativa a registro;
		R1 = R1+R2;		 # Operaciones numericas
		I(R0) = R1;		 # Guardamos valor de registro en memoria
		R7=R6;		 # Liberamos memoria local
		R6=P(R7+4);		 # Recuperamos marco
		R0 = P(R7);		 # Recuperamos etiqueta de retorno
		GT(R0);
L 9:
		R6=R7;		 # Nuevo marco
		R7=R7-8;		 # Reservamos espacio para variables locales
		R0 = I(R6+8);		 # Copiamos valor en memoria relativa a registro;
		R1 = 0; 		# Guardamos valor de constante numerica
		R0 = R0 != R1;		 # Operaciones logicas
		IF (R0) GT(10);		 # condición revertida
		R1 = 0; 		# Guardamos valor de constante numerica
		R1 = R1 * 4;		 # multiplicamos indice por bytes del tipo
		R2 = R6+12; 		 # Almacenamos dirección relativa de acceso de array
		R1 = R2+R1;
		R1 = P(R1);
		R2 = 0; 		# Guardamos valor de constante numerica
		I(R1) = R2;		 # Guardamos valor de registro en memoria
L 10:
		R0 = I(R6+8);		 # Copiamos valor en memoria relativa a registro;
		R1 = 1; 		# Guardamos valor de constante numerica
		R0 = R0 != R1;		 # Operaciones logicas
		IF (R0) GT(11);		 # condición revertida
		R1 = 0; 		# Guardamos valor de constante numerica
		R1 = R1 * 4;		 # multiplicamos indice por bytes del tipo
		R2 = R6+12; 		 # Almacenamos dirección relativa de acceso de array
		R1 = R2+R1;
		R1 = P(R1);
		R2 = 1; 		# Guardamos valor de constante numerica
		I(R1) = R2;		 # Guardamos valor de registro en memoria
L 11:
		R0 = I(R6+8);		 # Copiamos valor en memoria relativa a registro;
		R1 = 1; 		# Guardamos valor de constante numerica
		R0 = R0 <= R1;		 # Operaciones logicas
		IF (R0) GT(12);		 # condición revertida
		R7 = R7 - 0;		 # Reservamos memoria para cambio de contexto
		R0 = R6-4;		 # Almacenamos dirección relativo de acceso de array
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R0 = I(R6+8);		 # Copiamos valor en memoria relativa a registro;
		R1 = 1; 		# Guardamos valor de constante numerica
		R0 = R0-R1;		 # Operaciones numericas
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R7 = R7-8;
		P(R7+4) = R6;		 # Salvamos marco actual
		P(R7) = 13;		 # Almacenamos etiqueta de retorno
		GT(9);
L 13:
		R7 = R7+16;
		R7 = R7 + 0;		 # Volvemos al estado anterior al cambio de contexto
		R7 = R7 - 0;		 # Reservamos memoria para cambio de contexto
		R0 = R6-8;		 # Almacenamos dirección relativo de acceso de array
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R0 = I(R6+8);		 # Copiamos valor en memoria relativa a registro;
		R1 = 2; 		# Guardamos valor de constante numerica
		R0 = R0-R1;		 # Operaciones numericas
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R7 = R7-8;
		P(R7+4) = R6;		 # Salvamos marco actual
		P(R7) = 14;		 # Almacenamos etiqueta de retorno
		GT(9);
L 14:
		R7 = R7+16;
		R7 = R7 + 0;		 # Volvemos al estado anterior al cambio de contexto
		R0 = 0; 		# Guardamos valor de constante numerica
		R0 = R0 * 4;		 # multiplicamos indice por bytes del tipo
		R1 = R6+12; 		 # Almacenamos dirección relativa de acceso de array
		R0 = R1+R0;
		R0 = P(R0);
		R1 = 0; 		# Guardamos valor de constante numerica
		R1 = R1 * 4;		 # multiplicamos indice por bytes del tipo
		R2 = R6-4; 		 # Almacenamos dirección relativa de acceso de array
		R1 = R2+R1;
		R1 = I(R1);		 # Almacenamos valor de array (addr. relativo)
		R2 = 0; 		# Guardamos valor de constante numerica
		R2 = R2 * 4;		 # multiplicamos indice por bytes del tipo
		R3 = R6-8; 		 # Almacenamos dirección relativa de acceso de array
		R2 = R3+R2;
		R2 = I(R2);		 # Almacenamos valor de array (addr. relativo)
		R1 = R1+R2;		 # Operaciones numericas
		I(R0) = R1;		 # Guardamos valor de registro en memoria
L 12:
		R7=R6;		 # Liberamos memoria local
		R6=P(R7+4);		 # Recuperamos marco
		R0 = P(R7);		 # Recuperamos etiqueta de retorno
		GT(R0);
L 0:
	STAT(0)
		MEM(0x11ff8, 8);		 # Reservamos en memoria estática para variable primitiva
		MEM(0x11ff4, 4);		 # Reservamos en memoria estática para variable primitiva
		MEM(0x11ff0, 4);		 # Reservamos en memoria estática para variable primitiva
		FIL(0x11fc8, 40, 0);		 # Reservamos espacio para array
		FIL(0x11fb4, 20, 0);		 # Reservamos espacio para array
	CODE(0)
		R0 = 0x11ff8; 		 # Almacenamos dirección en registro
		RR0 = 2.200000; 		# Guardamos valor de constante numerica
		D(R0) = RR0;		 # Guardamos valor de registro en memoria
		R0 = 0x11ff4; 		 # Almacenamos dirección en registro
		RR0 = D(0x11ff8);		 # Copiamos valor en memoria a registro
		I(R0) = RR0;		 # Guardamos valor de registro en memoria
		R0 = 0x11ff0; 		 # Almacenamos dirección en registro
		RR0 = D(0x11ff8);		 # Copiamos valor en memoria a registro
		R1 = I(0x11ff4);		 # Copiamos valor en memoria a registro
		RR0 = RR0+R1;		 # Operaciones numericas
		I(R0) = RR0;		 # Guardamos valor de registro en memoria
		R0 = 3; 		# Guardamos valor de constante numerica
		R0 = R0 * 4;		 # multiplicamos indice por bytes del tipo
		R0 = 0x11fb4+R0;		 # Almacenamos dirección de acceso de array
		R1 = 10; 		# Guardamos valor de constante numerica
		I(R0) = R1;		 # Guardamos valor de registro en memoria
		R0 = 0x11fc8;		 # Almacenamos dirección de acceso de array
		R1 = 0x11fb4;		 # Almacenamos dirección de acceso de array
		R2 = I(R1+0);
		I(R0+0) = R2;
		R2 = I(R1+4);
		I(R0+4) = R2;
		R2 = I(R1+8);
		I(R0+8) = R2;
		R2 = I(R1+12);
		I(R0+12) = R2;
		R2 = I(R1+16);
		I(R0+16) = R2;
		R0 = I(0x11ff0);		 # Copiamos valor en memoria a registro
		R1 = 4; 		# Guardamos valor de constante numerica
		R0 = R0 <= R1;		 # Operaciones logicas
		IF (R0) GT(1);		 # condición revertida
		R0 = 1; 		# Guardamos valor de constante numerica
		R0 = R0 * 4;		 # multiplicamos indice por bytes del tipo
		R0 = 0x11fb4+R0;		 # Almacenamos dirección de acceso de array
		R1 = I(0x11ff0);		 # Copiamos valor en memoria a registro
		I(R0) = R1;		 # Guardamos valor de registro en memoria
		R0 = 2; 		# Guardamos valor de constante numerica
		R0 = R0 * 4;		 # multiplicamos indice por bytes del tipo
		R0 = 0x11fb4+R0;		 # Almacenamos dirección de acceso de array
		R2 = 3; 		# Guardamos valor de constante numerica
		R2 = R2 * 4;		 # multiplicamos indice por bytes del tipo
		R2 = I(0x11fc8+R2);		 # Almacenamos valor de array
		I(R0) = R2;		 # Guardamos valor de registro en memoria
		GT(2);
L 1:
		R0 = 1; 		# Guardamos valor de constante numerica
		R0 = R0 * 4;		 # multiplicamos indice por bytes del tipo
		R0 = 0x11fb4+R0;		 # Almacenamos dirección de acceso de array
		RR0 = D(0x11ff8);		 # Copiamos valor en memoria a registro
		I(R0) = RR0;		 # Guardamos valor de registro en memoria
		R0 = 2; 		# Guardamos valor de constante numerica
		R0 = R0 * 4;		 # multiplicamos indice por bytes del tipo
		R0 = 0x11fb4+R0;		 # Almacenamos dirección de acceso de array
		R1 = I(0x11ff0);		 # Copiamos valor en memoria a registro
		I(R0) = R1;		 # Guardamos valor de registro en memoria
L 2:
	STAT(1)
		MEM(0x11fb0, 4);		 # Reservamos en memoria estática para variable primitiva
	CODE(1)
		R0 = 0x11fb0; 		 # Almacenamos dirección en registro
		R1 = 0; 		# Guardamos valor de constante numerica
		I(R0) = R1;		 # Guardamos valor de registro en memoria
	STAT(2)
		MEM(0x11fac, 4);		 # Reservamos en memoria estática para variable primitiva
	CODE(2)
		R0 = 0x11fac; 		 # Almacenamos dirección en registro
		R1 = 0; 		# Guardamos valor de constante numerica
		I(R0) = R1;		 # Guardamos valor de registro en memoria
		R0 = 0; 		# Guardamos valor de constante numerica
		R0 = R0 * 4;		 # multiplicamos indice por bytes del tipo
		R0 = 0x11fb4+R0;		 # Almacenamos dirección de acceso de array
		R1 = I(0x11fb0);		 # Copiamos valor en memoria a registro
		R2 = I(0x11fac);		 # Copiamos valor en memoria a registro
		R1 = R1+R2;		 # Operaciones numericas
		I(R0) = R1;		 # Guardamos valor de registro en memoria
L 3:
		R0 = I(0x11fb0);		 # Copiamos valor en memoria a registro
		R1 = 10; 		# Guardamos valor de constante numerica
		R0 = R0 >= R1;		 # Operaciones logicas
		IF (R0) GT(4);		 # condición revertida
		R0 = I(0x11fb0);		 # Copiamos valor en memoria a registro
		R0 = R0 * 4;		 # multiplicamos indice por bytes del tipo
		R0 = 0x11fc8+R0;		 # Almacenamos dirección de acceso de array
		R1 = I(0x11fb0);		 # Copiamos valor en memoria a registro
		I(R0) = R1;		 # Guardamos valor de registro en memoria
		R0 = 0x11fb0; 		 # Almacenamos dirección en registro
		R1 = I(0x11fb0);		 # Copiamos valor en memoria a registro
		R2 = 1; 		# Guardamos valor de constante numerica
		R1 = R1+R2;		 # Operaciones numericas
		I(R0) = R1;		 # Guardamos valor de registro en memoria
L 5:
		R0 = I(0x11fac);		 # Copiamos valor en memoria a registro
		R1 = 10; 		# Guardamos valor de constante numerica
		R0 = R0 >= R1;		 # Operaciones logicas
		IF (R0) GT(6);		 # condición revertida
		R0 = I(0x11fb0);		 # Copiamos valor en memoria a registro
		R1 = 5; 		# Guardamos valor de constante numerica
		R0 = R0 != R1;		 # Operaciones logicas
		IF (R0) GT(7);		 # condición revertida
		GT(6);
L 7:
		R0 = 0x11fac; 		 # Almacenamos dirección en registro
		R1 = I(0x11fac);		 # Copiamos valor en memoria a registro
		R2 = 1; 		# Guardamos valor de constante numerica
		R1 = R1+R2;		 # Operaciones numericas
		I(R0) = R1;		 # Guardamos valor de registro en memoria
		GT(5);
L 6:
		GT(3);
L 4:
	STAT(3)
		FIL(0x11fa8, 4, 0);		 # Reservamos espacio para array
	CODE(3)
		R7 = R7 - 0;		 # Reservamos memoria para cambio de contexto
		R0 = 0x11fa8;		 # Almacenamos dirección de acceso de array
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R0 = 10; 		# Guardamos valor de constante numerica
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R7 = R7-8;
		P(R7+4) = R6;		 # Salvamos marco actual
		P(R7) = 15;		 # Almacenamos etiqueta de retorno
		GT(9);
L 15:
		R7 = R7+16;
		R7 = R7 + 0;		 # Volvemos al estado anterior al cambio de contexto
		GT(-2); 		# Terminamos la ejecución
END
