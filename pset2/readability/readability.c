#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    int words = 1;
    int letters = 0;
    int sentences = 0;
    string sentence = get_string("Text: ");
    for (int i = 0 ; i <= strlen(sentence) ; i++)
    {
        if (sentence[i] == ' ')
        {
            words++;
        }
        if (sentence[i] == '.' || sentence[i] == '!' || sentence[i] == '?')
        {
            sentences++;
        }
        if ((sentence[i] >= 65 && sentence[i] <= 90) || (sentence[i] >= 97 && sentence[i] <= 122))
        {
            letters++;
        }
    }
    
    float l = (float) letters / words * 100;
    float s = (float) sentences / words * 100;

    
    
    int index = round(.0588 * l - .296 * s - 15.8);
   
    if (index >= 16)
    {
        printf("Grade 16+\n");
        
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}