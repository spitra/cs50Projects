#include <stdio.h>
#include <cs50.h>

int cardTest(void);

int main(void)
{
    int output = cardTest();

    if (output == 0)
    {
        printf("INVALID\n");
    }
    if (output == 1)
    {
        printf("VISA\n");
    }
    if (output == 2)
    {
        printf("MASTERCARD\n");
    }
    if (output == 3) 
    {
        printf("AMEX\n");
    }

}

int cardTest(void)
{
    long card = get_long("Number: ");
    long c = card;
    int i = 1;
    // x represents digits to be multiplied
    int x = 0;
    
    do
    {
        
        if (i % 2 == 0)
        {
            int d = (c % 10) * 2;
            // d is just the doubled value of the final digit of c
            if (d > 9)
            {
                x += (1 + (d % 10));
            }
            else 
            {
                x += d;
            }
           
            
        }
        
        i++;
        c = c / 10;
    } 
    while (c > 0);
    

    c = card;
    i = 0;
    do 
    {
        if (i % 2 == 0)
        {
            x += (c % 10);
        }
        c = c / 10;
        i++;
        
    }
    
    while (c > 0);
    

    int type = card / 1000000000000;

    if (card < 1000000000000 || card > 9999999999999999)
    {
        return 0;
    }
    if (x % 10 != 0)
    {
        return 0;
    }

    if (type == 4)
    {
        return 1;
    }
    else if (type / 1000 == 4)
    {
        return 1;
    }
    else if (type / 100 > 50 && type / 100 < 56)
    {
        return 2;
    }
    else if (type / 10 == 34 || type / 10 == 37)
    {
        return 3;
    }
    else
    {
        return 0;
    }
}