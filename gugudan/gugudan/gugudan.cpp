#include <iostream>

__declspec(dllexport) int printDan(void) {
	int i, j;
	for (i = 1; i <= 10; i++) {
		for (j = 1; j <= 10; j++) {
			std::cout << i << " x " << j << " = " << i * j << std::endl;
		}
	}
	return 0;
}