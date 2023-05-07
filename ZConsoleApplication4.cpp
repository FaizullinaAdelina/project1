#include <iostream>
int a,i;
int main()
{
	a = 5;
	for (i = 1; i <= a; i ++) {
		if (a == i)
			continue;
		else a = 10;
	}

	printf("%d", a);
}
