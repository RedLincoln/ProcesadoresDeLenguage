#include "Qlib.h"
#include "Q.h"

BEGIN
L 6:
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
L 7:
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
L 8:
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
		R1 = R6+73692;
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
L 1:
		R0 = 1;
		R1 = 1;
		R0 = R0 != R1;
		IF (R0) GT(2);
		R0 = 0x11ffc;
		R1 = I(0x11ffc);
		R2 = 1;
		R2 = R2-R1;
		I(R0) = R2;
		R0 = I(0x11ffc);
		R1 = 0;
		R0 = R0 >= R1;
		IF (R0) GT(3);
		GT(2);
L 3:
		GT(1);
L 2:
		R0 = I(0x11ffc);
		R1 = 2;
		R0 = R0 != R1;
		IF (R0) GT(4);
		R1 = 0x11ffc;
		R2 = 3;
		I(R1) = R2;
		GT(5);
L 4:
		R1 = 0x11ffc;
		R3 = 4;
		I(R1) = R3;
L 5:
	STAT(1)
		FIL(0x11ff4, 8, 0);
		FIL(0x11fe8, 10, 0);
	CODE(1)
		R0 = 0x11fe8;
	STAT(2)
		STR(0x11fe4, "Hola");
	CODE(2)
		R1 = 0x11fe4;
	STAT(3)
		MEM(0x11fe0, 4);
	CODE(3)
		R0 = 0x11fe0;
		R1 = 0;
		R1 = R1 * 4;
		R1 = I(0x11ff4+R1);
		I(R0) = R1;
		R0 = 1;
		R0 = R0 * 4;
		R0 = 0x11ff4+R0;
		R1 = 1;
		I(R0) = R1;
	STAT(4)
		STR(0x11fdc, "Hola");
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
		R0 = 0x11ff4+R0;
		R7 = R7-4;
		I(R7) = R0;
		R7 = R7-8;
		P(R7+4) = R6;
		P(R7) = 9;
		GT(7);
L 9:
		R7 = R7 + 0;
		GT(-2);
END
