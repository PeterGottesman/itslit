#pragma once

typedef enum shape {
    SQUARE
} shape_t;

typedef struct placeable {
    int x, y;
    shape_t shape;
} placeable_t;

typedef struct light_source {
    int x, y;
} light_source_t;

typedef struct level {
    const char* level_name;
    struct placeable* placeables;
    int num_placeables;
    struct light_source* light_sources;
    int num_light_sources;
} level_t;

level_t* load_level(const char* filename);
void free_level(level_t* level);