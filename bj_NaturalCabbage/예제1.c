#include <stdio.h>

void func(int a, int b)
{
	b = 5;
	a += b;
	printf("func %d %d\n", a, b);

}

int main()
{
	int x = 5, y = 7;
	func(x, y);

	printf("main %d %d\n", x, y);
	return 0;
}