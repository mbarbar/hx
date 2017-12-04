/*
 * This file is part of hx - a hex editor for the terminal.
 *
 * Copyright (c) 2016 Kevin Pors. See LICENSE for details.
 */

#include "editor.h"  // for INPUT_BUF_SIZE.

#ifndef HX_HISTORY_H
#define HX_HISTORY_H

/*
 * Maximum number of history entries in the history list.
 */
#define HISTORY_SIZE 20

/*
 * Contains definitions and functions to keep track of search and
 * command history. In essence, a doubly linked list where the tail
 * is the latest command/search string and the head is the earliest.
 * When the list is full (HISTORY_SIZE), the head moves forward (the
 * head is deleted).
 */

/*
 * This struct contains information about a history item - the searched-for
 * string or the command string, and its length. Also contained are the
 * next and previous commands/search strings in the history.
 */
struct history_entry {
	struct history_entry* prev;  // Previous history entry or NULL if first.
	struct history_entry* next;  // Next history entry or NULL if last.

	char string[INPUT_BUF_SIZE];  // Command or search string.
};

/*
 * The history_list struct contains information on the head and tail of the
 * current history. It also contains information about the currently
 * pointed to history entry as the history is being scrolled through.
 * curr == NULL indicates that the current position in iteration is right
 * "after" the tail.
 */
struct history_list {
	struct history_entry* head;  // Head of the list.
	struct history_entry* curr;  // Current position within the list.
	struct history_entry* tail;  // Tail of the list.
};

/*
 * Creates a history_list on the heap, initializes the head, the tail, and curr
 * to NULL and returns it.
 */
struct history_list* history_list_init(void);

/*
 * Returns the number of entries in list.
 */
size_t history_size(struct history_list* list);

/*
 * Adds a `history_entry' to the tail of the list by allocating a new history
 * entry on the heap (deep copy of string), deleting the head if the length is
 * currently HISTORY_SIZE, then setting the pointers in list correctly.
 */
void history_add(struct history_list* list, char* string);

/*
 * Frees the history_list by first freeing its nodes.
 */
void history_free(struct history_list* list);

/*
 * For debugging purposes, prints the contents of list to stderr.
 */
void history_print(struct history_list* list);

/*
 * Moves the curr pointer forwards or backwards one history entry within
 * list according to direction.
 * If direction < 0, then curr moves backwards.
 * If direction > 0, then curr moves forward.
 * (Does nothing if direction == 0.)
 *
 * Movement is capped backwards at the head, and capped forwards one entry
 * "after" the tail (and curr becomes NULL).
 */
void history_move(struct history_list* list, int direction);

/*
 * Copies the current command/search string in list (excluding leading ':'/'/')
 * into string. string must be able to hold INPUT_BUF_SIZE + 1 bytes.
 */
void history_get_curr(struct history_list* list, char* string);

/*
 * Resets the curr pointer to point to "after" the tail.
 */
void history_reset_curr(struct history_list* list);

#endif // HX_UNDO_H

