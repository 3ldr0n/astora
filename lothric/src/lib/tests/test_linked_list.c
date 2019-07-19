#include <stdbool.h>

#include "lib/linked_list.h"
#include "lib/test.h"

int test_instanciate_list(struct list_t *list)
{
    instanciate_list(list);
    _assert(list->size == 0);
    return 1;
}

int test_is_empty_list(struct list_t *list)
{
    _assert(is_list_empty(list));
    return 1;
}

int test_append(struct list_t *list)
{
    append(list, (void *)3);
    append(list, (void *)1);
    append(list, (void *)2);
    _assert(list->size == 3);
    _assert(list->head->value == (void *)3);
    _assert(list->tail->value == (void *)2);
    return 1;
}

int test_remove_first(struct list_t *list)
{
    remove_first(list);
    _assert(list->size == 2);
    return 1;
}

int test_remove_last(struct list_t *list)
{
    remove_last(list);

    _assert(list->tail->value == list->head->value);
    _assert(list->size == 1);
    return 1;
}

int main()
{
    struct list_t list;

    test_instanciate_list(&list);

    test_is_empty_list(&list);

    test_append(&list);

    test_remove_first(&list);

    test_remove_last(&list);

    printf("%d/%d tests passed\n", tests_passed, tests_run);

    return 0;
}
