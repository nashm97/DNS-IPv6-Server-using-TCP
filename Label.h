/*
 * Label.h
 *
 *  Created on: 6 May 2021
 *      Author: USER
 */

#ifndef LABEL_H_
#define LABEL_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

struct label {
	int number_of_bytes;
	char* bytes;
	char number_of_bytes_as_char[1];

};

typedef struct label Label;

Label* read_in_label(FILE* log, int* NAME_finished, char* null_byte_at_end_of_name,  int file_descriptor);
char* label_to_string(Label* label);
#endif /* LABEL_H_ */
