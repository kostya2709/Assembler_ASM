# Assembler_ASM

# Desription

This project is an emulation of a translator from an assembly code to the byte code of a processor.

# Files

## Code_Reader.cpp
This file contains a function _Code_Read_ which reads commands and arguments of commands from file.

## File_Reader.cpp
This is the file from [Onegin 3.0](https://github.com/kostya2709/Onegin_End_Game). It allows to read file easily and to divide it by the end of a line. 

## Translate.cpp
This is the main file of the project. It contains all the functions to translate assembler code to the processor byte-code.

## file_paths.cpp
This is the file with some functions to ask a file to read assembler code from.

## string_lib.cpp
An auxilary file with some additional string functions.

## Examples
This a short program which reads two number, sums them, and displays the result.

```
	jmp main:	

	f_sum:
	push ax
	push bx
	add
	ret
	
	main:
	outf "Insert a\n\n"
	in
	pop ax
	outf "Insert b\n\n"
	in 
	pop bx


	call f_sum:
	
	outf "The sum is:\n\n"
	out
	end:
	end
  
  ```
