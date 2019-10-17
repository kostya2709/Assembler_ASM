#include "Asm_Head.h"
#include "File_Reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    int com_num = 0;
    command com[MAX_COM] = {};
    Code_Read (com, &com_num);

    char* file_n = Insert_File_Name (com);

    Translate (file_n, com, com_num);

    return 0;
}
