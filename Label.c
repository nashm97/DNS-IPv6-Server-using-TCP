/*
 * Label.c
 *
 *  Created on: 6 May 2021
 *      Author: USER
 */
#include "Label.h"
#include "util.h"

// read in and create the space for a label in a QNAME.
Label* read_in_label(FILE* log, int* NAME_finished, char* null_byte_at_end_of_name,  int file_descriptor){
	printf("INSIDE LABELS\n");
	char hex[1];

	// read in the length of the label
	read_into_hex(hex, 1, log, file_descriptor);
	int length = convert_bits_to_int(hex[0], 7, 0);
	printf(" number of bytes in label = %d\n",length);
	if(length>=192){
		*NAME_finished = 1;
		printf("LABEL IS COMPRESSED\n");

		// create space for the label and read into that space
		Label* label = malloc(sizeof(Label));
		label->bytes = malloc(sizeof(char)*0);
		label->number_of_bytes_as_char[1] =(char)0;
		label->number_of_bytes = 0;
		read_into_hex(label->bytes, label->number_of_bytes, log, file_descriptor);
		printf("LABEL = %s\n", label_to_string(label));
		printf("reading in possible junk char\n");
		char junk[1];
		read_into_hex(junk, 1, log, file_descriptor);
		return label;

	}
	// if we are at the end of the QNAME set QNAME_finished to 1.
	if(length == 0){
		null_byte_at_end_of_name = hex;
		*NAME_finished = 1;
		printf("NAME IS FINISHED\n");
	}

	// create space for the label and read into that space
	Label* label = malloc(sizeof(Label));
	label->bytes = malloc(sizeof(char)*length);
	label->number_of_bytes_as_char[1] =hex[0];
	label->number_of_bytes = length;
	read_into_hex(label->bytes, label->number_of_bytes, log, file_descriptor);
	printf("LABEL = %s\n", label_to_string(label));
	return label;
}



char* label_to_string(Label* label){
	char* chars = malloc(sizeof(char)*label->number_of_bytes);
	int i;
	for(i=0;i<label->number_of_bytes;i++){
		chars[i] = label->bytes[i];
	}
	chars[i] = '\0';
	return chars;
}
