#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5.h"

int main(int argc, char *argv[])
{
    // Get the name of the files from the command line.
    if (argc != 3)
    {
        printf("You must supply two filenames.\n");
        exit(1);
    }
    
    // Check if output file is the same as input file.
    if (argc == 3)
    {
        if (strcmp(argv[1], argv[2]) == 0)
        {
            printf("You must supply two different filenames.\n");
            exit(1);
        }
    }
    
    // Open first file for reading
    FILE *in = fopen(argv[1], "r");
    if (!in)
    {
        printf("Can't open %s for reading.\n", argv[1]);
        exit(1);
    }
    
    // Open second file for writing.
    FILE *out;
    if (argc == 3)
    {
        out = fopen(argv[2], "w");
        if (!out)
        {
            printf("Can't open %s for writing.\n", argv[2]);
            exit(1);
        }
    }
    
    char line[16];
    
    // Loop through first file, one line at a time
    while(fgets(line, 16, in) != NULL)
    {
        // Remove the new line char by replacing it with a null char
        line[strlen(line) - 1] = '\0';
        
        // Hash each line from the input file.
        char *hash = md5(line, strlen(line));
        
        // Write hash to the output file.
        fprintf(out, "%s\n", hash);
        
        // Free up memory from *md5's malloc.
        free(hash);
    }
    
    // Close both files
    fclose(in);
    fclose(out);
}