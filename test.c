#include <stdio.h>
#include <assert.h>
#include "asm1.h"
#include "asm2.h"

void test_first() {

	printf("%d\n", findSubstr("aaabbcc", "bb", 7, 2));
	printf("%d\n", findSubstr("aaabbcc", "a", 7, 1));
	printf("%d\n", findSubstr("aaabbcc", "bb", 6, 2));
	printf("%d\n", findSubstr("aaabbcc", "bb", 7, 0));
	printf("%d\n", findSubstr("aaabbcc", "dd", 7, 2));
}

int main() {
	test_first();

	printf("\n%f\n", tg(0.5));

	printf("%f\n", tg(0));

	printf("%f\n", tg(0.78539816339));

	//большое число тут , что означает inf
	printf("%f\n", tg(1.57));

	printf("%f\n", tg(3.14));

	printf("%f\n", tg(1e+9));
}