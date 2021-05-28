/*
 * Reasource_record.h
 *
 *  Created on: 9 May 2021
 *      Author: USER
 */

#ifndef RESOURCE_RECORD_H_
#define RESOURCE_RECORD_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "util.h"
#include "NAME.h"

struct resource_record {
	NAME NAME;
	char TYPE[2];
	char CLASS[2];
	char TTL[4];
	char RDLENGTH_as_char[2];
	int RDLENGTH;
	char* RDATA;
	char ip_address[8*4+7+1];

};

typedef struct resource_record Resource_record;

void read_into_resource_record(Resource_record* record, FILE* log, int file_descriptor);
int record_to_string(Resource_record* record, char* chars, int index_of_chars);
void ip_address_from_rdata(char* rdata, char* ip);


#endif /* RESOURCE_RECORD_H_ */
