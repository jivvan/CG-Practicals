// translate a st line between

#include <graphics.h>
#include <stdio.h>

struct point
{
    int x, y;
};

struct point translate(struct point p, int tx, int ty)
{
    int translation_m[3][3] = {
        {1, 0, tx},
        {0, 1, ty},
        {0, 0, 1}};
    int point_m[3] = {p.x, p.y, 1};
    int res[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            res[i] += translation_m[i][j] * point_m[j];
        }
    }
    p.x = res[0];
    p.y = res[1];
    return p;
}

int main()
{
    struct point p1, p2;
    int tx, ty;
    int gd = DETECT, gm;
    char debugstr[10];
    printf("Enter first point: (x1, y1)\n");
    scanf("%d%d", &p1.x, &p1.y);
    printf("Enter second point: (x2, y2)\n");
    scanf("%d%d", &p2.x, &p2.y);
    printf("Enter tx and ty\n");
    scanf("%d%d", &tx, &ty);
    initgraph(&gd, &gm, NULL);
    setbkcolor(WHITE);
    cleardevice();
    setcolor(BLACK);
    line(p1.x, p1.y, p2.x, p2.y);
    struct point p1_translated = translate(p1, tx, ty);
    struct point p2_translated = translate(p2, tx, ty);
    line(p1_translated.x, p1_translated.y, p2_translated.x, p2_translated.y);
    sprintf(debugstr, "C program for translating a line joining (%d, %d) and (%d, %d) by tx = %d, ty = %d", p1.x, p1.y, p2.x, p2.y, tx, ty);
    outtext(debugstr);
    getch();
    closegraph(0);
    return 0;
}