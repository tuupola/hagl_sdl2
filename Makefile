SDLFLAGS = $(shell sdl2-config --libs --cflags)

all: demo.c
	gcc -o demo demo.c hagl_hal.c ../hagl/src/*.c -I. -I../hagl/include -I../hagl/include/hagl $(SDLFLAGS) -lpng -lz -ljpeg -lfreetype -lm

clean:
	$(RM) *.o
	$(RM) demo
