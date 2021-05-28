/*
 * NAME.c
 *
 *  Created on: 6 May 2021
 *      Author: USER
 */

#include "NAME.h"
#include "Linked_list.h"


void read_into_NAME(NAME* name, FILE* log, int file_descriptor){
	name->length_of_name =0;
	Linked_list* linked_list = new_linked_list();
	int number_of_labels=0;
	int NAME_finished=0;

	// while we have not reached the end of the QNAME
	while(!NAME_finished){
		Label* label;

		// read in the label and create space for it
		label = read_in_label(log, &NAME_finished, name->null_byte_at_end_of_name,  file_descriptor);
		name->length_of_name += (1 + label->number_of_bytes);

		// if we are not at the end of the QNAME add the label to a linked list
		if(!NAME_finished){
			linked_list_add_to_foot(linked_list, label);
			number_of_labels +=1;
		}
	}


	// create the right amount of space for the number of labels
	name->labels = malloc(sizeof(Label)*number_of_labels);

	name->number_of_labels = number_of_labels;

	// iterate through the linked list of labels assigning them into the QNAME structure
	int i=0;
	while(i<name->number_of_labels){
		name->labels[i] = (Label*)linked_list_remove_from_head(linked_list);
		i+=1;
	}


}

char* name_to_string(NAME* name){
	char* name_as_chars = malloc(sizeof(char)*256);
	int index_of_char = 0;
	for(int i=0;i< name->number_of_labels;i++){
		for(int j=0;j<name->labels[i]->number_of_bytes;j++){
			name_as_chars[index_of_char] = name->labels[i]->bytes[j];
			index_of_char+=1;
		}
		name_as_chars[index_of_char] = '.';
		index_of_char+=1;
	}
	name_as_chars[index_of_char] = '\0';
	return name_as_chars;
}
