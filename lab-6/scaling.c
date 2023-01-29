#include <graphics.h>
#include <stdio.h>

struct point
{
    int x, y;
};

void drawTriangle(struct point triangle[3])
{
    for (int i = 0; i < 3; i++)
    {
        line(triangle[i].x, triangle[i].y, triangle[(i + 1) % 3].x, triangle[(i + 1) % 3].y);
    }
}

int main()
{
    int gd = DETECT, gm, sx, sy;
    struct point triangle[3];
    printf("Enter vertices of triangle:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("%c(x,y) = ", 65 + i);
        scanf("%d%d", &triangle[i].x, &triangle[i].y);
    }
    printf("Enter scaling factors sx, sy:");
    scanf("%d%d", &sx, &sy);
    initgraph(&gd, &gm, NULL);
    drawTriangle(triangle);
    for (int i = 0; i < 3; i++)
    {
        triangle[i].x *= sx;
        triangle[i].y *= sy;
    }
    drawTriangle(triangle);
    getch();
    closegraph(0);
    return 0;
}
