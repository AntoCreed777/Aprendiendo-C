ifeq ($(OS),Windows_NT)
	CFLAGS = -Iinclude -Llib
	LDFLAGS = -lmingw32 -lSDL2main -lSDL2
else
	CFLAGS = -Iinclude -Llib
	LDFLAGS = -lSDL2main -lSDL2
endif

TARGET = bin/main

$(TARGET): src/main.c
	gcc $(CFLAGS) src/main.c -o $(TARGET) $(LDFLAGS)

.PHONY: run
run: $(TARGET)
	./$(TARGET)
