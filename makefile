run :
	./Vlad_Projet_SNAKE_EXECUTABLE_v

Vlad_Projet_SNAKE_EXECUTABLE_v : Vlad_Projet_Main.o Snake-EI3-2024/snakeAPI.o Snake-EI3-2024/clientAPI.o
	gcc -o Vlad_Projet_SNAKE_EXECUTABLE_v Vlad_Projet_Main.o ./Snake-EI3-2024/snakeAPI.o Snake-EI3-2024/clientAPI.o

Vlad_Projet_Main.o : Vlad_Projet_Main.c Projet_Info.h
	gcc -o Vlad_Projet_Main.o -c Vlad_Projet_Main.c -I ./Snake-EI3-2024

Snake-EI3-2024/clientAPI.o : Snake-EI3-2024/clientAPI.c
	gcc -o Snake-EI3-2024/clientAPI.o -c Snake-EI3-2024/clientAPI.c -I ./Snake-EI3-2024

Snake-EI3-2024/snakeAPI.o : Snake-EI3-2024/snakeAPI.c
	gcc -o Snake-EI3-2024/snakeAPI.o -c Snake-EI3-2024/snakeAPI.c -I ./Snake-EI3-2024
