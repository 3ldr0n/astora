#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_CHARACTERS 200

struct node {
    void *value;
    struct node *next;
    struct node *prev;
};

struct list_t {
    struct node *head;
    struct node *tail;
    size_t size;
};

void *smalloc(size_t size);
void instanciate_list(struct list_t *list);
bool is_list_empty(struct list_t *list);
void append(struct list_t *list, void *value);
void remove_first(struct list_t *list);
void remove_last(struct list_t *list);
void print_list(struct list_t *list);

#endif
