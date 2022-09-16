#include <graphics.h>
#include <stdio.h>
#include <math.h>

#define SIN(x) sin(x * 3.141592653589 / 180)
#define COS(x) cos(x * 3.141592653589 / 180)

struct point
{
    int x, y;
};

struct point rotate(struct point p, struct point center, float angle)
{
    double rotation_m[3][3] = {
        {COS(angle), -SIN(angle), center.x * (1 - COS(angle)) + center.y * SIN(angle)},
        {SIN(angle), COS(angle), center.y * (1 - COS(angle)) - center.x * SIN(angle)},
        {0, 0, 1}};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%f\t", rotation_m[i][j]);
        }
        printf("\n");
    }
    int point_m[3] = {p.x, p.y, 1};
    int res[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            res[i] += int(rotation_m[i][j] * (float)point_m[j]);
        }
    }
    p.x = res[0];
    p.y = res[1];
    return p;
}

int main()
{
    struct point p1, p2, center;
    float angle;
    int gd = DETECT, gm;
    char debugstr[10];
    printf("Enter first point: (x1, y1)\n");
    scanf("%d%d", &p1.x, &p1.y);
    printf("Enter second point: (x2, y2)\n");
    scanf("%d%d", &p2.x, &p2.y);
    printf("Enter center of rotation: (xr, yr)\n");
    scanf("%d%d", &center.x, &center.y);
    printf("Enter angle:\n");
    scanf("%f", &angle);
    initgraph(&gd, &gm, NULL);
    setbkcolor(WHITE);
    cleardevice();
    setcolor(BLACK);
    line(p1.x, p1.y, p2.x, p2.y);
    struct point p1_rotated = rotate(p1, center, angle);
    struct point p2_rotated = rotate(p2, center, angle);
    line(p1_rotated.x, p1_rotated.y, p2_rotated.x, p2_rotated.y);
    sprintf(debugstr, "C program for rotating a line joining (%d, %d) and (%d, %d) w.r.t (%d, %d) by angle=%f", p1.x, p1.y, p2.x, p2.y, center.x, center.y, angle);
    outtext(debugstr);
    getch();
    closegraph(0);
    return 0;
}