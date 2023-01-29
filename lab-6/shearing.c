#include <graphics.h>
#include <stdio.h>
#define VERTICES 4

struct point
{
    float x, y;
};

void drawRectangle(struct point r[VERTICES])
{
    for (int i = 0; i < VERTICES; i++)
        line(r[i].x, r[i].y, r[(i + 1) % VERTICES].x, r[(i + 1) % VERTICES].y);
}

void xShear(struct point r[VERTICES], float shx)
{
    struct point rect[VERTICES];
    memcpy(rect, r, VERTICES * sizeof(struct point));
    for (int i = 0; i < VERTICES; i++)
        rect[i].x += rect[i].y * shx;
    drawRectangle(rect);
}

void yShear(struct point r[VERTICES], float shy)
{
    struct point rect[VERTICES];
    memcpy(rect, r, VERTICES * sizeof(struct point));
    for (int i = 0; i < VERTICES; i++)
        rect[i].y += rect[i].x * shy;
    drawRectangle(rect);
}

void xyShear(struct point r[VERTICES], float shx, float shy)
{
    struct point rect[VERTICES];
    memcpy(rect, r, VERTICES * sizeof(struct point));
    for (int i = 0; i < VERTICES; i++)
    {
        rect[i].x += r[i].y * shx;
        rect[i].y += r[i].x * shy;
    }
    drawRectangle(rect);
}

int main()
{
    int gd = DETECT, gm;
    float shx, shy;
    struct point rectangle[VERTICES];
    printf("Enter vertices of rectangle:\n");
    for (int i = 0; i < VERTICES; i++)
    {
        printf("%c(x,y): ", 65 + i);
        scanf("%f%f", &rectangle[i].x, &rectangle[i].y);
    }
    printf("Enter shearing factors shx, shy");
    scanf("%f%f", &shx, &shy);
    initgraph(&gd, &gm, NULL);
    drawRectangle(rectangle);
    xShear(rectangle, shx);
    yShear(rectangle, shy);
    xyShear(rectangle, shx, shy);
    getch();
    closegraph(0);
    return 0;
}