#include <my_cal.S>

char a[1086], b[1086];
int ans, i, n = 1, j;
char x;

int main()
{
	while((x = _my_getchar())!='\n')
	{
		a[i++] = x;
	}
	for (j = i - 1; j >= 0; j--)
	{
		ans += n * a[j];
		n *= 10;
	}
	for(i = 0; ans; i++)
	{
		b[i] = ans % 2 - '0';
		ans /= 2;
	}
	for (j = i - 1; j >= 0; j--)
	_my_putchar(b[j]);
}
