ifeq ($(OS),Windows_NT)
	CFLAGS = -Iinclude -Llib -Wall
	LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image -lm -g
else
	CFLAGS = -Iinclude -Llib
	LDFLAGS = -lSDL2main -lSDL2 -lm
endif

main : src/main.c
	@gcc $(CFLAGS) src/main.c -o bin/main $(LDFLAGS)
.PHONY :run_main debug_main

run_main : bin/main.exe
	@./bin/main.exe
debug_main : bin/main.exe
	@gdb ./bin/main.exe