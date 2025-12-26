CC = gcc
CFLAGS = -Wall -I../hagl/include -I.
LDFLAGS = -lm
SDLFLAGS = $(shell sdl2-config --libs --cflags)

src = $(wildcard *.c) \
      $(wildcard ../hagl/src/*.c)

obj = $(src:.c=.o)

TARGET = demo

all: $(TARGET)

clean:
	rm -f $(obj) $(TARGET)

$(TARGET): $(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(SDLFLAGS)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run