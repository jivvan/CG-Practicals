// reflect a triangle with vertices A(100,100), B(200,100) and C(150,150) wrt a st line y = 5x + 100

#include <stdio.h>
#include <graphics.h>

struct point
{
    int x, y;
};

struct point reflect(struct point p, float m, float c)
{
    int point_m[3] = {p.x, p.y, 1};
    float div = m * m + 1;
    float reflection_m[3][3] = {
        {((1 - m * m) / div), ((2 * m) / div), ((-2 * m * c) / div)},
        {((2 * m) / div), ((m * m - 1) / div), ((2 * c) / div)},
        {0, 0, 1}};
    int res[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            res[i] += int(reflection_m[i][j] * (float)point_m[j]);
        }
    }
    p.x = res[0];
    p.y = res[1];
    return p;
}

int main()
{
    struct point A, B, C;
    float c, m;
    int gd = DETECT, gm;
    char debugstr[10];
    printf("Enter first point: (x1, y1)\n");
    scanf("%d%d", &A.x, &A.y);
    printf("Enter second point: (x2, y2)\n");
    scanf("%d%d", &B.x, &B.y);
    printf("Enter third point: (x3, y3)\n");
    scanf("%d%d", &C.x, &C.y);
    printf("Enter slope m and c\n");
    scanf("%f%f", &m, &c);
    initgraph(&gd, &gm, NULL);
    setbkcolor(WHITE);
    cleardevice();
    setcolor(BLACK);

    line(A.x, A.y, B.x, B.y);
    line(B.x, B.y, C.x, C.y);
    line(C.x, C.y, A.x, A.y);

    struct point AR = reflect(A, m, c);
    struct point BR = reflect(B, m, c);
    struct point CR = reflect(C, m, c);

    line(AR.x, AR.y, BR.x, BR.y);
    line(BR.x, BR.y, CR.x, CR.y);
    line(CR.x, CR.y, AR.x, AR.y);

    line(0, c, 500, 500 * m + c);

    sprintf(debugstr, "C program for reflecting a triangle A(%d, %d), B(%d, %d), C(%d, %d) wrt line y=%.2fx + %.2f.", A.x, A.y, B.x, B.y, C.x, C.y, m, c);
    outtextxy(5, 5, debugstr);
    getch();
    closegraph(0);
    return 0;
}