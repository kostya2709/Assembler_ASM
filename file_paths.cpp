#include "main_lib.h"

char* Insert_File_Name (void);

char* Take_File_Path (int level);

char* Create_File (char* adress);

char* Insert_File_Name (void)
{
    printf ("Press '0' to run a default program \"asm_progs\\program_qq\".\n");
    printf ("Press '1' to create an assembler program right now!\n");
    printf ("Or enter your file name (without spaces) to compile from \"asm_progs\" folder.\n\n");

    char* file_n = (char*)calloc (1,511);
    char default_f[511] = "program_qq";
    char scanf_is_my_love[40] = {};
    char adress[511] = "asm_progs\\";
    char* path = (char*)calloc (1,511);
    path = Take_File_Path (2);
    char slash[2] = {};
    slash[0] = '\\';

    scanf ("%s", &scanf_is_my_love);

    if (scanf_is_my_love[0] == '1' && scanf_is_my_love[1] == '\0')
    {
        strcat(path, adress);
        strcpy (file_n, Create_File (path));
    }

    else if (scanf_is_my_love[0] == '0' && scanf_is_my_love[1] == '\0')
    {
        strcat (adress, default_f);
        strcat (adress, slash);
        strcat(path, adress);
        strcpy (file_n, strcat (path, default_f));
    }

    else
    {
        strcat (adress, scanf_is_my_love);
        strcat (adress, slash);
        strcat(path, adress);
        strcpy(file_n, strcat (path, scanf_is_my_love));
    }

    return file_n;
}

char* Take_File_Path (int level)
{
    char* path = (char*)calloc(1,511);
    strcpy (path, __FILE__);

    int count = level;
    char* ptr = path;
    while (*ptr++);
    while (count)
    {
        if (*ptr == '\\')
            count--;
        if (count) *ptr = '\0';
        ptr--;
    }

    ptr = path;

    return ptr;
}

char* Create_File (char* adress)
{
    printf ("Insert the name of the new file! (Without spaces and extension)\n");
    char file_n[511] = {};
    scanf ("%s", &file_n);
    printf ("Great! And now just insert your commands!\nPress '!@#' to finish your program!\n\n");

    char space = ' ';
    char slash = '\n';
    char slash1[2] = {};
    slash1[0] = '\\';

    char path[511] = {};
    strcpy (path, adress);
    strcat (path, file_n);

    if (mkdir (path) == 0)
        ;
    else perror("Error");

    strcat (path, slash1);
    strcat (path, file_n);

    char path1[511] = {};
    strcpy (path1, path);
    char txt[5] = ".txt";
    strcat (path1, txt);

    FILE* f = fopen (path1, "w");

    char* a_command = (char*)calloc (1, MAX_COM_NAME);
    int val = 0;
    char* end = "!@#";
    gets (a_command);

    while (true)
    {
        gets (a_command);
        if (!strcmp (a_command, end))
            break;
        fputs (a_command, f);
        fprintf (f, "%c", slash);
    }

    fclose (f);

    char* ptr = path;
    return ptr;
}
