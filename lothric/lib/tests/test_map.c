#include "lib/test.h"
#include "lib/map.h"

int main()
{
    struct map map;
    new_map(&map);

    map_insert(&map, "key", "value");

    delete_map(&map);
}
