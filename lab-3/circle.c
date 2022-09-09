/*
Midpoint circle drawing algorithm:
1. Read the radius 'r' and center (xc, yc) and obtain first point (x,y) = (0,r)
2. Calculate initial decision parameter p = 1 - r
3. While x <= y, increment x by 1 ie. x++, plot (x,y), and its symmetric points in 7 other octants
    if p < 0; p = p + 2 * x + 3
    else p = p + 2 * (x-y) + 5; y--;
4. End
*/

#include <graphics.h>
#include <stdio.h>

void drawSymmetricPoints(int x, int y, int xc, int yc)
{
    putpixel(x + xc, y + yc, BLACK);
    putpixel(-x + xc, y + yc, BLACK);
    putpixel(-x + xc, -y + yc, BLACK);
    putpixel(x + xc, -y + yc, BLACK);
    putpixel(y + xc, x + yc, BLACK);
    putpixel(-y + xc, x + yc, BLACK);
    putpixel(-y + xc, -x + yc, BLACK);
    putpixel(y + xc, -x + yc, BLACK);
}

void drawcircle(int xc, int yc, int r)
{
    int x = 0, y = r;
    int p = 1 - r;
    do
    {
        drawSymmetricPoints(x, y, xc, yc);
        x++;
        if (p <= 0)
        {
            p = p + 2 * x + 3;
        }
        else
        {
            y--;
            p = p + 2 * x - 2 * y + 5;
        }
    } while (x <= y);
}

int main()
{
    int gd = DETECT, gm;
    int xc, yc, r;
    char debugstr[10];
    printf("Enter center of circle (xc, yc):");
    scanf("%d%d", &xc, &yc);
    printf("Enter radius of circle:");
    scanf("%d", &r);
    initgraph(&gd, &gm, NULL);
    setbkcolor(WHITE);
    cleardevice();
    setcolor(BLACK);
    drawcircle(xc, yc, r);
    sprintf(debugstr, "C program for Midpoint circle drawing algorithm with center (%d, %d) radius %d.", xc, yc, r);
    outtextxy(0, 0, debugstr);
    getch();
    closegraph();
    return 0;
}