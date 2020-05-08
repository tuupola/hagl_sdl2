SDLFLAGS = $(shell sdl2-config --libs --cflags)

all: demo.c
	gcc -o demo demo.c hagl_hal.c ../hagl/src/rgb565.c ../hagl/src/hagl.c ../hagl/src/clip.c ../hagl/src/bitmap.c ../hagl/src/fontx2.c ../hagl/src/tjpgd.c -I. -I../hagl/include $(SDLFLAGS) -lpng -lz -ljpeg -lfreetype -lm -DNO_MENUCONFIG

clean:
	$(RM) *.o
	$(RM) demo
