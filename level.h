#pragma once

typedef enum shape {
    square
} shape_t;

struct placeable {
    int x, y;
    shape_t shape;
}

struct light_source {
    int x, y;
}

typedef struct level {
    const char* level_name;
    struct placeable* placeables;
} level_t;

level_t* load_level(const char* filename);
void free_level(level_t* level);