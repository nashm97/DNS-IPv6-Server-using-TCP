/*
 * Question.h
 *
 *  Created on: 3 May 2021
 *      Author: USER
 */

#ifndef QUESTION_H_
#define QUESTION_H_
#include <stdlib.h>

#include "NAME.h"
#include "util.h"


struct question {
	NAME QNAME;
	char QTYPE[2];
	char QCLASS[2];

};

typedef struct question Question;

void read_into_question(Question* question, FILE* log, int file_descriptor);
#endif /* QUESTION_H_ */
