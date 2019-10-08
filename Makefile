SDLFLAGS = $(shell sdl2-config --libs --cflags)

all: demo.c
	gcc -o demo demo.c copepod_hal.c copepod/rgb565.c copepod/copepod.c copepod/cohen_sutherland.c copepod/bitmap.c -I. -I./copepod $(SDLFLAGS) -lpng -lz -ljpeg -lfreetype -lm

clean:
	$(RM) *.o
	$(RM) demo
