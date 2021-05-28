/*
 * Message->c
 *
 *  Created on: 3 May 2021
 *      Author: Milo Nash
 */

#include "Message.h"

void read_into_message(Message* message, FILE* log, int file_descriptor){
	printf("INSIDE MESSAGE\n");
	// read in the header and the question
	read_into_header(&(message->header), log, file_descriptor);
	read_into_question(&(message->question), log, file_descriptor);

	// read in the answers
	Resource_record* answers= malloc(sizeof(Resource_record)*message->header.ANCOUNT);
	message->answer = answers;
	printf("NUMBER OF ANSWERS TO READ IN %d\n", message->header.ANCOUNT);
	for(int i=0;i<message->header.ANCOUNT;i++){

		read_into_resource_record(&(message->answer[i]), log, file_descriptor);
	}

	// read in the authoritative records
	Resource_record* authoritative= malloc(sizeof(Resource_record)*message->header.NSCOUNT);
	message->authoritative = authoritative;
	printf("NUMBER OF AUTHORITATIVE TO READ IN %d\n", message->header.NSCOUNT);
	for(int i=0;i<message->header.NSCOUNT;i++){

		read_into_resource_record(&(message->authoritative[i]), log, file_descriptor);
	}


	// read in the additional records
	Resource_record* additional= malloc(sizeof(Resource_record)*message->header.ARCOUNT);
	message->additional = additional;
	printf("NUMBER OF ADDITIONAL TO READ IN %d\n", message->header.ARCOUNT);
	for(int i=0;i<message->header.ARCOUNT;i++){
		read_into_resource_record(&(message->additional[i]), log, file_descriptor);
	}

	/*// calculate how many bytes the rest of the message has
	int amount_of_message_not_read_in = message->header.length  - message->question.QNAME.length_of_name  - 16;
	for(int i = 0;i<message->header.ANCOUNT;i++){
		amount_of_message_not_read_in-=message->answer[i].NAME.length_of_name;
		amount_of_message_not_read_in-=message->answer[i].RDLENGTH -1;
	}
	message->length_of_rest_of_message = amount_of_message_not_read_in;

	char rest_of_message[amount_of_message_not_read_in];
	// read the rest of the message
	read_into_hex(rest_of_message, amount_of_message_not_read_in, log, file_descriptor);
	message->rest_of_message  = rest_of_message;
	printf("finished read in message\n");*/

}


char* Message_to_string(Message* message, char* chars){


	// assign each byte of the header the header to chars
	chars[0] = message->header.length_as_char[0];
	chars[1] = message->header.length_as_char[1];
	chars[3] = message->header.ID[0];
	chars[4] = message->header.ID[2];
	chars[5] = message->header.QR_to_RCODE[0];
	printf("in message got here 12\n");
	chars[6] = message->header.QR_to_RCODE[1];
	chars[7] = message->header.QDCOUNT_as_char[0];
	chars[8] = message->header.QDCOUNT_as_char[1];
	chars[9] = message->header.ANCOUNT_as_char[0];
	chars[10] = message->header.ANCOUNT_as_char[1];
	chars[11] = message->header.NSCOUNT_as_char[0];
	chars[12] = message->header.NSCOUNT_as_char[1];
	printf("in message got here 13\n");
	chars[13] = message->header.ARCOUNT_as_char[0];
	chars[14] = message->header.ARCOUNT_as_char[1];

	// assign each byte of the header the question to chars

	// question name
	int added_length = 0;
	for(int i =0;i<message->question.QNAME.number_of_labels;i++){
		chars[15+added_length] = message->question.QNAME.labels[i]->number_of_bytes_as_char[0];
		added_length+=1;
		for(int j=0;j< message->question.QNAME.labels[i]->number_of_bytes;j++){
			chars[15+added_length] = message->question.QNAME.labels[i]->bytes[j];
			added_length+=1;
		}
		chars[15+added_length] = message->question.QNAME.null_byte_at_end_of_name[1];
		added_length+=1;
	}

	// rest of question
	chars[15+added_length] = message->question.QTYPE[0];
	chars[16+added_length] = message->question.QTYPE[1];
	chars[17+added_length] = message->question.QCLASS[0];
	chars[18+added_length] = message->question.QCLASS[1];

	// read in the answers
	int index;
	for( int i=0;i<message->header.ANCOUNT;i++){
		index = record_to_string(&(message->answer[i]), chars, 19+added_length);
	}

	// read in the authoritative
	for( int i=0;i<message->header.NSCOUNT;i++){
		index = record_to_string(&(message->authoritative[i]), chars, index);
	}

	// read in the additional
	for( int i=0;i<message->header.ARCOUNT;i++){
		index = record_to_string(&(message->additional[i]), chars, index);
	}

	printf("in message got here 18\n");

	/*// convert the rest of the message to a char
	for(int p=0;p<message->length_of_rest_of_message;p++){
		chars[29+added_length] = message->rest_of_message[p];
		added_length+=1;
	}*/

	printf("in message got here 19\n");


	//return the created char*
	return chars;
}

void change_RCODE(Message* message, int new_RCODE){
	message->header.RCODE = new_RCODE;
	message->header.QR_to_RCODE[1] = set_bits_in_byte_to_value(message->header.QR_to_RCODE[1], 3, 0, new_RCODE);
}
