#include <stdio.h>
#include <cs50.h>
#include <string.h>

string toUpperCase(string input);
char charToUpperCase(char input);
int validateKey(string);

int main(int argc, string argv[])
{
    if (argv[1] == NULL || argv[2] != NULL)
    {
        printf("Usage: ./substitution (Key)\n");
        {
            return 1;
        }
    }
    if (validateKey(argv[1]) == 1)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    if (validateKey(argv[1]) == 2)
    {
        printf("Key can't repeat characters.\n");
        return 1;
    }
    if (validateKey(argv[1]) == 3)
    {
        printf("Key can only contain alphabetic characters\n");
        return 1;
    }
    
    char key[26];
    
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        key[i] = toUpperCase(argv[1])[i];
    }
    
    string plainText = get_string("plaintext: ");
    string cipherText = plainText;
  
    for (int i = 0; i < strlen(plainText); i++)
    {
 
        int asciiCode = 65;
        for (int j = 0; j < 27; j++)
        {
            if ((int) charToUpperCase(plainText[i]) == asciiCode)
            {
                if (plainText[i] >= 97)
                {
                    cipherText[i] = key[j] + 32;
                }
                else
                {
                    cipherText[i] = key[j];
                }
                break;
            }
            asciiCode++;
        }
        
        
    }
    printf("ciphertext: %s\n", cipherText);
    return 0;
    
    

}



int validateKey(string input)
{
    input = toUpperCase(input);
    
    //Checks length of key
    if (strlen(input) != 26)
    {
        return 1;
    }
    
    //Checks for reapeating characters in key
    for (int i = 0; i < strlen(input) - 1; i++)
    {
        char index = input[i];
        int instances = 1;
        for (int j = i + 1; j < strlen(input); j++)
        {
            if (index == input[j])
            {
                instances++;
            }
        }
        if (instances > 1)
        {
            return 2;
        }

    }
    
    //Checks for non-alphabetic characters
    
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] < 65 || input[i] > 90)
        {
            return 3;
        }
    }
    
    
    
    return 0;
}

//converts key to uppercase
string toUpperCase(string input)
{
    string output = input;
    for (int i = 0; i <= strlen(input); i++)
    {
        if ((int)input[i] >= 97 && (int)input[i] <= 122)
        {
            output[i] = ((char)((int) input[i] - 32));
        }
    }
    return output;
}

//converts char to uppercase
char charToUpperCase(char input)
{
    char output = input;
    if ((int) input >= 97 && (int) input <= 122)
    {
        output = ((char)((int) input - 32));
    }
    return output;
}