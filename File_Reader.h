#ifdef Debug
#define PRINTF printf
#else
#define PRINTF if (0) printf
#endif // My_Debug

typedef struct {
    char* start;
    char* end;
    }poem_line;

char* File_Reader (char* file_name, long* num_lines, long* num_symb);

poem_line* StringMaker (char* str, int length, int amount);

int WriteFile (const char *file, int num, poem_line pointer[]);

char* Create_Str (long* length, const char* file_read);
