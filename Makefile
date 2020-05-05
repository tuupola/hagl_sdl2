SDLFLAGS = $(shell sdl2-config --libs --cflags)

all: demo.c
	gcc -o demo demo.c hagl_hal.c ../hagl/rgb565.c ../hagl/hagl.c ../hagl/clip.c ../hagl/bitmap.c ../hagl/fps.c -I. -I../hagl $(SDLFLAGS) -lpng -lz -ljpeg -lfreetype -lm

clean:
	$(RM) *.o
	$(RM) demo
