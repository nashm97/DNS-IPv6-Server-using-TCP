/*
 * Resource_record.c
 *
 *  Created on: 9 May 2021
 *      Author: USER
 */
#include "Resource_record.h"


void read_into_resource_record(Resource_record* record, FILE* log, int file_descriptor){
	printf("INSIDE RESOURCE RECORD\n");
	read_into_NAME(&(record->NAME), log, file_descriptor);
	printf("TYPE of RECORD = ");
	read_into_hex(record->TYPE, 2, log, file_descriptor);
	printf("CLASS of RECORD = ");
	read_into_hex(record->CLASS, 2, log, file_descriptor);
	read_into_hex(record->TTL, 4, log, file_descriptor);
	read_into_hex(record->RDLENGTH_as_char, 2, log, file_descriptor);
	record->RDLENGTH = convert_bits_to_int(record->RDLENGTH_as_char[0], 7, 0)*256 + convert_bits_to_int(record->RDLENGTH_as_char[1], 7, 0);
	printf("RDLENGTH = %d\n", record->RDLENGTH);

	record->RDATA = malloc(sizeof(char)*(record->RDLENGTH));
	read_into_hex(record->RDATA, record->RDLENGTH, log, file_descriptor);
	int type = record->TYPE[0]*256 + record->TYPE[1];
	int class = record->CLASS[0]*256 + record->CLASS[1];
	if(type == 28 && class == 1){
		ip_address_from_rdata(record->RDATA, record->ip_address);
	}
}

void ip_address_from_rdata(char* rdata, char* ip){
	ip[0] = rdata[0]*256+rdata[1];
	sprintf(ip, "%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x", rdata[0],rdata[1],rdata[2],rdata[3],rdata[4],rdata[5],rdata[6],rdata[7],rdata[8],rdata[9],rdata[10],rdata[11],rdata[12],rdata[13],rdata[14],rdata[15]);
	ip[8*4+7+1-1] = '\0';
}

int record_to_string(Resource_record* record, char* chars, int index_of_chars){
	// assign each byte of the record
	int added_length = 0;
	for(int i =0;i<record->NAME.number_of_labels;i++){
		chars[index_of_chars+added_length] = record->NAME.labels[i]->number_of_bytes_as_char[0];
		added_length+=1;
		for(int j=0;j< record->NAME.labels[i]->number_of_bytes;j++){
			chars[index_of_chars+added_length] = record->NAME.labels[i]->bytes[j];
			added_length+=1;
		}
		chars[index_of_chars+added_length] = record->NAME.null_byte_at_end_of_name[1];
		added_length+=1;
	}

	// rest of record
	printf("in message got here 16\n");
	chars[index_of_chars+added_length+1] = record->TYPE[0];
	chars[index_of_chars+added_length+2] = record->TYPE[1];
	chars[index_of_chars+added_length+3] = record->CLASS[0];
	chars[index_of_chars+added_length+4] = record->CLASS[1];
	chars[index_of_chars+added_length+5] = record->TTL[0];
	chars[index_of_chars+added_length+6] = record->TTL[1];
	chars[index_of_chars+added_length+7] = record->TTL[2];
	chars[index_of_chars+added_length+8] = record->TTL[3];
	chars[index_of_chars+added_length+9] = record->RDLENGTH_as_char[0];
	chars[index_of_chars+added_length+10] = record->RDLENGTH_as_char[1];
	printf("in message got here 17\n");

	for(int k=0;k<record->RDLENGTH;k++){
		chars[index_of_chars+added_length+11] = record->RDATA[k];
		added_length+=1;
	}
	return index_of_chars+added_length+11;
}


