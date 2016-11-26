#include "undo.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static const char* action_names[] = {
	"none",
	"delete",
	"insert",
	"replace",
	"append"
};


struct action_list* action_list_init() {
	struct action_list* list = malloc(sizeof(struct action_list));
	list->head = NULL;
	list->tail = NULL;
	return list;
}

void action_list_add(struct action_list* list, enum action_type type, int offset, unsigned char c) {
	assert(list != NULL);

	struct action* action = malloc(sizeof(struct action));
	action->prev = NULL;
	action->next = NULL;
	action->act = type;
	action->offset = offset;
	action->c = c;

	if (list->head == NULL) {
		// is this the first node added to the list?
		list->head = action;
		list->tail = action;
	} else {
		// Point the previous node of the new action to the current tail.
		action->prev = list->tail;
		// Then point the tail of the list to the new action.
		list->tail->next = action;
		// Then
		list->tail = action;
	}
}

void action_list_free(struct action_list* list) {
	assert(list != NULL);

	struct action* node = list->head;
	while (node != NULL) {
		struct action* temp = node;
		node = node->next;
		free(temp);
	}
	free(node);
	free(list);
}


void action_list_print(struct action_list* list) {
	struct action* node = list->head;
	while (node != NULL) {
		fprintf(stderr, "(%d, %s, %02x) -> ", node->offset, action_names[node->act], node->c);
		node = node->next;
		if (node == NULL) {
			fprintf(stderr, "END\n");
		}
	}
}

