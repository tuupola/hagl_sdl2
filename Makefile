SDLFLAGS = $(shell sdl2-config --libs --cflags)

all: demo.c
	gcc -o demo demo.c copepod-hal.c copepod/copepod.c copepod/color.c copepod/cohen-sutherland.c copepod/framebuffer.c -I. -I./copepod $(SDLFLAGS) -lpng -lz -ljpeg -lfreetype -lm

clean:
	$(RM) *.o
	$(RM) demo
