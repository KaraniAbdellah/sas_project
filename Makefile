CC=gcc
CFLAGS= -Wall -Wextra
FILIES=main.c
EXEC=main



build: 
	$(CC) $(CFLAGS) $(FILIES) -o $(EXEC)   


clean: 
	rm $(EXEC) 


