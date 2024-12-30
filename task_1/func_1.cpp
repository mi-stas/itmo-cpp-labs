#include <iostream>

int f(void) {
	int var1 = 2;
	float var2{17};
	double var3 = 52;
	char var4{9};
    std::cout << var1 + var2 - var3 / var4;
	return 0;
}

int main() {
	f();
}