/*
 * Question.c
 *
 *  Created on: 3 May 2021
 *      Author: USER
 */
#include "Question.h"

void read_into_question(Question* question, FILE* log, int file_descriptor){
	printf("INSIDE QUESTION\n");
	read_into_NAME(&(question->QNAME), log, file_descriptor);
	read_into_hex(question->QTYPE, 2, log, file_descriptor);
	read_into_hex(question->QCLASS, 2, log, file_descriptor);
}

