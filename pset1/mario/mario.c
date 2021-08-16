#include <stdio.h>
#include <cs50.h>



int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");

    } 
    while (n < 1 || n > 8);
    for (int i = n; i > 0; i--)
    {
        for (int j = 0; j < n; j++)
        {
            int c = i - 1;
            if (j < c)
            {
                printf(" ");
            }    
            else
            {
                printf("#");
            }
        }
        printf("  ");
        for (int j = 0; j < n; j++)
        {
            int c = (n - (i - 1));
            if (j < c)
            {
                printf("#");
            }
            
        }
        printf("\n");
    }
}