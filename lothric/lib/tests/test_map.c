#include "lib/test.h"
#include "lib/map.h"

int main()
{
    struct map map;
    map_new(&map, 1);

    map_insert(&map, "key", "value");

    map_delete(&map);
}
