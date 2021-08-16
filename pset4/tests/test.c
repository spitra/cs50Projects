#include <stdio.h>

int main(void)
{
    int args[10];
    for ( int i = 0; i < 10; i++)
    {
        args[i] = i;
        printf("%i\n", args[i]);
    }
    
    printf("%i\n", args[-1000]);
}