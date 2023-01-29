#include <graphics.h>
#include <stdio.h>
#include <math.h>
#define FOV_ANGLE 45
#define CUBE_DISTANCE 10
#define WIDTH 640
#define HEIGHT 480

const int SIDES_OF_POLYGON = 4;
const int POLYGONS_IN_CUBE = 8;
const double angleInRadian = ((double)(FOV_ANGLE) / 180) * M_PI;

struct point2D
{
    double x, y;
};

struct point3D
{
    double x, y, z;
};

struct polygon3D
{
    struct point3D vertices[SIDES_OF_POLYGON];
};

struct polygon2D
{
    struct point2D vertices[SIDES_OF_POLYGON];
};

struct polygon3D cube3D[POLYGONS_IN_CUBE] =
    {
        // bottom
        {.vertices = {{
                          .x = -0.5,
                          .y = 0.5,
                          .z = -0.5,
                      },
                      {
                          .x = 0.5,
                          .y = 0.5,
                          .z = -0.5,
                      },
                      {
                          .x = 0.5,
                          .y = 0.5,
                          .z = 0.5,
                      },
                      {
                          .x = -0.5,
                          .y = 0.5,
                          .z = 0.5,
                      }}},
        // top
        {.vertices = {{
                          .x = -0.5,
                          .y = -0.5,
                          .z = -0.5,
                      },
                      {
                          .x = 0.5,
                          .y = -0.5,
                          .z = -0.5,
                      },
                      {
                          .x = 0.5,
                          .y = -0.5,
                          .z = 0.5,
                      },
                      {
                          .x = -0.5,
                          .y = -0.5,
                          .z = 0.5,
                      }

         }},
        // front
        {.vertices = {{
                          .x = -0.5,
                          .y = -0.5,
                          .z = 0.5,
                      },
                      {
                          .x = 0.5,
                          .y = -0.5,
                          .z = 0.5,
                      },
                      {
                          .x = 0.5,
                          .y = 0.5,
                          .z = 0.5,
                      },
                      {
                          .x = -0.5,
                          .y = 0.5,
                          .z = 0.5,
                      }}},
        // back
        {.vertices = {{
                          .x = -0.5,
                          .y = -0.5,
                          .z = -0.5,
                      },
                      {
                          .x = 0.5,
                          .y = -0.5,
                          .z = -0.5,
                      },
                      {
                          .x = 0.5,
                          .y = 0.5,
                          .z = -0.5,
                      },
                      {
                          .x = -0.5,
                          .y = 0.5,
                          .z = -0.5,
                      }}}};

struct point3D rotate3D(struct point3D point, double yaw, double pitch, double roll)
{
    struct point3D res;
    res.x = cos(yaw) * cos(pitch) * point.x + (cos(yaw) * sin(pitch) * sin(roll) - sin(yaw) * cos(roll)) * point.y + (cos(yaw) * sin(pitch) * cos(roll) + sin(yaw) * sin(roll)) * point.z;
    res.y = sin(yaw) * cos(pitch) * point.x +
            (sin(yaw) * sin(pitch) * sin(roll) + cos(yaw) * cos(roll)) * point.y +
            (sin(yaw) * sin(pitch) * cos(roll) - cos(yaw) * sin(roll)) * point.z;
    res.z = -sin(pitch) * point.x + cos(pitch) * sin(roll) * point.y +
            cos(pitch) * cos(roll) * point.z;
    return res;
}

double transformTo2D(double xy, double z)
{
    return xy / (z * tan(angleInRadian / 2));
}

int main()
{
    int gd = DETECT,
        gm, quit = 0;
    initgraph(&gd, &gm, NULL);
    // yaw - z, pitch - y, roll - x
    double yaw = 0, pitch = 0, roll = 0;
    outtextxy(WIDTH / 4, HEIGHT / 2, (char *)"use 'w' 'a' 's' 'd' 'z' 'x' keys for rotation, 'q' to quit");
    do
    {
        char res = getch();
        switch (res)
        {
        case 'q':
            quit = 1;
            break;
        case 'a':
            pitch += 0.1;
            break;
        case 'w':
            roll -= 0.1;
            break;
        case 'd':
            pitch -= 0.1;
            break;
        case 's':
            roll += 0.1;
            break;
        case 'z':
            yaw -= 0.1;
            break;
        case 'x':
            yaw += 0.1;
            break;
        default:
            break;
        }
        cleardevice();
        // project cube
        struct polygon2D cube2D[POLYGONS_IN_CUBE];
        for (int i = 0; i < POLYGONS_IN_CUBE; i++)
        {
            struct point2D cubeFace[SIDES_OF_POLYGON];
            for (int j = 0; j < SIDES_OF_POLYGON; j++)
            {
                struct point3D point = cube3D[i].vertices[j];
                struct point2D res;
                point = rotate3D(point, yaw, pitch, roll);
                point.z += CUBE_DISTANCE;
                res.x = transformTo2D(point.x, point.z);
                res.y = transformTo2D(point.y, point.z);
                res.x = res.x * WIDTH + WIDTH / 2;
                res.y = res.y * HEIGHT + HEIGHT / 2;
                cubeFace[j] = res;
            }
            memcpy(cube2D[i].vertices, cubeFace, sizeof(cubeFace));
        }
        // draw the cube
        for (int i = 0; i < POLYGONS_IN_CUBE; i++)
        {
            for (int j = 0; j < SIDES_OF_POLYGON; j++)
            {
                // printf("%f, %f\n", cube2D[i].vertices[j].x, cube2D[i].vertices[j].y);
                line(cube2D[i].vertices[j].x, cube2D[i].vertices[j].y, cube2D[i].vertices[(j + 1) % SIDES_OF_POLYGON].x, cube2D[i].vertices[(j + 1) % SIDES_OF_POLYGON].y);
            }
        }
    } while (quit == 0);
    closegraph(0);
    return 0;
}