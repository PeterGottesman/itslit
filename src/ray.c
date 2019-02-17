#include "ray.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "defs.h"

point_t* cast_ray(float x_src, float y_src, float x_dest, float y_dest) {
    float dx = x_dest - x_src;
    float dy = y_dest - y_src;

    float magnitude = sqrt(dx*dx + dy*dy);

    point_t* point = malloc(sizeof(point_t));

    if (magnitude < 0.0001) {
        point->x = x_src;
        point->y = y_src;
        return point;
    }

    dx /= magnitude;
    dy /= magnitude;

    float xn = x_src;
    float yn = y_src;

    while (1) {
        if (xn < 0 || yn < 0 || xn > WIDTH || yn > HEIGHT)
            break;
        
        xn += dx;
        yn += dy;
        printf("%f, %f\n", xn, yn);
    }

    point->x = xn;
    point->y = yn;
    
    return point;
}

float calculate_angle(float x_src, float y_src, float x_dest, float y_dest) {
    float dx = x_dest - x_src;
    float dy = y_dest - y_src;
    return atan2(dy, dx);
}

point_t* compile_point(light_source_t* light_source, float x, float y) {
    point_t* point = cast_ray(light_source->x, light_source->y, x, y);
    point-> angle = calculate_angle(light_source->x, light_source->y, x, y);
    return point;
}

point_t* sort_points(point_t* points, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (points[j].angle > points[j+1].angle) {
                point_t temp = points[j];
                points[j] = points[j + 1];
                points[j + 1] = temp;
            }
        }
    }
    return points;
}
