const int MAX_COM = 500;

const int MAX_COM_NAME = 10;

struct label
{
    char* name;
    int where_to_jmp;
    int* where_from_jmp;
    int jmp_count;
};

int Translate (char* file_name);

char* Insert_File_Name (void);

char* Take_File_Path (int level);

char* Create_File (char* adress);

char type_of_str (char* str);

char* Change_Symb (char* str, char bad, char good);

char** Divide_Str (char* str, int* number, char divide_symb);

long Str_Length (char* str);

/*
end 0
push 1
add 2
min 3
mul 4
div 5
pop 6
*/
