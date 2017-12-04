/*
 * This file is part of hx - a hex editor for the terminal.
 *
 * Copyright (c) 2016 Kevin Pors. See LICENSE for details.
 */

#include "history.h"

#include <stdlib.h>

struct history_list* history_list_init(void) {
	return NULL;
}

void history_add(struct history_list* list, char* string) {
	(void)list;
	(void)string;
}

void history_free(struct history_list* list) {
	(void)list;
}

void history_print(struct history_list* list) {
	(void)list;
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

