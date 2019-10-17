#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Asm_Head.h"

int Code_Read (command* com, int* max)
{
    char* file_codes = (char*)calloc (1,255);
    file_codes = Take_File_Path (2);
    char* file_codes_name = "Command_Codes.txt";
    strcat (file_codes, file_codes_name);

	FILE* f = fopen (file_codes, "r");

	int i = 0;
    fseek (f, 0, SEEK_END);
    long pointer = ftell (f);
    fseek (f, 0, SEEK_SET);

	while (ftell(f) !=  pointer)
	{
		fscanf (f, "%s %d", &com[i].name, &com[i].code);
		i++;
	}

	*max = i;

	fclose (f);

	return 0;
}

