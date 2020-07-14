#include "Qlib.h"
#include "Q.h"

BEGIN
L 6:
		R6=R7;		 # Nuevo marco
		R7=R7-16;		 # Reservamos espacio para variables locales
		R0 = R6+8;		 # Almacenamos dirección relativa en registro
		R1 = 0; 		# Guardamos valor de constante numerica
		D(R0) = R1;		 # Guardamos valor de registro en memoria
		R0 = R6-4;		 # Almacenamos dirección relativa en registro
		R1 = 2; 		# Guardamos valor de constante numerica
		I(R0) = R1;		 # Guardamos valor de registro en memoria
		R0 = R6+8;		 # Almacenamos dirección relativa en registro
		R1 = I(R6-4)		 # Copiamos valor en memoria relativa a registro;
		D(R0) = R1;		 # Guardamos valor de registro en memoria
		R7=R6;		 # Liberamos memoria local
		R6=P(R7+4);		 # Recuperamos marco
		R0 = P(R7);		 # Recuperamos etiqueta de retorno
		GT(R0);
L 7:
		R6=R7;		 # Nuevo marco
		R7=R7-0;		 # Reservamos espacio para variables locales
		R0 = 0; 		# Guardamos valor de constante numerica
		R0 = R0 * 4;		 # multiplicamos indice por bytes del tipo
		I(R7-4) = R0;
		R0 = R6+16; 		 # Almacenamos dirección relativa de acceso de array
		R0 = I(R7-4) + R0;
		R1 = I(R6+8)		 # Copiamos valor en memoria relativa a registro;
		R2 = I(R6+12)		 # Copiamos valor en memoria relativa a registro;
		R2 = R2+R1;		 # Operaciones numericas
		I(R0) = R2;		 # Guardamos valor de registro en memoria
		R0 = 0; 		# Guardamos valor de constante numerica
		R0 = R0 * 4;		 # multiplicamos indice por bytes del tipo
		I(R7-4) = R0;
		R0 = R6+16; 		 # Almacenamos dirección relativa de acceso de array
		R0 = I(R7-4) + R0;
		R1 = 0; 		# Guardamos valor de constante numerica
		R1 = R1 * 4;		 # multiplicamos indice por bytes del tipo
		I(R7-4) = R1;
		R1 = R6+16; 		 # Almacenamos dirección relativa de acceso de array
		R1 = I(R7-4) + R1;
		R1 = I(R1);		 # Almacenamos valor de array (addr. relativo)
		R1 = R1 * -1;
		I(R0) = R1;		 # Guardamos valor de registro en memoria
		R7=R6;		 # Liberamos memoria local
		R6=P(R7+4);		 # Recuperamos marco
		R0 = P(R7);		 # Recuperamos etiqueta de retorno
		GT(R0);
L 8:
		R6=R7;		 # Nuevo marco
		R7=R7-20;		 # Reservamos espacio para variables locales
		R0 = R6+8;		 # Almacenamos dirección relativa en registro
		RR0 = 0.100000; 		# Guardamos valor de constante numerica
		D(R0) = RR0;		 # Guardamos valor de registro en memoria
		R0 = 0; 		# Guardamos valor de constante numerica
		R0 = R0 * 4;		 # multiplicamos indice por bytes del tipo
		I(R7-4) = R0;
		R0 = R6-8; 		 # Almacenamos dirección relativa de acceso de array
		R0 = I(R7-4) + R0;
		R1 = 3; 		# Guardamos valor de constante numerica
		I(R0) = R1;		 # Guardamos valor de registro en memoria
		R0 = R6-20;		 # Almacenamos dirección relativa en registro
		R1 = R6+73692;		 # Almacenamos dirección relativa en registro
		R7=R6;		 # Liberamos memoria local
		R6=P(R7+4);		 # Recuperamos marco
		R0 = P(R7);		 # Recuperamos etiqueta de retorno
		GT(R0);
L 0:
		R0 = 2; 		# Guardamos valor de constante numerica
		RR0 = 2.200000; 		# Guardamos valor de constante numerica
		R0 = 0; 		# Guardamos valor de constante numerica
	STAT(0)
		MEM(0x11ffc, 4);		 # Reservamos en memoria estática para variable primitiva
	CODE(0)
		R0 = 0x11ffc; 		 # Almacenamos dirección en registro
		R1 = 2; 		# Guardamos valor de constante numerica
		I(R0) = R1;		 # Guardamos valor de registro en memoria
		R0 = 0x11ffc; 		 # Almacenamos dirección en registro
		RR0 = 2.200000; 		# Guardamos valor de constante numerica
		I(R0) = RR0;		 # Guardamos valor de registro en memoria
L 1:
		R0 = 1; 		# Guardamos valor de constante numerica
		R1 = 1; 		# Guardamos valor de constante numerica
		R0 = R0 != R1;		 # Operaciones logicas
		IF (R0) GT(2);		 # condición revertida
		R0 = 0x11ffc; 		 # Almacenamos dirección en registro
		R1 = I(0x11ffc);		 # Copiamos valor en memoria a registro
		R2 = 1; 		# Guardamos valor de constante numerica
		R2 = R2-R1;		 # Operaciones numericas
		I(R0) = R2;		 # Guardamos valor de registro en memoria
		R0 = I(0x11ffc);		 # Copiamos valor en memoria a registro
		R1 = 0; 		# Guardamos valor de constante numerica
		R0 = R0 >= R1;		 # Operaciones logicas
		IF (R0) GT(3);		 # condición revertida
		GT(2);
L 3:
		GT(1);
L 2:
		R0 = I(0x11ffc);		 # Copiamos valor en memoria a registro
		R1 = 2; 		# Guardamos valor de constante numerica
		R0 = R0 != R1;		 # Operaciones logicas
		IF (R0) GT(4);		 # condición revertida
		R1 = 0x11ffc; 		 # Almacenamos dirección en registro
		R2 = 3; 		# Guardamos valor de constante numerica
		I(R1) = R2;		 # Guardamos valor de registro en memoria
		GT(5);
L 4:
		R1 = 0x11ffc; 		 # Almacenamos dirección en registro
		R3 = 4; 		# Guardamos valor de constante numerica
		I(R1) = R3;		 # Guardamos valor de registro en memoria
L 5:
	STAT(1)
		FIL(0x11ff4, 8, 0);		 # Reservamos espacio para array
		FIL(0x11fe8, 10, 0);		 # Reservamos espacio para array
	CODE(1)
		R0 = 0x11fe8; 		 # Almacenamos dirección en registro
	STAT(2)
		STR(0x11fe4, "Hola");		 # Almacenamos memoria para String
	CODE(2)
		R1 = 0x11fe4; 		 # Almacenamos dirección en registro
	STAT(3)
		MEM(0x11fe0, 4);		 # Reservamos en memoria estática para variable primitiva
	CODE(3)
		R0 = 0x11fe0; 		 # Almacenamos dirección en registro
		R1 = 0; 		# Guardamos valor de constante numerica
		R1 = R1 * 4;		 # multiplicamos indice por bytes del tipo
		R1 = I(0x11ff4+R1);		 # Almacenamos valor de array
		I(R0) = R1;		 # Guardamos valor de registro en memoria
		R0 = 1; 		# Guardamos valor de constante numerica
		R0 = R0 * 4;		 # multiplicamos indice por bytes del tipo
		R0 = 0x11ff4+R0;		 # Almacenamos dirección de acceso de array
		R1 = 1; 		# Guardamos valor de constante numerica
		I(R0) = R1;		 # Guardamos valor de registro en memoria
	STAT(4)
		STR(0x11fdc, "Hola");		 # Almacenamos memoria para String
	CODE(4)
		R7 = R7 - 0;		 # Reservamos memoria para cambio de contexto
		R0 = 2; 		# Guardamos valor de constante numerica
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R0 = 2; 		# Guardamos valor de constante numerica
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R0 = 0; 		# Guardamos valor de constante numerica
		R0 = R0 * 4;		 # multiplicamos indice por bytes del tipo
		R0 = 0x11ff4+R0;		 # Almacenamos dirección de acceso de array
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R7 = R7-8;
		P(R7+4) = R6;		 # Salvamos marco actual
		P(R7) = 9;		 # Almacenamos etiqueta de retorno
		GT(7);
L 9:
		R7 = R7 + 0;		 # Volvemos al estado anterior al cambio de contexto
		GT(-2); 		# Terminamos la ejecución
END
