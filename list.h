#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

typedef void List;

/**
 * Create a new list with `item` as the first item.
 *
 * @returns The newly created list.
 */
List *list_create(void *item);

/**
 * Prepend `item` to start of the `list`.
 *
 * @returns `true` on success or `false` on error.
 */
bool list_prepend(List *list, void *item);

/**
 * Append `item` to the end of the `list`
 *
 * @returns `true` on success or `false` on error.
 */
bool list_append(List *list, void *item);

/**
 * Remove `item` from the `list`
 *
 * @returns `true` on success or `false` on error.
 */
bool list_remove(List *list, const void *item);

/**
 * Get the `item` at position `index`
 *
 * @returns The item or `NULL` if not found.
 */
const void *list_get(List *list, unsigned int index);

/**
 * Get the size of the `list`
 *
 * @returns The amount of elements in the list.
 */
unsigned int list_size(List *list);

#endif /* list.h  */
