#include "lib/linked_list.h"

static void *smalloc(const size_t size)
{
    if (!size)
        return NULL;

    void *mem = malloc(size);

    if (!mem) {
        fprintf(stderr, "Fatal: Memory allocation error (%zu bytes malloc)\n", size);
        exit(EXIT_FAILURE);
    }

    return mem;
}

void print_list(const struct list_t *list)
{
    for (struct node *item = list->head;item != NULL;item = item->next)
        printf("%s ", item->value);

    printf("\n");
}

void instanciate_list(struct list_t *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

bool is_list_empty(const struct list_t *list)
{
    return list->head == NULL;
}

void append(struct list_t *list, const void *value)
{
    struct node *new_node = (struct node *)smalloc(sizeof(struct node *));
    new_node->value = value;
    new_node->next = NULL;

    if (is_list_empty(list)) {
        new_node->prev = NULL;
        list->tail = list->head = new_node;
    } else {
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }

    list->size++;
}

void remove_first(struct list_t *list)
{
    if (is_list_empty(list)) return;

    if (list->head == list->tail) {
        free(list->head);
        list->head = list->tail = NULL;
    } else {
        struct node *aux = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        free(aux);
    }
    list->size--;
}

void remove_last(struct list_t *list)
{
    if (is_list_empty(list)) return;

    if (list->head == list->tail) {
        free(list->head);
        list->head = list->tail = NULL;
    } else {
        struct node *aux = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free(aux);
    }
    list->size--;
}
