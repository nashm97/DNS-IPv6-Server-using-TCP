/*
 * Header.h
 *
 *  Created on: 3 May 2021
 *      Author: USER
 */

#ifndef HEADER_H_
#define HEADER_H_
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "util.h"
 //headeer length = 12
 //question legnth = 4 + name length


struct header {
	char length_as_char[2];
	int length;
	char ID[2];
	char QR_to_RCODE[2];
	int QR;
	int Opcode;
	int AA;
	int TC;
	int RD;
	int RA;
	int Z;
	int RCODE;
	char QDCOUNT_as_char[2];
	int QDCOUNT;
	char ANCOUNT_as_char[2];
	int ANCOUNT;
	char NSCOUNT_as_char[2];
	int NSCOUNT;
	char ARCOUNT_as_char[2];
	int ARCOUNT;
};


typedef struct header Header;

void read_into_header(Header* header, FILE* log, int file_descriptor);

#endif /* HEADER_H_ */
