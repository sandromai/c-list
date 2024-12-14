#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

typedef struct Node {
  void *data;
  struct Node *prev;
  struct Node *next;
} Node;

typedef struct List {
  unsigned int length;
  Node *head;
  Node *tail;
} List;

static Node *dln_create(void *item) {
  Node *node = malloc(sizeof *node);

  if (node == NULL) {
    return NULL;
  }

  node->data = item;
  node->prev = node->next = NULL;

  return node;
}

List *list_create(void *item) {
  Node *node = dln_create(item);

  if (node == NULL) {
    return NULL;
  }

  List *list = malloc(sizeof *list);

  if (list == NULL) {
    free(node);
    return NULL;
  }

  list->length = 1;
  list->head = list->tail = node;

  return list;
}

bool list_prepend(List *list, void *item) {
  errno = 0;

  if (list == NULL) {
    return false;
  }

  Node *node = dln_create(item);

  if (node == NULL) {
    return false;
  }

  ++list->length;

  if (list->head == NULL) {
    list->head = list->tail = node;
    return true;
  }

  node->next = list->head;
  list->head->prev = node;
  list->head = node;
  return true;
}

bool list_append(List *list, void *item) {
  errno = 0;

  if (list == NULL) {
    return false;
  }

  Node *node = dln_create(item);

  if (node == NULL) {
    return false;
  }

  ++list->length;

  if (list->tail == NULL) {
    list->tail = list->head = node;
    return true;
  }

  node->prev = list->tail;
  list->tail->next = node;
  list->tail = node;
  return true;
}

bool list_remove(List *list, const void *item) {
  errno = 0;

  if (list == NULL || list->head == NULL) {
    return false;
  }

  Node *currentNode = list->head;

  for (unsigned int i = 0; i < list->length; ++i) {
    if (currentNode->data == item) {
      break;
    }

    currentNode = currentNode->next;
  }

  if (currentNode == NULL) {
    return false;
  }

  --list->length;

  if (currentNode->prev != NULL) {
    currentNode->prev->next = currentNode->next;
  }

  if (currentNode->next != NULL) {
    currentNode->next->prev = currentNode->prev;
  }

  if (currentNode == list->head) {
    list->head = currentNode->next;
  }

  if (currentNode == list->tail) {
    list->tail = currentNode->prev;
  }

  currentNode->prev = NULL;
  currentNode->next = NULL;
  free(currentNode);
  currentNode = NULL;
  return true;
}

const void *list_get(List *list, unsigned int index) {
  errno = 0;

  if (list == NULL || list->head == NULL) {
    return NULL;
  }

  if (index >= list->length) {
    return NULL;
  }

  Node *currentNode = list->head;

  for (unsigned int i = 0; i < index; ++i) {
    currentNode = currentNode->next;
  }

  return currentNode->data;
}

unsigned int list_size(List *list) {
  if (list == NULL) {
    return 0;
  }

  return list->length;
}
