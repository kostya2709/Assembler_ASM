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


This a short program which reads two number, sums them up, and displays the result.



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
  
  This code is translated into this byte-code:
  ![byte-code](https://github.com/kostya2709/Assembler_ASM/blob/master/Examples/sum/%D0%A1%D0%BD%D0%B8%D0%BC%D0%BE%D0%BA%20%D1%8D%D0%BA%D1%80%D0%B0%D0%BD%D0%B0%20%D0%BE%D1%82%202020-06-25%2013-54-37.png)

You can see more examples in the folder "Examples".
