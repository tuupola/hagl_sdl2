#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "copepod.h"
#include "pps.h"
#include "font8x8.h"

uint32_t flush_callback(uint32_t interval, void *param)
{
    pod_flush();
    //printf("Primitives per second: %f\n", *(float *)param);
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
    pod_polygon(5, vertices, colour);
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
    pod_fillpolygon(5, vertices, colour);
}

void circle_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t r = (rand() % 40);
    uint16_t colour = rand() % 0xffff;
    pod_circle(x0, y0, r, colour);
}

void fill_circle_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t r = (rand() % 40);
    uint16_t colour = rand() % 0xffff;
    pod_fillcircle(x0, y0, r, colour);
}

void line_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */
    int16_t x1 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y1 = (rand() % 280) - 20; /* -20 ... 260 */
    uint16_t colour = rand() % 0xffff;
    pod_line(x0, y0, x1, y1, colour);
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
    pod_rectangle(x0, y0, x1, y1, colour);
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
    pod_fillrectangle(x0, y0, x1, y1, colour);
}

void put_character_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */

    uint16_t colour = rand() % 0xffff;
    char ascii = rand() % 127;
    pod_putchar(ascii, x0, y0, colour, font8x8_basic);
}

void put_text_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */

    uint16_t colour = rand() % 0xffff;
    pod_puttext("YO! MTV Raps", x0, y0, colour, font8x8_basic);
}

void put_pixel_demo()
{
    int16_t x0 = (rand() % 360) - 20; /* -20 ... 340 */
    int16_t y0 = (rand() % 280) - 20; /* -20 ... 260 */

    uint16_t colour = rand() % 0xffff;
    pod_putpixel(x0, y0, colour);
}

int main()
{
    pod_init();
    pod_clip_window(0, 30, 319, 210);
    srand(time(0));

    uint32_t flush_delay = 1000 / 30; /* 30 fps */
    uint32_t pps_delay = 2000; /* 0.5 fps */
    uint16_t demo = 1;
    float current_pps = 0.0; /* primitives per secod */

    SDL_TimerID flush_id = SDL_AddTimer(flush_delay, flush_callback, NULL);
    SDL_TimerID pps_id = SDL_AddTimer(pps_delay, pps_callback, &current_pps);

    bool quit = false;
    SDL_Event event;

    while (!quit) {

        if (0 == demo % 10) {
            put_pixel_demo();
        } else if (0 == demo % 9) {
            put_text_demo();
        } else if (0 == demo % 8) {
            put_character_demo();
        } else if (0 == demo % 7) {
            fill_rectangle_demo();
        } else if (0 == demo % 6) {
            rectangle_demo();
        } else if (0 == demo % 5) {
            line_demo();
        } else if (0 == demo % 4) {
            circle_demo();
        } else if (0 == demo % 3) {
            fill_circle_demo();
        } else if (0 == demo % 2) {
            polygon_demo();
        } else if (0 == demo % 1) {
            fill_polygon_demo();
        }

        current_pps = pps(false);

        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                current_pps = pps(true);
                demo = demo + 1;
                printf("Demo is now: %d\n", demo);

            }
        }

        //SDL_Delay(500);
    }

    SDL_RemoveTimer(flush_id);
    SDL_RemoveTimer(pps_id);
    pod_destroy();
    return 0;
}

int xmain()
{
    uint16_t max_x = 320;
    uint16_t max_y = 280;
    uint16_t max_iters = 1028;

    uint16_t n = 0;
    uint16_t px;
    uint16_t py;

    double x;
    double y;
    double x0;
    double y0;
    double xx;
    double yy;
    double xtemp;

    double zoom = 1.0;

    clock_t start;
    clock_t end;
    double time_spent;

    pod_init();

    start = clock();

    for (py = 1; py <= max_y; py++)  {
        for (px = 1; px <= max_x; px++)  {
            x0 = (((float) px) / ((float) max_x) - 0.5) / zoom * 3.0 - 0.7;
            y0 = (((float) py) / ((float) max_y) - 0.5) / zoom * 3.0;
            x = 0.0;
            y = 0.0;
            n = 0;

            xx = x * x;
            yy = y * y;

            while ((x * x + y * y < 4) && (n != max_iters)) {
                xtemp = x * x - y * y + x0;
                y = 2.0 * x * y + y0;
                x = xtemp;
                n++;
            }

            // while ((xx + yy < 4) && (n != max_iters)) {
            //     y = (x + x) * y + y0;
            //     x = xx - yy + x0;

            //     xx = x * x;
            //     yy = y * y;
            //     n++;
            // }

            if (n < max_iters) {
                pod_putpixel(px, py, n);
            } else {
                pod_putpixel(px, py, 0);
            }
        }
    }

    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Generated in %g seconds.\n", time_spent);
    pod_flush();

    return 0;
}

