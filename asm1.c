#include <stdlib.h>
#include <stdio.h>

int findSubstr(char* str, char* substr, int size_str, int size_substr) {

	int result;

	__asm {
		//проверяем что строка не пустая
		mov		eax, str //присваиваем регистру строку
		cmp		eax, 0   //проверяем что она нулевая
		je		NULL_STRING //если она нулевая, то отправляемся на этот лейбл

		//проверяем что подстрока не пустая
		mov		eax, substr
		cmp		eax, 0
		je		NULL_STRING

		//проверяем что размеры не пустые
		mov		eax, size_str
		cmp		eax, 0
		je		EMPTY_SIZE

		mov		eax, size_substr
		cmp		eax, 0
		je		EMPTY_SIZE

		xor		ebx, ebx
		mov		esi, str
		mov 	edi, substr
		
	CYCLE:
		xor		ecx, ecx
		cmp		ebx, size_str
		je		SUBSTR_NOT_FOUND

		mov		dl, [esi][ebx]
		cmp		[edi][ecx], dl
		je		CHECK_FOR_SUBSTR

		inc		ebx
		jmp		CYCLE

	CHECK_FOR_SUBSTR:
		cmp		ecx, substr
		je		GET_SUBSTR_POS

		inc		ebx
		inc		ecx

		mov		dl, [esi][ebx]
		cmp		[edi][ecx], dl
		je		CHECK_FOR_SUBSTR

		cmp		ebx, size_str
		jne		GET_SUBSTR_POS
		jmp		SUBSTR_NOT_FOUND

	GET_SUBSTR_POS:
		sub		ebx, ecx
		jmp		END


	SUBSTR_NOT_FOUND:
		jmp		END_SUBSTR_NOT_FOUND


	NULL_STRING:
		jmp		END

	MALLOC_NULL:
		jmp		END

	EMPTY_SIZE:
		xor		ebx, ebx
		mov		result, ebx
		jmp		END_OF_PROGRAMM

	END:
		mov		result, ebx
		jmp		END_OF_PROGRAMM

	END_SUBSTR_NOT_FOUND:
		xor		ebx, ebx
		mov		result, ebx
		jmp		END_OF_PROGRAMM

	END_OF_PROGRAMM:
	}
	return result;
}