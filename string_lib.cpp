#include "main_lib.h"

char** Divide_Str (char* str, int* number, char divide_symb);

char type_of_str (char* str);

char* Change_Symb (char* str, char bad, char good);

char type_of_str (char* str)
{
    char* str_ptr = str;

    int state = 1;

    if (*str_ptr == '-')
            str_ptr++;

    while (*str_ptr)
    {

        if (*str_ptr < '0' || *str_ptr > '9' || *str_ptr == ' ')
        {
            state = 0;
            break;
        }
        str_ptr++;

    }

    if (state == 1)
        return 'd';

    state = 1;

    while (*str_ptr)
        str_ptr++;
    /*while (*str_ptr)
    {
        if (!((*str_ptr >= 'a' && *str_ptr <= 'z') || (*str_ptr >= 'A' && *str_ptr <= 'Z') || (*str_ptr == ' ')))
        {
            state = 0;
            break;
        }
        str_ptr++;
    }*/

    //if (state == 1)
        if (*(str_ptr - 1) == ':')
            return 'l';
        else return 's';

    //else return 'x';
}

char** Divide_Str (char* str, int* number, char divide_symb)
{

    assert (str);
    assert (number);

    int max_s = 10;
    int max_n = 10;

    int cur_num = 0;

    char* ptr = str;

    char** arr = (char**)calloc (sizeof(char*), max_n);

    while (true)
    {

    while (*ptr == ' ' || *ptr == divide_symb || *ptr == '\t')
        ptr++;

    if (*ptr == '\0' || *ptr == '\n' || (*ptr == '/' && *(ptr + 1) == '/'))
    {
        *number = cur_num;
        return arr;
    }

    char* cur_ptr = (char*)calloc (1, max_s);
    char* start_cur_ptr = cur_ptr;

    int cur_str_size = 0;
    int cur_max_s = max_s;

    while (*ptr != divide_symb && *ptr != '\0' && *ptr != '\n' && !(*ptr == '/' && *(ptr + 1) == '/'))
    {

        if (cur_str_size >= cur_max_s)
        {
            cur_max_s += max_s;
            start_cur_ptr = (char*)realloc (start_cur_ptr, cur_max_s);
            cur_ptr = start_cur_ptr + cur_str_size;
        }

       *cur_ptr = *ptr;
       cur_ptr++;
       ptr++;
       cur_str_size++;
    }

    *cur_ptr = '\0';

    *(arr + cur_num) = start_cur_ptr;

    cur_num++;

    if (cur_num >= max_n)
    {
        max_n += max_n;
        arr = (char**)realloc (arr, max_n);
    }

    }

}

/*! Counts length of the string.
*/
long Str_Length (char* str)
{
    char* str_cur = str;
    char* str_start = str;
    for (;*str_cur; str_cur++)
        ;
    return str_cur - str_start;
}

char* Change_Symb (char* str, char bad, char good)
{
    int size = Str_Length (str);
    char* new_str = (char*)calloc (1, Str_Length (str) + 1);
    char* new_str_start = new_str;
    int i = 0;
    for (i = 0; i < size; i++)
    {
        if (*str == bad)
        {
            *new_str = good;
            new_str++;
            str++;
            continue;
        }
            *new_str = *str;
            new_str++;
            str++;
    }

    return new_str_start;
}
