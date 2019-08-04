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

static struct map_item *new_map_item(const char *key, void *value)
{
    struct map_item *new_item = smalloc(sizeof(struct map_item));
    new_item->key = strdup(key);
    new_item->value = value;
    return new_item;
}

void new_map(struct map *map)
{
    map = smalloc(sizeof(struct map));
    map->max_size = 50;
    map->size = 0;
    map->items = scalloc(map->max_size, sizeof(struct map_item *));
}

static void delete_map_item(struct map_item *item)
{
    free(item->key);
    free(item->value);
    free(item);
}

void delete_map(struct map *map)
{
    if (map->items == NULL)
        return;

    for (uint i = 0;i < map->size;i++) {
        struct map_item *item = map->items[i];
        if (item != NULL)
            delete_map_item(item);
    }
    free(map->items);
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
    struct map_item *item = new_map_item(key, value);
    int index = map_get_hash(item->key, map->max_size, 0);

    struct map_item *aux = map->items[index];
    for (int i = 1;aux != NULL;i++) {
        index = map_get_hash(item->key, map->max_size, i);
        aux = map->items[index];
    }

    map->items[index] = item;
    map->size++;
}
