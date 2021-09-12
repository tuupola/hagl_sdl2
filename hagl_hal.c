/*

MIT License

Copyright (c) 2019-2021 Mika Tuupola

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-cut-

This file is part of the SDL2 HAL for the HAGL graphics library:
https://github.com/tuupola/hagl_sdl2

SPDX-License-Identifier: MIT

*/

#include <stdint.h>
#include <stdbool.h>
#include <rgb565.h>
#include <SDL2/SDL.h>
#include <bitmap.h>
#include <window.h>

#include "hagl_hal.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

static bitmap_t bb = {
    .width = DISPLAY_WIDTH,
    .height = DISPLAY_HEIGHT,
    .depth = DISPLAY_DEPTH,
};

static window_t dirty = {
    .x0 = DISPLAY_WIDTH - 1,
    .y0 = DISPLAY_HEIGHT - 1,
    .x1 = 0,
    .y1 = 0,
};

void hagl_hal_put_pixel(int16_t x0, int16_t y0, color_t color)
{
    color_t *ptr = (color_t *) (bb.buffer + bb.pitch * y0 + (bb.depth / 8) * x0);
    *ptr = color;

    /* Tracking dirty window is not needed by HAGL. Below code is included */
    /* as an example if you want to iplement it in your HAL. */
    dirty.x0 = min(dirty.x0, x0);
    dirty.x1 = max(dirty.x1, x0);
    dirty.y0 = min(dirty.y0, y0);
    dirty.y1 = max(dirty.y1, y0);
}

color_t hagl_hal_get_pixel(int16_t x0, int16_t y0)
{
    return *(color_t *) (bb.buffer + bb.pitch * y0 + (bb.depth / 8) * x0);
}

bitmap_t *hagl_hal_init(void)
{
    static uint8_t buffer[BITMAP_SIZE(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_DEPTH)];
    bitmap_init(&bb, buffer);

    if ((window != NULL) && (renderer != NULL)) {
        return NULL;
    }

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    window = SDL_CreateWindow(
        "HAGL SDL2",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        DISPLAY_WIDTH,
        DISPLAY_HEIGHT,
        0
    );

    if (NULL == window) {
        printf("Could not create window: %s\n", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (NULL == renderer) {
        printf("Could not create renderer: %s\n", SDL_GetError());
    }

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGB565,
        SDL_TEXTUREACCESS_STATIC,
        DISPLAY_WIDTH,
        DISPLAY_HEIGHT
    );

    if (NULL == texture) {
        printf("Could not create texture: %s\n", SDL_GetError());
    }

    return &bb;
}

/*
 * Flushes the back buffer to the SDL2 window
 */
size_t hagl_hal_flush()
{
    /* Check whether something has been drawn already */
    if (dirty.y1 < dirty.y0) {
        return 0;
    }

    SDL_UpdateTexture(texture, NULL, bb.buffer, bb.pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    // printf("Dirty %d,%d %d,%d (%d,%d)\n",
    //     dirty.x0,
    //     dirty.y0,
    //     dirty.x1,
    //     dirty.y1,
    //     dirty.x1 - dirty.x0 + 1,
    //     dirty.y1 - dirty.y0 + 1
    // );

    /* Reset dirty window */
    dirty.x0 = DISPLAY_WIDTH - 1;
    dirty.x1 = 0;
    dirty.y0 = DISPLAY_HEIGHT - 1;
    dirty.y1 = 0;

    return DISPLAY_WIDTH * DISPLAY_HEIGHT * DISPLAY_DEPTH / 2;
}

void hagl_hal_close(void)
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

color_t hagl_hal_color(uint8_t r, uint8_t g, uint8_t b)
{
    color_t color = rgb565(r, g, b);
    return (color >> 8) | (color << 8);
}