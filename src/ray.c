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

point_t* egde_ray(point_t* point) {
    float r = sqrt(point->x*point->x + point->y*point->y);

    float left_angle = (point->angle - 0.00001)*(180/PI);
    float left_x = r * cos(left_angle);
    float left_y = r * sin(left_angle);
    point_t left_ray;
    left_ray.x = left_x;
    left_ray.y = left_y;
    
    float right_angle = (point->angle + 0.00001) * (180/PI);
    float right_x = r * cos(right_angle);
    float right_y = r * sin(right_angle);
    point_t right_ray;
    right_ray.x = right_x;
    right_ray.y = right_y;

    point_t* edge_rays = malloc(sizeof(point_t)*2);
    edge_rays[0] = left_ray;
    edge_rays[1] = right_ray;

    return edge_rays;
}