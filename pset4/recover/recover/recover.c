

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<cs50.h>






typedef unsigned char BYTE;

int main(int argc, char *argv[])
{
    
    
    if (argc != 2)
    {
        printf("Usage ./recover image name\n");
        return 1;
    }

    BYTE buffer[512];
    int counter = 0;
    
    FILE *infile = fopen(argv[1], "r");
    FILE *outfile;
    char filename[8];
    while (fread(buffer, 512, 1, infile) == 1)
    {
        
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (counter > 0)
            {
                fclose(outfile);
                
                sprintf(filename, "%03d.jpg", counter);
                counter += 1;
                
                outfile = fopen(filename, "w");
                
                fwrite(buffer, 512, 1, outfile);
            }
            if (counter == 0)
            {
                sprintf(filename, "%03d.jpg", counter);
                counter += 1;
                
                outfile = fopen(filename, "w");
                
                fwrite(buffer, 512, 1, outfile);
            }
        }
        else if (counter > 0)
        {
            fwrite(buffer, 512, 1, outfile);
        }
    }
    
    fclose(outfile);
    fclose(infile);
    return 0;
}