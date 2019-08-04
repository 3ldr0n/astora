#ifndef MAP_H
#define MAP_H

#include <string.h>

struct map_element {
    char *key;
    void *value;
};

struct map {
    size_t size;
    struct map_element **elements;
};

void map_new(struct map *map, const size_t size);
void map_delete(struct map *map);
int map_insert(struct map *map, const char *key, void *value);
void* map_search(struct map *map, const char *key);
void map_delete_key(struct map *map, const char *key);

#endif
