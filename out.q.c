#include "Qlib.h"
#include "Q.h"

#define INI 0
BEGIN
L 8:
		R6=R7;		 # Nuevo marco
		R7=R7-8;		 # Reservamos espacio para variables locales
		R0 = I(R6+8);		 # Copiamos valor en memoria relativa a registro;
		R1 = 0; 		# Guardamos valor de constante numerica
		R0 = R0 != R1;		 # Operaciones logicas
		IF (R0) GT(9);		 # condición revertida
		R1 = 0; 		# Guardamos valor de constante numerica
		R1 = R1 * 4;		 # multiplicamos indice por bytes del tipo
		R2 = R6+12; 		 # Almacenamos dirección relativa de acceso de array
		R1 = R2+R1;
		R1 = P(R1);
		R2 = 0; 		# Guardamos valor de constante numerica
		I(R1) = R2;		 # Guardamos valor de registro en memoria
L 9:
		R0 = I(R6+8);		 # Copiamos valor en memoria relativa a registro;
		R1 = 1; 		# Guardamos valor de constante numerica
		R0 = R0 != R1;		 # Operaciones logicas
		IF (R0) GT(10);		 # condición revertida
		R1 = 0; 		# Guardamos valor de constante numerica
		R1 = R1 * 4;		 # multiplicamos indice por bytes del tipo
		R2 = R6+12; 		 # Almacenamos dirección relativa de acceso de array
		R1 = R2+R1;
		R1 = P(R1);
		R2 = 1; 		# Guardamos valor de constante numerica
		I(R1) = R2;		 # Guardamos valor de registro en memoria
L 10:
		R0 = I(R6+8);		 # Copiamos valor en memoria relativa a registro;
		R1 = 1; 		# Guardamos valor de constante numerica
		R0 = R0 <= R1;		 # Operaciones logicas
		IF (R0) GT(11);		 # condición revertida
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
		P(R7) = 12;		 # Almacenamos etiqueta de retorno
		GT(8);
L 12:
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
		P(R7) = 13;		 # Almacenamos etiqueta de retorno
		GT(8);
L 13:
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
L 11:
		R7=R6;		 # Liberamos memoria local
		R6=P(R7+4);		 # Recuperamos marco
		R0 = P(R7);		 # Recuperamos etiqueta de retorno
		GT(R0);
L 16:
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
L 19:
		R6=R7;		 # Nuevo marco
		R7=R7-4;		 # Reservamos espacio para variables locales
		R0 = R6-4;		 # Almacenamos dirección relativa en registro
		R1 = 0; 		# Guardamos valor de constante numerica
		I(R0) = R1;		 # Guardamos valor de registro en memoria
L 20:
		R0 = I(R6-4);		 # Copiamos valor en memoria relativa a registro;
		R1 = I(R6+12);		 # Copiamos valor en memoria relativa a registro;
		R0 = R0 >= R1;		 # Operaciones logicas
		IF (R0) GT(21);		 # condición revertida
		R0 = 0; 		# Guardamos valor de constante numerica
		R0 = R0 * 4;		 # multiplicamos indice por bytes del tipo
		R1 = R6+16; 		 # Almacenamos dirección relativa de acceso de array
		R0 = R1+R0;
		R0 = P(R0);
		R1 = 0; 		# Guardamos valor de constante numerica
		R1 = R1 * 4;		 # multiplicamos indice por bytes del tipo
		R2 = R6+16; 		 # Almacenamos dirección relativa de acceso de array
		R1 = R2+R1;
		R1 = I(R1);		 # Almacenamos valor de array (addr. relativo)
		R1 = P(R1);
		R2 = I(R6+8);		 # Copiamos valor en memoria relativa a registro;
		R1 = R1+R2;		 # Operaciones numericas
		I(R0) = R1;		 # Guardamos valor de registro en memoria
		R0 = R6-4;		 # Almacenamos dirección relativa en registro
		R1 = I(R6-4);		 # Copiamos valor en memoria relativa a registro;
		R2 = 1; 		# Guardamos valor de constante numerica
		R1 = R1+R2;		 # Operaciones numericas
		I(R0) = R1;		 # Guardamos valor de registro en memoria
		R7 = R7 - 4;		 # Reservamos memoria para cambio de contexto
		I(R7 + 0) = R1;		 # Almacenamos variable en pila
		R0 = 22; 		# Guardamos valor de constante numerica
		R1 = 0x11f70; 		 # Almacenamos dirección en registro
		R2 = I(R6-4);		 # Copiamos valor en memoria relativa a registro;
		GT(-12);
L 22:
		R1 = I(R7 + 0);		 # Recuperamos variable de pila
		R7 = R7 + 4;		 # Volvemos al estado anterior al cambio de contexto
		GT(20);
L 21:
		R7=R6;		 # Liberamos memoria local
		R6=P(R7+4);		 # Recuperamos marco
		R0 = P(R7);		 # Recuperamos etiqueta de retorno
		GT(R0);
L 26:
		R6=R7;		 # Nuevo marco
		R7=R7-4;		 # Reservamos espacio para variables locales
		R7 = R7 - 0;		 # Reservamos memoria para cambio de contexto
		R0 = R6-4;		 # Almacenamos dirección relativo de acceso de array
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R0 = I(R6+16);		 # Copiamos valor en memoria relativa a registro;
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R0 = I(R6+8);		 # Copiamos valor en memoria relativa a registro;
		R1 = I(R6+12);		 # Copiamos valor en memoria relativa a registro;
		R0 = R0+R1;		 # Operaciones numericas
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R7 = R7-8;
		P(R7+4) = R6;		 # Salvamos marco actual
		P(R7) = 27;		 # Almacenamos etiqueta de retorno
		GT(16);
L 27:
		R7 = R7+20;
		R7 = R7 + 0;		 # Volvemos al estado anterior al cambio de contexto
		R0 = 0; 		# Guardamos valor de constante numerica
		R0 = R0 * 4;		 # multiplicamos indice por bytes del tipo
		R1 = R6+20; 		 # Almacenamos dirección relativa de acceso de array
		R0 = R1+R0;
		R0 = P(R0);
		R1 = 0; 		# Guardamos valor de constante numerica
		R1 = R1 * 4;		 # multiplicamos indice por bytes del tipo
		R2 = R6-4; 		 # Almacenamos dirección relativa de acceso de array
		R1 = R2+R1;
		R1 = I(R1);		 # Almacenamos valor de array (addr. relativo)
		I(R0) = R1;		 # Guardamos valor de registro en memoria
		R7=R6;		 # Liberamos memoria local
		R6=P(R7+4);		 # Recuperamos marco
		R0 = P(R7);		 # Recuperamos etiqueta de retorno
		GT(R0);
L 29:
		R6=R7;		 # Nuevo marco
		R7=R7-0;		 # Reservamos espacio para variables locales
		R7 = R7 - 0;		 # Reservamos memoria para cambio de contexto
		R0 = 30; 		# Guardamos valor de constante numerica
		R1 = 0x11f2c; 		 # Almacenamos dirección en registro
		R2 = 2; 		# Guardamos valor de constante numerica
		GT(-12);
L 30:
		R7 = R7 + 0;		 # Volvemos al estado anterior al cambio de contexto
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
		P(R7) = 14;		 # Almacenamos etiqueta de retorno
		GT(8);
L 14:
		R7 = R7+16;
		R7 = R7 + 0;		 # Volvemos al estado anterior al cambio de contexto
		R7 = R7 - 0;		 # Reservamos memoria para cambio de contexto
		R0 = 15; 		# Guardamos valor de constante numerica
	STAT(4)
		STR(0x11f98, "fibo(10) = %d\n");		 # Almacenamos memoria para String
	CODE(4)
		R1 = 0x11f98; 		 # Almacenamos dirección en registro
		R2 = 0; 		# Guardamos valor de constante numerica
		R2 = R2 * 4;		 # multiplicamos indice por bytes del tipo
		R2 = I(0x11fa8+R2);		 # Almacenamos valor de array
		GT(-12);
L 15:
		R7 = R7 + 0;		 # Volvemos al estado anterior al cambio de contexto
	STAT(5)
		FIL(0x11f94, 4, 0);		 # Reservamos espacio para array
	CODE(5)
		R7 = R7 - 0;		 # Reservamos memoria para cambio de contexto
		R0 = 0x11f94;		 # Almacenamos dirección de acceso de array
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R0 = 15; 		# Guardamos valor de constante numerica
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R0 = 10; 		# Guardamos valor de constante numerica
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R7 = R7-8;
		P(R7+4) = R6;		 # Salvamos marco actual
		P(R7) = 17;		 # Almacenamos etiqueta de retorno
		GT(16);
L 17:
		R7 = R7+20;
		R7 = R7 + 0;		 # Volvemos al estado anterior al cambio de contexto
		R7 = R7 - 0;		 # Reservamos memoria para cambio de contexto
		R0 = 18; 		# Guardamos valor de constante numerica
	STAT(6)
		STR(0x11f7c, "La suma de 10+15 es %d\n");		 # Almacenamos memoria para String
	CODE(6)
		R1 = 0x11f7c; 		 # Almacenamos dirección en registro
		R2 = 0; 		# Guardamos valor de constante numerica
		R2 = R2 * 4;		 # multiplicamos indice por bytes del tipo
		R2 = I(0x11f94+R2);		 # Almacenamos valor de array
		GT(-12);
L 18:
		R7 = R7 + 0;		 # Volvemos al estado anterior al cambio de contexto
	STAT(7)
		STR(0x11f70, "aux es %d\n");		 # Almacenamos memoria para String
		FIL(0x11f6c, 4, 0);		 # Reservamos espacio para array
	CODE(7)
		R7 = R7 - 0;		 # Reservamos memoria para cambio de contexto
		R0 = 0x11f6c;		 # Almacenamos dirección de acceso de array
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R0 = 10; 		# Guardamos valor de constante numerica
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R0 = 2; 		# Guardamos valor de constante numerica
		R0 = R0 * -1;
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R7 = R7-8;
		P(R7+4) = R6;		 # Salvamos marco actual
		P(R7) = 23;		 # Almacenamos etiqueta de retorno
		GT(19);
L 23:
		R7 = R7+20;
		R7 = R7 + 0;		 # Volvemos al estado anterior al cambio de contexto
		R7 = R7 - 0;		 # Reservamos memoria para cambio de contexto
		R0 = 24; 		# Guardamos valor de constante numerica
	STAT(8)
		STR(0x11f48, "La multiplicacion de 2*10 es %d\n");		 # Almacenamos memoria para String
	CODE(8)
		R1 = 0x11f48; 		 # Almacenamos dirección en registro
		R2 = 0; 		# Guardamos valor de constante numerica
		R2 = R2 * 4;		 # multiplicamos indice por bytes del tipo
		R2 = I(0x11f6c+R2);		 # Almacenamos valor de array
		GT(-12);
L 24:
		R7 = R7 + 0;		 # Volvemos al estado anterior al cambio de contexto
		R7 = R7 - 0;		 # Reservamos memoria para cambio de contexto
		R0 = 25; 		# Guardamos valor de constante numerica
	STAT(9)
		STR(0x11f3c, "10%3 es %d\n");		 # Almacenamos memoria para String
	CODE(9)
		R1 = 0x11f3c; 		 # Almacenamos dirección en registro
		R2 = 10; 		# Guardamos valor de constante numerica
		R3 = 3; 		# Guardamos valor de constante numerica
		R3 = R3 * -1;
		R2 = R2%R3;		 # Operaciones numericas
		GT(-12);
L 25:
		R7 = R7 + 0;		 # Volvemos al estado anterior al cambio de contexto
		R7 = R7 - 0;		 # Reservamos memoria para cambio de contexto
		R0 = 0x11f6c;		 # Almacenamos dirección de acceso de array
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R0 = 6; 		# Guardamos valor de constante numerica
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R0 = 4; 		# Guardamos valor de constante numerica
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R0 = 2; 		# Guardamos valor de constante numerica
		R7 = R7-4;
		I(R7) = R0;		 # Guardamos valor de registro en memoria
		R7 = R7-8;
		P(R7+4) = R6;		 # Salvamos marco actual
		P(R7) = 28;		 # Almacenamos etiqueta de retorno
		GT(26);
L 28:
		R7 = R7+24;
		R7 = R7 + 0;		 # Volvemos al estado anterior al cambio de contexto
	STAT(10)
		STR(0x11f2c, "PrintDos %d\n");		 # Almacenamos memoria para String
	CODE(10)
		R7 = R7 - 0;		 # Reservamos memoria para cambio de contexto
		R0 = 31; 		# Guardamos valor de constante numerica
	STAT(11)
		STR(0x11f04, "La suma con auxliar de 2 + 4 + 6 es %d\n");		 # Almacenamos memoria para String
	CODE(11)
		R1 = 0x11f04; 		 # Almacenamos dirección en registro
		R2 = 0; 		# Guardamos valor de constante numerica
		R2 = R2 * 4;		 # multiplicamos indice por bytes del tipo
		R2 = I(0x11f6c+R2);		 # Almacenamos valor de array
		GT(-12);
L 31:
		R7 = R7 + 0;		 # Volvemos al estado anterior al cambio de contexto
		R7 = R7 - 0;		 # Reservamos memoria para cambio de contexto
		R7 = R7-8;
		P(R7+4) = R6;		 # Salvamos marco actual
		P(R7) = 32;		 # Almacenamos etiqueta de retorno
		GT(29);
L 32:
		R7 = R7+8;
		R7 = R7 + 0;		 # Volvemos al estado anterior al cambio de contexto
		GT(-2); 		# Terminamos la ejecución
END
