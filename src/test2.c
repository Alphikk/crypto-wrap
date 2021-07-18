#include <stdio.h>





int main (void)
{
    int n = 18;
    printf("%d",!(n & (n - 1)));
}
