/*
 * This file is part of hx - a hex editor for the terminal.
 *
 * Copyright (c) 2016 Kevin Pors. See LICENSE for details.
 */

#include "history.h"

#include <stdlib.h>
#include <stdio.h>

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

void history_add(struct history_list* list, char* string) {
	(void)list;
	(void)string;
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
	(void)list;
	(void)direction;
}

void history_get_curr(struct history_list* list, char* string) {
	(void)list;
	(void)string;
}

void history_reset_curr(struct history_list* list) {
	(void)list;
}

