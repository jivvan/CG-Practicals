#include <graphics.h>
#include <stdio.h>

void dda(int x1, int y1, int x2, int y2)
{
    int step;
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (abs(dx) >= abs(dy))
    {
        step = abs(dx);
    }
    else
    {
        step = abs(dy);
    }
    float xinc = (float)dx / step;
    float yinc = (float)dy / step;
    float x = x1, y = y1;
    putpixel(x, y, 255);
    for (int k = 0; k < step; k++)
    {
        x += xinc;
        y += yinc;
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
    dda(x1, y1, x2, y2);
    getch();
    closegraph(0);
    return 0;
}