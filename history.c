/*
 * This file is part of hx - a hex editor for the terminal.
 *
 * Copyright (c) 2016 Kevin Pors. See LICENSE for details.
 */

#include "history.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct history_list* history_list_init(void) {
	struct history_list* list = malloc(sizeof(struct history_list));

	if (list == NULL) {
		perror("Unable to allocate size for struct history_list");
		exit(1);
	}

	list->head = NULL;
	list->tail = NULL;
	list->curr = NULL;

	return list;
}

size_t history_size(struct history_list* list) {
	size_t size = 0;
	struct history_entry* node = list->head;

	for (; node != NULL; node = node->next) ++size;

	return size;
}

void history_add(struct history_list* list, char* string) {
	struct history_entry *entry = malloc(sizeof(struct history_entry));
	if (entry == NULL) {
		perror("Unable to allocate size for struct history_entry");
		exit(1);
	}

	entry->prev = list->tail;
	entry->next= NULL;
	strncpy(entry->string, string, INPUT_BUF_SIZE);

	if (list->head == NULL) {
		// Empty list
		list->head = list->tail = entry;
	} else {
		if (history_size(list) == HISTORY_SIZE) {
			struct history_entry* old_head = list->head;
			list->head = old_head->next;
			list->head->prev = NULL;
			free(old_head);
		}

		list->tail->next = entry;
		list->tail = entry;
	}

	// curr is untouched.
}

void history_free(struct history_list* list) {
	struct history_entry* curr = list->head;
	while (curr != NULL) {
		struct history_entry* prev = curr;
		curr = curr->next;
		free(prev);
	}

	free(list);
}

void history_print(struct history_list* list) {
	struct history_entry* node = list->head;

	fprintf(stderr, "History: ");

	if (node == NULL) fprintf(stderr, "empty history");

	while (node != NULL) {
		fprintf(stderr, "(%s) -> ", node->string);
		node = node->next;
		if (node == NULL) fprintf(stderr, "END\n");
	}

	fprintf(stderr, "\n");
}

void history_move(struct history_list* list, int direction) {
	if (direction == 1) {
		if (list->curr != NULL) list->curr = list->curr->next;
	} else if (direction == -1) {
		if (list->curr == NULL) list->curr = list->tail;
		else {
			if (list->curr != list->head) {
				list->curr = list->curr->prev;
			}
		}
	} else {
		// direction == 0 - do nothing.
	}
}

void history_get_curr(struct history_list* list, char* string) {
	if (list->curr == NULL) string[0] = '\0';
	else strncpy(string, list->curr->string, INPUT_BUF_SIZE);
}

void history_reset_curr(struct history_list* list) {
	list->curr = NULL;
}

