/*
 * Linked_list.c
 *
 *  Created on: 6 May 2021
 *      Author: USER
 */


/*
 * Doubly_linked_list.c
 *
 *  Created on: 20 Mar 2021
 *      Author: USER
 */
#include "Linked_list.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

Linked_list* new_linked_list(){
	Linked_list* new_linked_list = malloc(sizeof(Linked_list));
	new_linked_list->is_empty = 1;
	new_linked_list->length = 0;
	set_head(new_linked_list, NULL);
	return new_linked_list;
}

// sets the value for the head and the foot if appropriate
void set_head(Linked_list* list, node* value){
  if(value == NULL){
    list->foot = NULL;
  }
  if(list->is_empty){
    list->foot = value;
  }
  list->head = value;
}

// sets the value for the foot and the head if appropriate
void set_foot(Linked_list* list, node* value){
  if(value == NULL){
    list->head = NULL;
  }
  if(list->is_empty){
    list->head = value;
  }
  list->foot = value;
}

void free_linked_list(Linked_list *list) {
  node* tmp;
  while(list->head != NULL){
    tmp = list->head;
    set_head(list, list->head->next);
    free(tmp);
  }
}


void linked_list_add_to_head(Linked_list *list, void* data) {
  node* new_node = malloc(sizeof(node));
  new_node->data = data;
  //if head and foot are NULL initialize
  if(list->is_empty){
    set_head(list, new_node);
    list->is_empty = 0;
    list->head->prev = NULL;
    list->head->next = NULL;
  }
  //otherwise push to the head
  else{
    new_node->next = list->head;
    new_node->prev = NULL;
    list->head->prev = new_node;
    set_head(list, new_node);
  }
  list->length+=1;
}


void linked_list_add_to_foot(Linked_list *list, void* data) {
  node* new_node = malloc(sizeof(node));
  new_node->data = data;
  //if head and foot are NULL initialize
  if(list->is_empty){
    set_foot(list, new_node);
    list->is_empty = 0;
    list->head->prev = NULL;
    list->head->next = NULL;
  }
  else{
    //otherwise insert to the foot
    new_node->prev = list->foot;
    new_node->next = NULL;
    list->foot->next = new_node;
    set_foot(list, new_node);
  }
  list->length+=1;
}


void* linked_list_remove_from_head(Linked_list *list) {
  void* data = list->head->data;
  //if final node set head and foot
  if(list->length ==1){
    set_head(list, list->head->next);
    list->is_empty = 1;
    list->length-=1;
  }
  //otherwise pop appropriately
  else{
    set_head(list, list->head->next);
    list->head->prev = NULL;
    list->length-=1;
    free(list->head->prev);
  }
  return data;
}


void* linked_list_remove_from_foot(Linked_list *list) {
  void* process = list->foot->data;
  //if final node set head and foot
  if(list->length ==1){
    set_foot(list, list->foot->prev);
    list->is_empty = 1;
    list->length-=1;
  }
  else{
    set_foot(list, list->foot->prev);
    list->foot->next = NULL;
    list->length-=1;
    free(list->foot->next);
  }
  return process;
}
