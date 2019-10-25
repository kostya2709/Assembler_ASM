#include "main_lib.h"

int Byte_Write_Str (void* val, char* str, int size);

char* Write_Down_Args (int args_num, char** comms, char* buf_w_ptr, char* name, int num_of_cur_line, int com_amount, int* lab_num, label* lab, char* buf_w);

label* Label_Construct (int label_num, int label_name_size);

int Label_Exist (char* name, int lab_count, label* lab);

int Make_Labels (char* lab_name, int* lab_num, label* lab, char* buf_w_ptr, char* buf_w, char type);

int Translate (char* file_name)
{
    assert (file_name);

    const char txt[5] = ".txt";
    const char assm[5] = ".asm";

    char file[100] = {};
    strcpy (file, file_name);
    char file1[100] = {};
    strcpy (file1, file_name);

    char* read = strcat (file, txt);
    char* write_asm = strcat (file1, assm);

    FILE* f = fopen (read, "r");
    if (!f)
    {
        printf ("File is %s\n", read);
        printf ("This file doesn't exist!\n");
        abort();
    }
    FILE* fa = fopen (write_asm, "w");


    long num_lines = 0;
    long num_symb = 0;
    char* buf_r = File_Reader (read, &num_lines, &num_symb);
    poem_line* buf_l = StringMaker (buf_r, num_symb, num_lines);

    int buf_w_size = num_symb;
    char* buf_w = (char*)calloc (1, buf_w_size);
    char* buf_w_ptr = buf_w;

    int code = -1;
    int in_code = 0;

    label* lab = Label_Construct (50, 15);
    int lab_num = 0;
    int num_of_cur_line = 0;

    while (true)
    {
        in_code = 0;
        int com_amount = 0;

        if (buf_l[num_of_cur_line].start == buf_l[num_of_cur_line].end)
        {
            num_of_cur_line++;
            continue;
        }

        char* temp_str = Change_Symb (buf_l[num_of_cur_line].start, '\t', ' ');

        char** comms = Divide_Str (Change_Symb (buf_l[num_of_cur_line].start, '\t', ' '), &com_amount, ' ');

        if (com_amount == 0)
        {
            num_of_cur_line++;
            continue;
        }

        PRINTF ("com = %s, len = %d, dp = %d, buf %d, com_amount %d\n", *comms, Str_Length (*comms), buf_w_ptr - buf_w, buf_w_size, com_amount);

        com_amount--;

    #define ASM_CMD( name, num, args_num, code)                     \
    else if (strcmp (*comms, #name) == 0)                           \
    {                                                               \
        *(buf_w_ptr) = (char)num;                                   \
        buf_w_ptr++;                                                \
                                                                    \
        buf_w_ptr = Write_Down_Args (args_num, comms, buf_w_ptr, #name, num_of_cur_line, com_amount, &lab_num, lab, buf_w); \
                                                                        \
        if (num == 0)                                                   \
            break;                                                      \
                                                                        \
        num_of_cur_line++;                                              \
                                                                        \
    }

    if (false);

    #include "..\Commands_Header.h"

    else if (type_of_str (*comms) == 'l')
    {
        Make_Labels (*comms, &lab_num, lab, buf_w_ptr, buf_w, 'l');

        num_of_cur_line++;
    }
    else
    {
            printf ("Unidentified operator in line %d.\nIt is %s\nIts type is %c\nIts size is %d\n\n", num_of_cur_line + 1, *comms, type_of_str (*comms), Str_Length(*comms));
            abort();
    }

    #undef ASM_CMD

    int cur_length = buf_w_ptr - buf_w;
    /*if (buf_w_size - cur_length <= 50)
    {
        buf_w_size *= 2;
        buf_w = (char*)realloc (buf_w, buf_w_size);
        buf_w_ptr = buf_w + cur_length;
        printf ("change\n");
    }*/

    //free (buf_l[num_of_cur_line - 1].start);
    //free (comms);

    }

    int i = 0;
    for (i = 0; i < lab_num; i++)
    {
        int temp_to = lab[i].where_to_jmp;
        int k = 0;
        for (k = 0; k < lab[i].jmp_count; k++)
        {
            Byte_Write_Str(&temp_to, buf_w + *(lab[i].where_from_jmp + k), sizeof (int));
        }

    }

    for (i = 0; i < lab_num; i++)
    {
        PRINTF ("name = %s, where_to = %d, counter = %d\n", lab[i].name, lab[i].where_to_jmp, lab[i].jmp_count);
    }

    fwrite (buf_w, buf_w_ptr - buf_w, 1, fa);
    fclose (fa);
    fclose (f);

    return 0;
}

int Byte_Write_Str (void* val, char* str, int size)
{
    assert (val);

    int i = 0;
    for (i = 0; i < size; i++)
        *(str + i) = (char)*((char*)val + i);

    return 0;
}

char* Write_Down_Args (int args_num, char** comms, char* buf_w_ptr, char* name, int num_of_cur_line, int com_amount, int* lab_num, label* lab, char* buf_w)
{

    if (com_amount != args_num)
        {
                printf ("Invalid number of arguments, function %s, line %d.\n"
                "Valid number is %d. Your current number is %d.\n",name, num_of_cur_line + 1, args_num, com_amount);
                abort();

        }

        int i = 0;
        if (args_num > 0)
            for (i = 0; i < args_num; i++)
                {
                    if (type_of_str (*(comms + 1)) == 'd')
                        *buf_w_ptr = 1;

                    else if (type_of_str (*(comms + 1)) == 's')
                    {
                            *buf_w_ptr = Str_Length (*(comms + 1));
                    }
                    else if (type_of_str (*(comms + 1)) == 'l')
                        ;
                    else { printf ("Invalid type of argument!\n"
                         "Command %s, line %d.\n", name, num_of_cur_line + 1); abort();}
                    buf_w_ptr++;
                }

            for (i = 1; i < com_amount + 1; i++)
            if (type_of_str (*(comms + i)) == 'd')
            {
                int temp = atoi (*(comms + i));
                Byte_Write_Str (&temp, buf_w_ptr, sizeof (temp));
                buf_w_ptr += sizeof (temp);
            }
            else if (type_of_str (*(comms + i)) == 's')
            {
                int len = Str_Length (*(comms + i));
                Byte_Write_Str (*(comms + i), buf_w_ptr, len);
                buf_w_ptr += len;
            }
            else if (type_of_str (*(comms + 1)) == 'l')
                    {
                        int temp = -1;
                        buf_w_ptr--;
                        Make_Labels (*(comms + 1), lab_num, lab, buf_w_ptr, buf_w, 'j');
                        Byte_Write_Str (&temp, buf_w_ptr, sizeof (temp));
                        buf_w_ptr += sizeof (int);
                    }

            return buf_w_ptr;
}

label* Label_Construct (int label_num, int label_name_size)
{
        label* lab = (label*) calloc (1,label_name_size + sizeof (int) + sizeof(char*) * label_num );
        int i = 0;
        for (i = 0; i < label_num; i++)
        {
            lab[i].name = (char*)calloc (1, label_name_size);
            lab[i].where_from_jmp = (int*)calloc (sizeof(int), label_num);
            lab[i].where_to_jmp = -1;
        }
        return lab;
}

int Make_Labels (char* lab_name, int* lab_num, label* lab, char* buf_w_ptr, char* buf_w, char type)
{
#define new_label \
lab[*lab_num].name = lab_name;      \
lab[*lab_num].where_to_jmp = buf_w_ptr - buf_w; \
*lab_num += 1;

        if (type == 'l')
        {
            int state = Label_Exist (lab_name, *lab_num, lab);
            if (state == -1)
            {
                new_label
            }

            lab[state].where_to_jmp = buf_w_ptr - buf_w;
        }

        else if (type == 'j')
        {
            int state = Label_Exist (lab_name, *lab_num, lab);
            if (state == -1)
            {
                new_label
                state = *lab_num - 1;
            }

            *(lab[state].where_from_jmp + lab[state].jmp_count) = (int)(buf_w_ptr - buf_w);
            lab[state].jmp_count += 1;
        }

#undef new_label

    return 0;

}

int Label_Exist (char* name, int lab_count, label* lab)
{
    int i = 0;
    for (i = 0; i < lab_count; i++)
        if (strcmp (lab[i].name, name) == 0)
            return i;
    return -1;
}
