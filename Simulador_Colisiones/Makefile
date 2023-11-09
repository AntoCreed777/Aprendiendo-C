ifeq ($(OS),Windows_NT)
	CFLAGS = -Iinclude -Llib -Wall
	LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lm -g
else
	CFLAGS = -Iinclude -Llib
	LDFLAGS = -lSDL2main -lSDL2 -lm
endif

ENTRADA : src/Entrada.c
	@gcc $(CFLAGS) src/Entrada.c -o bin/entrada $(LDFLAGS)
MAIN : src/main.c
	@gcc $(CFLAGS) src/main.c -o bin/main $(LDFLAGS)
.PHONY : run_entrada debug_entrada run_main debug_main

run_entrada : bin/entrada.exe
	@./bin/entrada.exe
debug_entrada : bin/entrada.exe
	@gdb ./bin/entrada.exe
run_main : bin/main.exe
	@./bin/main.exe
debug_main : bin/main.exe
	@gdb ./bin/main.exe