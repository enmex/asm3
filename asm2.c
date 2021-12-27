#include "asm2.h"
double tg(double x) {

	double result;
	double sin, cos;

	__asm {
		finit

		//вычислим x = x - [x/2*pi]*2pi
		fldpi //pi
		fadd	st(0), st(0) //2pi
		fld		qword ptr x //2pi x
		fld		qword ptr x //2pi x x
		fdiv	st(0), st(2) //2pi x x/2pi
		frndint		//2pi x [x/2pi]
		fmul	st(0), st(2) //2pi x [x/2pi]*2pi
		fxch	st(1) //2pi [x/2pi]*2pi x
		fsub	st(0), st(1)
		fstp	x
		fstp	st(0)
		fstp	st(0)

		fld1
		fld1
		fld1

		fld		qword ptr x
		fldz
		fld		qword ptr x
		fld		qword ptr x

		mov		ecx, 10
		mov		eax, 2
	LOOP_FOR_COMMON_TERM_SIN:
			
		fmul	st(0), st(1)
		fmul	st(0), st(1)

		fxch	st(2)
		fadd	st(0), st(2)

				
		fxch	st(4)
		fadd	st(0), st(6)
		fmul	st(5), st(0)
		fadd	st(0), st(6)
		fmul	st(5), st(0)
		fxch	st(4)

				
		fdiv	st(0), st(5)

		mov		edx, ecx
		and edx, 1
		cmp		edx, 0
		je		IS_ODD_SIN
		jmp		IS_EVEN_SIN

	IS_ODD_SIN :
		fchs

	IS_EVEN_SIN :
		fadd	st(3), st(0)

		fsub	st(0), st(0)
		fxch	st(2)

		loop LOOP_FOR_COMMON_TERM_SIN

		fxch	st(3)
		fstp	qword ptr sin

		finit
		fld1
		fld1

		fadd	st(0), st(0)

		fld1

		fadd	st(0), st(0)

		fld1
		fldz
		fld		qword ptr x
		fld1

		mov		ecx, 10
		mov		eax, 2

	LOOP_FOR_COMMON_TERM_COS:
		fmul	st(0), st(1)
		fmul	st(0), st(1)

		fxch	st(2)
		fadd	st(0), st(2)

				
		fdiv	st(0), st(5)

				
		fxch	st(4)
		fadd	st(0), st(6)
		fmul	st(5), st(0)
		fadd	st(0), st(6)
		fmul	st(5), st(0)
		fxch	st(4)

		mov		edx, ecx
		and edx, 1
		cmp		edx, 0
		je		IS_ODD_COS
		jmp		IS_EVEN_COS

	IS_ODD_COS :
		fchs

	IS_EVEN_COS :
			
		fadd	st(3), st(0)
		
		fsub	st(0), st(0)
		fxch	st(2)

		loop LOOP_FOR_COMMON_TERM_COS

		fxch	st(3)
		fstp	qword ptr cos
	END:	
		finit
		fld		qword ptr cos
		fld		qword ptr sin
		fdiv	st(0), st(1)
		fstp	qword ptr result
	}
	return result;
}
