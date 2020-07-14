#include "Qlib.h"
#include "Q.h"

BEGIN
L 1:
		R6=R7;
		R7=R7-16;
		R0 = R6+8;
		R1 = 0;
		D(R0) = R1;
		R0 = R6-4;
		R1 = 2;
		I(R0) = R1;
		R0 = R6+8;
		R1 = I(R6-4);
		D(R0) = R1;
		R7=R6;
		R6=P(R7+4);
		R0 = P(R7);
		GT(R0);
L 2:
		R6=R7;
		R7=R7-0;
		R0 = 0;
		R0 = R0 * 4;
		I(R7-4) = R0;
		R0 = R6+16;
		R0 = I(R7-4) + R0;
		R1 = I(R6+8);
		R2 = I(R6+12);
		R2 = R2+R1;
		I(R0) = R2;
		R0 = 0;
		R0 = R0 * 4;
		I(R7-4) = R0;
		R0 = R6+16;
		R0 = I(R7-4) + R0;
		R1 = 0;
		R1 = R1 * 4;
		I(R7-4) = R1;
		R1 = R6+16;
		R1 = I(R7-4) + R1;
		R1 = I(R1);
		R1 = R1 * -1;
		I(R0) = R1;
		R7=R6;
		R6=P(R7+4);
		R0 = P(R7);
		GT(R0);
L 3:
		R6=R7;
		R7=R7-20;
		R0 = R6+8;
		RR0 = 0.100000;
		D(R0) = RR0;
		R0 = 0;
		R0 = R0 * 4;
		I(R7-4) = R0;
		R0 = R6-8;
		R0 = I(R7-4) + R0;
		R1 = 3;
		I(R0) = R1;
		R0 = R6-20;
		R1 = R6+73688;
		R7=R6;
		R6=P(R7+4);
		R0 = P(R7);
		GT(R0);
L 0:
		R0 = 2;
		RR0 = 2.200000;
		R0 = 0;
	STAT(0)
		MEM(0x11ffc, 4);
	CODE(0)
		R0 = 0x11ffc;
		R1 = 2;
		I(R0) = R1;
		R0 = 0x11ffc;
		RR0 = 2.200000;
		I(R0) = RR0;
		R0 = 2;
		R1 = 2;
		R0 = R0 != R1;
		R1 = 2;
		R2 = 2;
		R1 = R1 != R2;
		R2 = 3;
		R3 = 4;
		R2 = R2 != R3;
		R0 = I(0x11ffc);
		RR0 = 2.200000;
		R0 = R0 != RR0;
	STAT(1)
		MEM(0x11ff8, 4);
		FIL(0x11ff0, 8, 0);
		FIL(0x11fe4, 10, 0);
	CODE(1)
		R0 = 0x11fe4;
	STAT(2)
		STR(0x11fe0, "Hola");
	CODE(2)
		R1 = 0x11fe0;
	STAT(3)
		MEM(0x11fdc, 4);
	CODE(3)
		R0 = 0x11fdc;
		R1 = 0;
		R1 = R1 * 4;
		R1 = I(0x11ff0+R1);
		I(R0) = R1;
		R0 = 1;
		R0 = R0 * 4;
		R0 = 0x11ff0+R0;
		R1 = 1;
		I(R0) = R1;
	STAT(4)
		STR(0x11fd8, "Hola");
	CODE(4)
		R7 = R7 - 0;
		R0 = 2;
		R7 = R7-4;
		I(R7) = R0;
		R0 = 2;
		R7 = R7-4;
		I(R7) = R0;
		R0 = 0;
		R0 = R0 * 4;
		R0 = 0x11ff0+R0;
		R7 = R7-4;
		I(R7) = R0;
		R7 = R7-8;
		P(R7+4) = R6;
		P(R7) = 4;
		GT(2);
L 4:
		R7 = R7 + 0;
		GT(-2);
END
