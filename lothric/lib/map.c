#include <math.h>

#include "lib/map.h"
#include "lib/commons.h"

/**
 *
 */
static struct map_element *map_new_element(const char *key, void *value)
{
    struct map_element *new_item = smalloc(sizeof(struct map_element));
    new_item->key = strdup(key);
    new_item->value = value;
    return new_item;
}

/**
 *
 */
void map_new(struct map *map, const size_t size)
{
    if (size == 0)
        return;

    map = smalloc(sizeof(struct map));
    map->elements = (struct map_element **)smalloc(size * sizeof(struct map_element));
    memset(map->elements, 0, size * sizeof(struct map_element));
    map->size = size;
}

/**
 *
 */
static void map_delete_element(struct map_element *item)
{
    free(item->key);
    free(item->value);
    free(item);
}

/**
 *
 */
void map_delete(struct map *map)
{
    if (map->elements == NULL)
        return;

    for (unsigned int i = 0;i < map->size;i++) {
        struct map_element *item = map->elements[i];
        if (item != NULL)
            map_delete_element(item);
    }
    free(map->elements);
    free(map);
}

/**
 *
 */
static unsigned int hash(const char *key, const size_t map_size)
{
    unsigned int hash = 0;
    unsigned int i = 0;
    while (key && key[i]) {
        hash = (hash + key[i]) % map_size;
        ++i;
    }

    return hash;
}

/**
 *
 */
int map_insert(struct map *map, const char *key, void *value)
{
    if (map == NULL)
        return 1;

    struct map_element *element = map_new_element(key, value);

    unsigned int index = hash(element->key, map->size);
    struct map_element *tmp = map->elements[index];

    if (tmp == NULL) {
        map->elements[index] = element;
        return 0;
    }

    return 0;
}
