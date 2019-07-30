#include "lib/linked_list.h"

/**
 * Malloc seguro, verifica se alocação ocorreu corretamente.
 *
 * size:
 * Tamanho a ser alocado.
 */
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

/**
 * Inicializa a lista vazia.
 *
 * list:
 * Ponteiro para o lista.
 */
void instanciate_list(struct list_t *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

/**
 * Verifica se a lista está vazia.
 *
 * list:
 * Ponteiro para a lista.
 */
bool is_list_empty(const struct list_t *list)
{
    return list->head == NULL;
}

/**
 * Insere um elemento no final da lista.
 *
 * list:
 * Ponteiro para a lista.
 * value:
 * Valor a ser inserido.
 */
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

/**
 * Remove o primeiro elemento da lista.
 *
 * list:
 * Ponteiro para a lista.
 */
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

/**
 * Remove o último elemento da lista.
 *
 * list:
 * Ponteiro para a lista.
 */
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
