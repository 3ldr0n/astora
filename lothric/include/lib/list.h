#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_CHARACTERS 200

struct node {

    // ponteiro generico
    const void *value;

    // ponteiro para o proximo nó na lista
    struct node *next;

    // ponteiro para o nó anterior na lista
    struct node *prev;
};

struct list_t {

    // ponteiro para  cabeça
    struct node *head;

    // ponteiro para o rabo
    struct node *tail;

    size_t size;
};

// inicializa a lista
void list_instanciate(struct list_t *list);

// verifica se é uma lista vazia
bool list_is_empty(const struct list_t *list);

// adiciona um elemento na lista
void list_append(struct list_t *list, const void *value);

// remove o primeiro elemento da lista
void list_remove_first(struct list_t *list);

// remove o ultimo elemento da lista
void list_remove_last(struct list_t *list);

#endif
