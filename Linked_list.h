/*
 * Linked_list.h
 *
 *  Created on: 6 May 2021
 *      Author: USER
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include "Label.h"

typedef struct linked_list Linked_list;
typedef struct node node;

struct node {
	void* data;
	node* next;
	node* prev;
};

struct linked_list {
	int is_empty;
	int length;
	node* head;
	node* foot;
};



Linked_list* new_linked_list();
void set_head(Linked_list* list, node* value);
void set_foot(Linked_list* list, node* value);
void free_linked_list(Linked_list *list);
void linked_list_add_to_head(Linked_list *list, void* data);
void linked_list_add_to_foot(Linked_list *list, void* data);
void* linked_list_remove_from_head(Linked_list *list);
void* linked_list_remove_from_foot(Linked_list *list);

#endif /* LINKED_LIST_H_ */
