/*

MIT License

Copyright (c) 2019-2023 Mika Tuupola

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
#include <hagl/bitmap.h>
#include <hagl/backend.h>
#include <hagl/window.h>

#include "hagl_hal.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

static hagl_bitmap_t bb;

static void
put_pixel(void *self, int16_t x0, int16_t y0, hagl_color_t color)
{
    /* Bitmap already provides a put pixel function. */
    bb.put_pixel(&bb, x0, y0, color);
}

static hagl_color_t
get_pixel(void *self, int16_t x0, int16_t y0)
{
    /* Bitmap already provides a get pixel function. */
    return bb.get_pixel(&bb, x0, y0);
}

/*
 * Flushes the back buffer to the SDL2 window
 */
static size_t
flush(void *self)
{
    SDL_UpdateTexture(texture, NULL, bb.buffer, bb.pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    return bb.size;
}

static void
close(void *self)
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

static hagl_color_t
color(void *self, uint8_t r, uint8_t g, uint8_t b)
{
    hagl_color_t color = rgb565(r, g, b);
    return (color >> 8) | (color << 8);
}

void
hagl_hal_init(hagl_backend_t *backend)
{
    if (!backend->buffer) {
        backend->buffer = calloc(HAGL_SDL2_DISPLAY_WIDTH * HAGL_SDL2_DISPLAY_HEIGHT * (HAGL_SDL2_DISPLAY_DEPTH / 8), sizeof(uint8_t));
        printf("Allocated back buffer to address %p.\n", (void *) backend->buffer);
    } else {
        printf("Using provided back buffer at address %p.\n", (void *) backend->buffer);
    }

    backend->width = HAGL_SDL2_DISPLAY_WIDTH;
    backend->height = HAGL_SDL2_DISPLAY_HEIGHT;
    backend->depth = HAGL_SDL2_DISPLAY_DEPTH;
    backend->put_pixel = put_pixel;
    backend->get_pixel = get_pixel;
    backend->color = color;

    backend->flush = flush;
    backend->close = close;

    hagl_bitmap_init(&bb, backend->width, backend->height, backend->depth, backend->buffer);

    if (0 > SDL_Init(SDL_INIT_EVERYTHING)) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());

    };
    if (0 > SDL_CreateWindowAndRenderer(HAGL_SDL2_DISPLAY_WIDTH, HAGL_SDL2_DISPLAY_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer)) {
        printf("Could not create window and renderer: %s\n", SDL_GetError());
    };

    texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGB565,
            SDL_TEXTUREACCESS_STATIC,
            HAGL_SDL2_DISPLAY_WIDTH,
            HAGL_SDL2_DISPLAY_HEIGHT
        );

    if (NULL == texture) {
        printf("Could not create texture: %s\n", SDL_GetError());
    }
}