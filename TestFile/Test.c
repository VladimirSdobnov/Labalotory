#include <windows.h>
#include <conio.h>
#include <limits.h>
#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
int main(){
	int i1, i2, i3;
	int* p1, * p2, * p3;
	i1 = 1; i2 = 2; i3 = 3;
	p1 = &i1;
	p2 = &i2;
	p3 = &i3;
	*p1 = i1 + i2;
	*p2 += 1;
	*p3 = *p1 + *p2;
	printf("%d %d %d", i1, i2, i3);
}
