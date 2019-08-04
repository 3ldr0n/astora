#include "lib/map.h"

#include <math.h>

static void *smalloc(const size_t size)
{
    if (!size)
        return NULL;

    void *mem = malloc(size);

    if (!mem) {
        fprintf(stderr, "Fatal: Memory allocation error(%zu bytes malloc)\n", size);
        exit(EXIT_FAILURE);
    }

    return mem;
}

static void *scalloc(const size_t nitems, const size_t size)
{
    if (!size)
        return NULL;

    void *mem = calloc(nitems, size);

    if (!mem) {
        fprintf(stderr, "Fatal: Memory allocation error (%zu bytes calloc)\n", size);
        exit(EXIT_FAILURE);
    }

    return mem;
}

static struct map_element *new_map_element(const char *key, void *value)
{
    struct map_element *new_item = smalloc(sizeof(struct map_element));
    new_item->key = strdup(key);
    new_item->value = value;
    return new_item;
}

void map_new(struct map *map)
{
    map = smalloc(sizeof(struct map));
    map->max_size = 50;
    map->size = 0;
    map->elements = scalloc(map->max_size, sizeof(struct map_element *));
}

static void map_delete_element(struct map_element *item)
{
    free(item->key);
    free(item->value);
    free(item);
}

void map_delete(struct map *map)
{
    if (map->elements == NULL)
        return;

    for (uint i = 0;i < map->size;i++) {
        struct map_element *item = map->elements[i];
        if (item != NULL)
            map_delete_element(item);
    }
    free(map->elements);
    free(map);
}

static int map_hash(const char *key, const int magic_number, const int buckets)
{
    long hash = 0;
    int key_length = strlen(key);
    for (int i = 0;i < key_length;i++) {
        hash += (long) pow(magic_number, key_length - (i + 1)) * key[i];
        hash = hash % buckets;
    }

    return hash;
}

static int map_get_hash(const char *key, const int buckets, const int attempts)
{
    const int hash_a = map_hash(key, MAP_PRIME_A, buckets);
    const int hash_b = map_hash(key, MAP_PRIME_B, buckets);
    return (hash_a + (attempts * (hash_b + 1))) % buckets;
}

void map_insert(struct map *map, const char *key, void *value)
{
    struct map_element *item = new_map_element(key, value);
    int index = map_get_hash(item->key, map->max_size, 0);

    struct map_element *aux = map->elements[index];
    for (int i = 1;aux != NULL;i++) {
        index = map_get_hash(item->key, map->max_size, i);
        aux = map->elements[index];
    }

    map->elements[index] = item;
    map->size++;
}
