#include "level.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

level_t* load_level(const char* filename) {
    level_t* level = malloc(sizeof(level_t));
    
    FILE *fp;
    char line[100];

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("File could not be opened.");
    }

    fgets(line, 100, fp);
    level->level_name = strdup(line);
    fgets(line, 100, fp);
    int light_source_count = atoi(line);
    fgets(line, 100, fp);
    int placeable_count = atoi(line);

    level->light_sources = malloc(sizeof(light_source_t) * light_source_count);

    for (int i = 0; i < light_source_count; ++i) {
        light_source_t light_source;
        fgets(line, 100, fp);
        int x = atoi(line);
        fgets(line, 100, fp);
        int y = atoi(line);
        level->light_sources[i].x = x;
        level->light_sources[i].y = y;
    }

    level->placeables = malloc(sizeof(placeable_t) * placeable_count);

    for (int i = 0; i < placeable_count; ++i) {
        placeable_t placeable;
        fgets(line, 100, fp);
        level->placeables[i].x = -1;
        level->placeables[i].y = -1;
        level->placeables[i].shape = SQUARE;
    }

   fclose(fp);

   return level;
}