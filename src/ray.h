#include "level.h"
#include <stdbool.h>

#pragma once

typedef struct point {
    float x, y;
    float angle;
} point_t;

point_t cast_ray(float x_src, float y_src, float x_dest, float y_dest, int trx, int try);
float calculate_angle(float x_src, float y_src, float x_dest, float y_dest);
point_t compile_point(light_source_t* light_source, float x, float y);
point_t* sort_points(point_t* points, int n);
point_t* edge_ray(point_t* point);
bool has_collided(int top_right_x, int top_right_y, int ray_x, int ray_y);
