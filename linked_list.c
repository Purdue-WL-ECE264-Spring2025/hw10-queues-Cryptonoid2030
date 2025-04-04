#include "linked_list.h"
#include <stdlib.h>

struct list_node *new_node(size_t value) {
    struct list_node *node = malloc(sizeof(struct list_node));
    node->value = value;
    node->next = NULL;
    return node;
}

void insert_at_head(struct linked_list *list, size_t value) {
    struct list_node *node = new_node(value);
    node->next = list->head;
    list->head = node;
}

void insert_at_tail(struct linked_list *list, size_t value) {
    struct list_node *node = new_node(value);
    if (!list->head) {
        list->head = node;
        return;
    }
    struct list_node *cur = list->head;
    while (cur->next) 
    {
      cur = cur->next;
    }
    cur->next = node;
}

// size_t remove_from_head(struct linked_list *list) {
//     if (!list->head) return false; // how to handle if empty linked list in queue.c?
//     struct list_node *temp = list->head;
//     size_t value = temp->value;
//     list->head = list->head->next;
//     free(temp);
//     return value;
// }

size_t remove_from_head(struct linked_list *list) {
  if (!list->head) {
    printf("\nreeeeeee\n");
    return (size_t)-1;  // or SIZE_MAX
  }
  struct list_node *temp = list->head;
  size_t value = temp->value;
  list->head = list->head->next;
  free(temp);
  return value;
}


size_t remove_from_tail(struct linked_list *list) {
    if (!list->head) return false;
    struct list_node *cur = list->head, *prev = NULL;
    while (cur->next) {
        prev = cur;
        cur = cur->next;
    }
    size_t value = cur->value;
    if (prev)
        prev->next = NULL;
    else
        list->head = NULL;
    free(cur);
    return value;
}

void free_list(struct linked_list list) {
  struct list_node *current = list.head;
  while (current != NULL) {
      struct list_node *temp = current;
      current = current->next;
      free(temp);
  }
}
