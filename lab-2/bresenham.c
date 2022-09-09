#include <stdio.h>
#include <graphics.h>

void drawline(int x1, int y1, int x2, int y2)
{
    int x = x1, y = y1;
    int dx = x2 - x1, dy = y2 - y1;
    int p = 2 * dx - dy;
    while (x <= x2)
    {
        putpixel(x, y, BLACK);
        x++;
        if (p < 0)
        {
            p = p + 2 * dy;
        }
        else
        {
            p = p + 2 * dy - 2 * dx;
            y++;
        }
    }
}

int main()
{
    int gd = DETECT, gm;
    int x1, y1, x2, y2;
    char debugstr[10];
    printf("Enter first coordinate (x1, y1):");
    scanf("%d%d", &x1, &y1);
    printf("Enter second coordinate (x2, y2):");
    scanf("%d%d", &x2, &y2);
    initgraph(&gd, &gm, NULL);
    setbkcolor(WHITE);
    cleardevice();
    setcolor(BLACK);
    drawline(x1, y1, x2, y2);
    sprintf(debugstr, "C program for Bresenham's Algorithm joining points (%d, %d) and (%d, %d)", x1, y1, x2, y2);
    outtextxy(0, 0, debugstr);
    getch();
    closegraph();
    return 0;
}