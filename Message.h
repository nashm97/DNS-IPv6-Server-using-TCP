/*
 * message.h
 *
 *  Created on: 3 May 2021
 *      Author: Milo Nash
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "Question.h"
#include "Header.h"
#include "Resource_record.h"


struct message{
	Header header;
	Question question;
	Resource_record* answer;
	Resource_record* authoritative;
	Resource_record* additional;
	//char* rest_of_message;
	//int length_of_rest_of_message;
};

typedef struct message Message;

void read_into_message(Message* message, FILE* log, int file_descriptor);
char* Message_to_string(Message* message, char* chars);
void change_RCODE(Message* message, int new_RCODE);
#endif /* MESSAGE_H_ */
