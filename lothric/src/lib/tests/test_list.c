#include <stdbool.h>

#include "lib/list.h"
#include "lib/test.h"

int test_list_instanciate(struct list_t *list)
{
    list_instanciate(list);
    _assert(list->size == 0);
    return 1;
}

int test_list_is_empty(struct list_t *list)
{
    _assert(list_is_empty(list));
    return 1;
}

int test_list_append(struct list_t *list)
{
    list_append(list, (void *)3);
    list_append(list, (void *)1);
    list_append(list, (void *)2);
    _assert(list->size == 3);
    _assert(list->head->value == (void *)3);
    _assert(list->tail->value == (void *)2);
    return 1;
}

int test_list_remove_first(struct list_t *list)
{
    list_remove_first(list);
    _assert(list->size == 2);
    return 1;
}

int test_list_remove_last(struct list_t *list)
{
    list_remove_last(list);

    _assert(list->tail->value == list->head->value);
    _assert(list->size == 1);
    return 1;
}

int main()
{
    struct list_t list;

    test_list_instanciate(&list);

    test_list_is_empty(&list);

    test_list_append(&list);

    test_list_remove_first(&list);

    test_list_remove_last(&list);

    printf("%d/%d tests passed\n", tests_passed, tests_run);

    return 0;
}
