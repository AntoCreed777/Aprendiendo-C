ifeq ($(OS),Windows_NT)
	CFLAGS = -Iinclude -Llib -Wall
	LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image -lm -g
else
	CFLAGS = -Iinclude -Llib
	LDFLAGS = -lSDL2main -lSDL2 -lm
endif

entrada : src/Entrada.c
	@gcc $(CFLAGS) src/Entrada.c -o bin/entrada $(LDFLAGS)
previsualizado : src/previsualizado.c
	@gcc $(CFLAGS) src/previsualizado.c -o bin/previsualizado $(LDFLAGS)
main : src/main.c
	@gcc $(CFLAGS) src/main.c -o bin/main $(LDFLAGS)
.PHONY : run_entrada debug_entrada run_main debug_main run_previsualizado

run_entrada : bin/entrada.exe
	@./bin/entrada.exe
debug_entrada : bin/entrada.exe
	@gdb ./bin/entrada.exe
run_main : bin/main.exe
	@./bin/main.exe
debug_main : bin/main.exe
	@gdb ./bin/main.exe
run_previsualizado :  bin/previsualizado.exe
	@./bin/previsualizado.exe
debug_previsualizado :  bin/previsualizado.exe
	@gdb ./bin/previsualizado.exe