CFLAGS = -Wall -Wextra -g -I ./Snake-EI3-2024
All_Object = Projet_Info_ARENE.o Projet_Info_SERPENT.o Vlad_Projet_Main.o Snake-EI3-2024/clientAPI.o Snake-EI3-2024/snakeAPI.o

Vlad_Projet_SNAKE_EXECUTABLE_v : $(All_Object)
	gcc $(CFLAGS) -o Vlad_Projet_SNAKE_EXECUTABLE_v $(All_Object)

Vlad_Projet_Main.o : Vlad_Projet_Main.c Projet_Info_ARENE.h Projet_Info_SERPENT.h Snake-EI3-2024/clientAPI.h Snake-EI3-2024/snakeAPI.h
	gcc $(CFLAGS) -o Vlad_Projet_Main.o -c Vlad_Projet_Main.c

Projet_Info_SERPENT.o : Projet_Info_SERPENT.c Projet_Info_SERPENT.h
	gcc $(CFLAGS) -o Projet_Info_SERPENT.o -c Projet_Info_SERPENT.c

Projet_Info_ARENE.o : Projet_Info_ARENE.c Projet_Info_ARENE.h
	gcc $(CFLAGS) -o Projet_Info_ARENE.o -c Projet_Info_ARENE.c

Snake-EI3-2024/clientAPI.o : Snake-EI3-2024/clientAPI.c Snake-EI3-2024/clientAPI.h
	gcc $(CFLAGS) -o Snake-EI3-2024/clientAPI.o -c Snake-EI3-2024/clientAPI.c

Snake-EI3-2024/snakeAPI.o : Snake-EI3-2024/snakeAPI.c Snake-EI3-2024/snakeAPI.h
	gcc $(CFLAGS) -o Snake-EI3-2024/snakeAPI.o -c Snake-EI3-2024/snakeAPI.c

# Convention proposee par Thibault HILAIRE de scinder le run et le make
run : Vlad_Projet_SNAKE_EXECUTABLE_v
	./Vlad_Projet_SNAKE_EXECUTABLE_v

# Excellente idee de Ayoub LADJICI de mettre un clean
clean :
	rm $(All_Object)