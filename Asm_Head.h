const int MAX_COM = 10;

const int MAX_COM_NAME = 10;

struct command
{
	char name[MAX_COM_NAME];
	int code;
};

int Code_Read (command* com, int* max);

int Translate (char* file_name, command com[MAX_COM], int com_num);

char* Insert_File_Name (command com[MAX_COM]);

char* Take_File_Path (int level);

char* Create_File (char* adress, command com[MAX_COM]);

/*
end 0
push 1
add 2
min 3
mul 4
div 5
*/
