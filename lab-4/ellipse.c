/*
    Midpoint Ellipse Algorithm
    1. Input rx, ry and ellipse center (xc, yc) andobtain the first point on an ellipse centered on origin as:
        (x, y) = (0, ry)
    2. Calculate the initial value of the decision parameter in region 1 as:
        p1 = pow(ry, 2) - pow(rx, 2)*ry + (1/4)*pow(rx, 2)
    3. While 2*pow(ry,2)*x >= 2*pow(rx,2)*y:
        if p1 < 0:
            - (x, y) = (x + 1, y)
            - p1 = p1 + 2 * pow(ry,2)* x + pow(ry, 2)
        else:
            - (x, y) = (x+1, y-1)
            - p1 = p1 + 2 * pow(ry, 2)* x - 2* pow(rx, 2)*y + pow(ry, 2)
    4. Calculate inital decision parameter for region 2 using last point in region 1:
        p2 = pow(ry, 2)*pow((x + 1/2), 2) + pow(rx, 2) * pow((y -1), 2) - rx*rx*ry*ry;
    5. While x <= rx:
        if p2 > 0:
            - (x, y) = (x, y-1)
            - p2 = p2 - 2 * ry * ry * y + rx * rx
        else:
            - (x, y) = (x+1, y-1)
            - p2 = p2 + 2 * ry * ry * x - 2 * rx * rx * y + rx * rx
    6. Detrmine symmetrical points for all other three quadrants
    7. Move each calculated pixel position (x, y) into elliptical path centered at (xc, yc)
    8. Plot
*/

#include <graphics.h>
#include <stdio.h>
#include <math.h>

void drawSymmetricPoints(int x, int y, int xc, int yc)
{
    putpixel(x + xc, y + yc, BLACK);
    putpixel(-x + xc, y + yc, BLACK);
    putpixel(-x + xc, -y + yc, BLACK);
    putpixel(x + xc, -y + yc, BLACK);
}

void drawellipse(int xc, int yc, int rx, int ry)
{
    int x = 0, y = ry;
    float p1 = (ry * ry) - (rx * rx * ry) + (0.25);
    do
    {
        drawSymmetricPoints(x, y, xc, yc);
        if (p1 < 0)
        {
            x++;
            p1 = p1 + 2 * ry * ry * x + ry * ry;
        }
        else
        {
            x++;
            y--;
            p1 = p1 + 2 * ry * ry * x - 2 * rx * rx * y + ry * ry;
        }
    } while (2 * ry * ry * x < 2 * rx * rx * y);
    int p2 = pow(ry, 2) * pow((x + 0.5), 2) + pow((y - 1), 2) * rx * rx - rx * rx * ry * ry;
    do
    {
        drawSymmetricPoints(x, y, xc, yc);
        if (p2 > 0)
        {
            y--;
            p2 = p2 - 2 * rx * rx * y + rx * rx;
        }
        else
        {
            x++;
            y--;
            p2 = p2 + 2 * ry * ry * x - 2 * rx * rx * y + rx * rx;
        }
    } while (y >= 0);
}

int main()
{
    int gd = DETECT, gm;
    int xc, yc, rx, ry;
    char debugstr[10];
    printf("Enter center of ellipse (xc, yc):");
    scanf("%d%d", &xc, &yc);
    printf("Enter radii of ellipse (rx, ry):");
    scanf("%d%d", &rx, &ry);
    initgraph(&gd, &gm, NULL);
    setbkcolor(WHITE);
    cleardevice();
    setcolor(BLACK);
    drawellipse(xc, yc, rx, ry);
    sprintf(debugstr, "C program for Midpoint ellipse drawing algorithm with center (%d, %d) radii rx = %d, ry = %d.", xc, yc, rx, ry);
    outtextxy(0, 0, debugstr);
    getch();
    closegraph();
    return 0;
}