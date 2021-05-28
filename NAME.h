/*
 * NAME.h
 *
 *  Created on: 6 May 2021
 *      Author: USER
 */

#ifndef NAME_H_
#define NAME_H_

#include "Label.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

struct name {
	int length_of_name;
	int number_of_labels;
	Label** labels;
	char null_byte_at_end_of_name[1];

};

typedef struct name NAME;

void read_into_NAME(NAME* name, FILE* log, int file_descriptor);
char* name_to_string(NAME* name);
#endif /* NAME_H_ */
