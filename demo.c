/*

MIT No Attribution

Copyright (c) 2019-2020 Mika Tuupola

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-cut-

SPDX-License-Identifier: MIT-0

*/
#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "hagl_hal.h"
#include "hagl.h"
#include "rgb565.h"
#include "fps.h"
#include "font6x9.h"

uint32_t flush_callback(uint32_t interval, void *param)
{
    hagl_flush();
    return interval;
}

uint32_t pps_callback(uint32_t interval, void *param)
{
    printf("Primitives per second: %f\n", *(float *)param);
    return interval;
}

void polygon_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x1 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y1 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x2 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y2 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x3 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y3 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x4 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y4 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t colour = rand() % 0xffff;
    int16_t vertices[10] = {x0, y0, x1, y1, x2, y2, x3, y3, x4, y4};

    hagl_draw_polygon(5, vertices, colour);
}

void fill_polygon_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x1 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y1 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x2 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y2 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x3 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y3 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x4 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y4 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t colour = rand() % 0xffff;
    int16_t vertices[10] = {x0, y0, x1, y1, x2, y2, x3, y3, x4, y4};

    hagl_fill_polygon(5, vertices, colour);
}

void circle_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t r = (rand() % 40);
    uint16_t colour = rand() % 0xffff;

    hagl_draw_circle(x0, y0, r, colour);
}

void fill_circle_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t r = (rand() % 40);
    uint16_t colour = rand() % 0xffff;

    hagl_fill_circle(x0, y0, r, colour);
}

void line_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x1 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y1 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t colour = rand() % 0xffff;

    hagl_draw_line(x0, y0, x1, y1, colour);
}

void rectangle_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x1 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y1 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x2 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y2 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x3 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y3 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x4 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y4 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t colour = rand() % 0xffff;

    hagl_draw_rectangle(x0, y0, x1, y1, colour);
}

void fill_rectangle_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x1 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y1 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x2 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y2 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x3 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y3 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x4 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y4 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t colour = rand() % 0xffff;

    hagl_fill_rectangle(x0, y0, x1, y1, colour);
}

void put_character_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t colour = rand() % 0xffff;
    char ascii = rand() % 127;

    hagl_put_char(ascii, x0, y0, colour, font6x9);
}

void put_text_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t colour = rand() % 0xffff;

    hagl_put_text(u"YO! MTV raps.", x0, y0, colour, font6x9);
}

void put_pixel_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t colour = rand() % 0xffff;

    hagl_put_pixel(x0, y0, colour);

}

void triangle_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x1 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y1 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x2 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y2 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t colour = rand() % 0xffff;

    hagl_draw_triangle(x0, y0, x1, y1, x2, y2, colour);
}

void fill_triangle_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x1 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y1 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x2 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y2 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t colour = rand() % 0xffff;

    hagl_fill_triangle(x0, y0, x1, y1, x2, y2, colour);
}

void scale_blit_demo()
{
}

void rgb_demo()
{
    uint16_t red = rgb565(255, 0, 0);
    uint16_t green = rgb565(0, 255, 0);
    uint16_t blue = rgb565(0, 0, 255);
    int16_t x0 = 0;
    int16_t x1 = DISPLAY_WIDTH / 3;
    int16_t x2 = 2 * x1;

    hagl_fill_rectangle(x0, 0, x1 - 1, DISPLAY_HEIGHT, red);
    hagl_fill_rectangle(x1, 0, x2 - 1, DISPLAY_HEIGHT, green);
    hagl_fill_rectangle(x2, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, blue);
}

int main()
{
    hagl_init();
    //pod_set_clip_window(0, 30, 319, 210);
    srand(time(0));

    uint32_t flush_delay = 1000 / 30; /* 30 fps */
    uint32_t pps_delay = 2000; /* 0.5 fps */
    uint16_t current_demo = 0;
    float current_pps = 0.0; /* primitives per secod */

    SDL_TimerID flush_id = SDL_AddTimer(flush_delay, flush_callback, NULL);
    SDL_TimerID pps_id = SDL_AddTimer(pps_delay, pps_callback, &current_pps);

    bool quit = false;
    SDL_Event event;

    void (*demo[13]) ();
    demo[0] = rgb_demo;
    demo[1] = put_character_demo;
    demo[2] = put_pixel_demo;
    demo[3] = fill_triangle_demo;
    demo[4] = triangle_demo;
    demo[5] = fill_rectangle_demo;
    demo[6] = rectangle_demo;
    demo[7] = line_demo;
    demo[8] = circle_demo;
    demo[9] = fill_circle_demo;
    demo[10] = polygon_demo;
    demo[11] = fill_polygon_demo;
    demo[12] = put_text_demo;

    printf("\n");
    printf("Press any key to change demo.\n");
    printf("Press ESC to quit.\n\n");

    while (!quit) {

        (*demo[current_demo])();
        current_pps = fps();
        //SDL_Delay(100);
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                if (SDLK_ESCAPE ==event.key.keysym.sym) {
                    quit = true;
                } else {
                    //fps_reset();
                    hagl_clear_screen();
                    current_demo = (current_demo + 1) % 12;
                }
            }
        }
    }

    SDL_RemoveTimer(flush_id);
    SDL_RemoveTimer(pps_id);
    hagl_close();
    return 0;
}
