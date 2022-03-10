#include <stdio.h>
#include <string.h>

int ispalindrome(char *p, int n)
{
    for (int i = 0; i < n / 2; i++)
        if (*(p + i) != *(p + n - 1 - i))
            return 0;
    return 1;
}

int main()
{
    int n;
    char str[10] = {};
    scanf("%d", &n);
    sprintf(str, "%d", n);
    printf(ispalindrome(str, strlen(str)) ? "Y" : "N");
    return 0;
}

