#include <stdio.h>
#include <graphics.h>

void bresenham(int x1, int y1, int x2, int y2)
{
    float x, y, xend;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int p = 2 * dy - dx;
    if (x1 > x2)
    {
        x = x2;
        y = y2;
        xend = x1;
    }
    else
    {
        x = x1;
        y = y1;
        xend = x2;
    }
    putpixel(x, y, 255);
    while (x < xend)
    {
        x++;
        if (p < 0)
            p = p + 2 * dy;
        else
        {
            p = p + 2 * (dy - dx);
            y++;
        }
        putpixel(x, y, 255);
    }
}

int main()
{
    int x1, y1, x2, y2;
    int gd = DETECT, gm;
    printf("Enter first point: (x1, y1)\n");
    scanf("%d%d", &x1, &y1);
    printf("Enter second point: (x2, y2)\n");
    scanf("%d%d", &x2, &y2);
    initgraph(&gd, &gm, NULL);
    bresenham(x1, y1, x2, y2);
    getch();
    closegraph(0);
    return 0;
}