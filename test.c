#include "./bonus/cub3d.h"
#include <math.h>

void    calculate_deltas(int start, int end, int *r_s, int *g_s, int *b_s, float *delta_r, float *delta_g, float *delta_b, int pixels)
{

    int r_e;
    int g_e;
    int b_e;

    *r_s = (start >> 16) & 0xFF;
    *g_s = (start >> 8) & 0xFF;
    *b_s = start & 0xFF;

    r_e = (end >> 16) & 0xFF;
    g_e = (end >> 8) & 0xFF;
    b_e = end & 0xFF;

    int steps = pixels - 1;


    *delta_r = (float)(r_e - *r_s) / steps;
    *delta_g = (float)(g_e - *g_s) / steps;
    *delta_b = (float)(b_e - *b_s) / steps;

}


int main()
{
    int color2 = 0xFF0000;
    int color1 = 0x000000;
    int pixels = 10;

    int r_s, r_e;
    int g_s, g_e;
    int b_s, b_e;

    float delta_r;
    float delta_g;
    float delta_b;

    int r;
    int g;
    int b;

    printf("start: %d\n\n", color1);

    calculate_deltas(color1, color2, &r_s, &g_s, &b_s, &delta_r, &delta_g, &delta_b, pixels);

    int t = 0;
    int color = color1;
    while (t < pixels)
    {
        r = (r_s + (t * delta_r));
        g = (g_s + (t * delta_g));
        b = (b_s + (t * delta_b));

        color = (r << 16) | (g << 8) | b;

        printf("color ==> %d\n", color);
        t++;
    }
}