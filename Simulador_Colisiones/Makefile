ifeq ($(OS),Windows_NT)
	CC = gcc
	CFLAGS = -Iinclude -Llib -Wall
	LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image -lm -g
	OBJS_DIR = src/obj
	OBJS = $(OBJS_DIR)/main.o $(OBJS_DIR)/colisiones.o $(OBJS_DIR)/entrada.o $(OBJS_DIR)/visualizacion.o
	TARGET = bin\main.exe
else
	CFLAGS = -Iinclude -Llib
	LDFLAGS = -lSDL2main -lSDL2 -lm
endif

all: $(TARGET)

$(OBJS_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET) : $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@$(info Compilacion terminada)

.PHONY: run debug clean

run: $(TARGET)
	@./$(TARGET)
debug: $(TARGET)
	@gdb ./$(TARGET)
clean:
	@del .\$(TARGET)
	@$(info Ejecutable eliminado)
