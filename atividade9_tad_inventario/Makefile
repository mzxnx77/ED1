CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2 $(shell pkg-config --cflags raylib 2>/dev/null)
LDLIBS = $(shell pkg-config --libs raylib 2>/dev/null)

ifeq ($(strip $(LDLIBS)),)
LDLIBS = -lraylib -lm
endif

SOURCES = atividade9.c entidade.c inventario.c
TARGET = atividade9

all: $(TARGET)

$(TARGET): $(SOURCES) entidade.h inventario.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDLIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
