#include "Asm_Head.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <dir.h>

int Find_Code (char* name, command com[MAX_COM], int com_num, int* in_code);

int Byte_Write (void* val, FILE* f, int size);

char* Insert_File_Name (void);

char* Take_File_Path (int level);

int Translate (char* file_name, command com[MAX_COM], int com_num)
{
    assert (file_name);

    const char txt[5] = ".txt";
    const char assm[5] = ".asm";
    const char txt1[10] = "_code.txt";

    char file[100] = {};
    strcpy (file, file_name);
    char file1[100] = {};
    strcpy (file1, file_name);
    char file2[100] = {};
    strcpy (file2, file_name);

    char* read = strcat (file, txt);
    char* write_asm = strcat (file1, assm);
    char* write_txt = strcat (file2, txt1);

    FILE* f = fopen (read, "r");
    if (!f)
    {
        printf ("This file doesn't exist!\n");
        abort();
    }
    FILE* fa = fopen (write_asm, "w");
    FILE* ft = fopen (write_txt, "w");


    char* buf_r = (char*)calloc (1, MAX_COM * MAX_COM_NAME);
    char* buf_r_ptr = buf_r;

    char* buf_w = (char*)calloc (1, MAX_COM * MAX_COM_NAME);
    char* buf_w_ptr = buf_w;


    char cur_com[MAX_COM_NAME] = {};
    int code = -1;
    int in_code = 0;
    int val = 0;

    int j = 0;

    while (true)
    {
        fscanf (f, "%s", &cur_com);
        in_code = 0;

        code = Find_Code (cur_com, com, com_num, &in_code);
        if (code == -1)
            printf ("Unidentified operator\n");
        fprintf (fa, "%c", (char)code);
        fprintf (ft, "%d ", code);

        if (in_code == 1)
        {
            fscanf (f, "%d", &val);
            fprintf (ft, "%d", val);
            Byte_Write (&val, fa, sizeof(in_code));
        }

        fprintf (ft, "\n");

        if (!strcmp (cur_com, com[0].name))
            break;
    }

    fclose (f);
}

int Find_Code (char* name, command com[MAX_COM], int com_num, int* in_code)
{
    assert (name);
    assert (in_code);

    int i = 0;
    for (i = 0; i < com_num; i++)
    {
        if (strcmp (com[i].name, name) == 0)
        {
            *in_code = i;
            return com[i].code;
        }

    }
    return -1;
}

int Byte_Write (void* val, FILE* f, int size)
{
    assert (val);

    int i = 0;
    for (i = 0; i < size; i++)
        fprintf (f, "%c", (char)*((char*)val + i));
    return 0;
}

char* Insert_File_Name (command com[MAX_COM])
{
    printf ("Press '0' to run a default program \"asm_progs\\coms1\".\n");
    printf ("Press '1' to create an assembler program right now!\n");
    printf ("Or enter your file name (without spaces) to compile from \"asm_progs\" folder.\n\n");

    char* file_n = (char*)calloc (1,255);
    char default_f[100] = "program_qq";
    char scanf_is_my_love[40] = {};
    char adress[255] = "asm_progs\\";
    char* path = (char*)calloc (1,255);
    path = Take_File_Path (2);
    char slash[2] = {};
    slash[0] = '\\';

    scanf ("%s", &scanf_is_my_love);

    if (scanf_is_my_love[0] == '1' && scanf_is_my_love[1] == '\0')
    {
        strcat(path, adress);
        strcpy (file_n, Create_File (path, com));
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
    char* path = (char*)calloc(1,255);
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

char* Create_File (char* adress, command com[MAX_COM])
{
    printf ("Insert the name of the new file! (Without spaces and extension)\n");
    char file_n[255] = {};
    scanf ("%s", &file_n);
    printf ("Great! And now just insert your commands!\n");

    char space = ' ';
    char slash = '\n';
    char slash1[2] = {};
    slash1[0] = '\\';

    char path[255] = {};
    strcpy (path, adress);
    strcat (path, file_n);

    if (mkdir (path) == 0)
        ;
    else perror("Error");

    strcat (path, slash1);
    strcat (path, file_n);

    char path1[255] = {};
    strcpy (path1, path);
    char txt[5] = ".txt";
    strcat (path1, txt);

    FILE* f = fopen (path1, "w");

    char a_command[MAX_COM_NAME] = {};
    int val = 0;

    while (true)
    {
        scanf ("%s", &a_command);
        fputs (a_command, f);

        if (!strcmp (com[1].name, a_command))
        {
            fputc (space, f);
            scanf ("%d", &val);
            fprintf (f, "%d", val);
        }
        fprintf (f, "%c", slash);

        if (!strcmp (com[0].name, a_command))
            break;
    }

    fclose (f);

    char* ptr = path;
    return ptr;
}
