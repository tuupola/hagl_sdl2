/*

MIT No Attribution

Copyright (c) 2019-2023 Mika Tuupola

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
#include "aps.h"
#include "font6x9.h"
#include "backend.h"

hagl_backend_t *backend;
static aps_instance_t pps;

static const uint64_t MS_PER_FRAME_60_FPS = 1000 / 60;

uint32_t
pps_callback(uint32_t interval, void *param)
{
    printf("Primitives per second: %f\n", *(float *)param);
    return interval;
}


void
grid_test()
{
    uint16_t red = hagl_color(backend, 255, 0, 0);
    uint16_t green = hagl_color(backend, 0, 255, 0);
    uint16_t blue = hagl_color(backend, 0, 0, 255);

    hagl_draw_rectangle(backend, 0, 0, backend->width - 1, backend->height - 1, red);
    hagl_draw_hline(backend, 0, 0, backend->width - 1, green);
    hagl_draw_hline(backend, 0, backend->height - 1, backend->width - 1, green);
    hagl_draw_vline(backend, 0, 0, backend->height - 1, green);
    hagl_draw_vline(backend, backend->width - 1, 0, backend->height - 1, green);

    for (int16_t x = 16; x < backend->width; x += 16) {
        hagl_draw_vline(backend, x, 0, backend->height - 1, red);
    }

    for (int16_t y = 16; y < backend->height; y += 16) {
        hagl_draw_hline(backend, 0, y, backend->width - 1, red);
    }
}

void
polygon_demo()
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

    hagl_draw_polygon(backend, 5, vertices, colour);
}

void
fill_polygon_demo()
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

    hagl_fill_polygon(backend, 5, vertices, colour);
}

void
circle_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t r = (rand() % 40);
    uint16_t colour = rand() % 0xffff;

    hagl_draw_circle(backend, x0, y0, r, colour);
}

void
fill_circle_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t r = (rand() % 40);
    uint16_t colour = rand() % 0xffff;

    hagl_fill_circle(backend, x0, y0, r, colour);
}

void
line_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x1 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y1 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t colour = rand() % 0xffff;

    hagl_draw_line(backend, x0, y0, x1, y1, colour);
}

void
rectangle_demo()
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

    hagl_draw_rectangle(backend, x0, y0, x1, y1, colour);
}

void
fill_rectangle_demo()
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

    hagl_fill_rectangle(backend, x0, y0, x1, y1, colour);
}

void
put_character_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t colour = rand() % 0xffff;
    wchar_t ascii = rand() % 127;

    hagl_put_char(backend, ascii, x0, y0, colour, font6x9);
}

void
put_text_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t colour = rand() % 0xffff;

    hagl_put_text(backend, L"YO! MTV raps.", x0, y0, colour, font6x9);
}

void
put_pixel_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t colour = rand() % 0xffff;

    hagl_put_pixel(backend, x0, y0, colour);
}

void
triangle_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x1 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y1 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x2 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y2 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t colour = rand() % 0xffff;

    hagl_draw_triangle(backend, x0, y0, x1, y1, x2, y2, colour);
}

void
fill_triangle_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x1 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y1 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x2 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y2 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t colour = rand() % 0xffff;

    hagl_fill_triangle(backend, x0, y0, x1, y1, x2, y2, colour);
}


void
blit_xywh_demo()
{
    hagl_bitmap_t bitmap;
    bitmap.buffer = (uint8_t *) malloc(6 * 9 * sizeof(hagl_color_t));

    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t colour = rand() % 0xffff;
    wchar_t ascii = rand() % 127;

    if (0 == hagl_get_glyph(backend, ascii, colour, &bitmap, font6x9)) {
        hagl_blit_xywh(backend, x0, y0, 24, 36, &bitmap);
    }
}

void
rgb_demo()
{
    uint16_t red = rgb565(255, 0, 0);
    uint16_t green = rgb565(0, 255, 0);
    uint16_t blue = rgb565(0, 0, 255);
    int16_t x0 = 0;
    int16_t x1 = backend->width / 3;
    int16_t x2 = 2 * x1;

    hagl_fill_rectangle(backend, x0, 0, x1 - 1, backend->height, red);
    hagl_fill_rectangle(backend, x1, 0, x2 - 1, backend->height, green);
    hagl_fill_rectangle(backend, x2, 0, backend->width, backend->height, blue);
}


int
main()
{
    backend = hagl_init();
    srand(time(0));

    uint32_t pps_delay = 2000; /* 0.5 fps */
    uint16_t current_demo = 0;
    float current_pps = 0.0; /* primitives per second */

    SDL_TimerID pps_id;
    pps_id = SDL_AddTimer(pps_delay, pps_callback, &pps.current);

    bool quit = false;
    SDL_Event event;

    void (*demo[15])();
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
    demo[13] = blit_xywh_demo;
    demo[14] = grid_test;

    printf("\n");
    printf("Press any key to change demo.\n");
    printf("Press ESC to quit.\n\n");

    aps_init(&pps);

    uint32_t start = SDL_GetTicks();

    while (!quit) {
        (*demo[current_demo])();
        aps_update(&pps, 1);

        uint32_t end = SDL_GetTicks();
        int32_t delta = MS_PER_FRAME_60_FPS - (end - start);

        if (delta < 0) {
            hagl_flush(backend);
            start = SDL_GetTicks();
        }

        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                if (SDLK_ESCAPE == event.key.keysym.sym) {
                    quit = true;
                } else {
                    aps_reset(&pps);
                    hagl_clear(backend);
                    current_demo = (current_demo + 1) % 15;
                }
            }
        }
    }

    SDL_RemoveTimer(pps_id);
    hagl_close(backend);
    return 0;
}
