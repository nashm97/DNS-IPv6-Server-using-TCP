/*
 * Header.c
 *
 *  Created on: 3 May 2021
 *      Author: USER
 */
#include "Header.h"




void read_into_header(Header* header, FILE* log, int file_descriptor){
	// read in the header
	read_into_hex(header->length_as_char, 2, log, file_descriptor);

	int first_byte_of_length = convert_bits_to_int(header->length_as_char[0], 7, 0);
	//printf("byte 1 of length = %d\n", first_byte_of_length);
	int second_byte_of_length = convert_bits_to_int(header->length_as_char[1], 7, 0);
	//printf("byte 2 of length = %d\n", second_byte_of_length);
	header->length = first_byte_of_length*256 + second_byte_of_length;
	read_into_hex(header->ID, 2, log, file_descriptor);

	read_into_hex(header->QR_to_RCODE, 2, log, file_descriptor);
	header->QR = convert_bits_to_int(header->QR_to_RCODE[0], 7, 7);
	header->Opcode = convert_bits_to_int(header->QR_to_RCODE[0], 6, 3);
	header->AA = convert_bits_to_int(header->QR_to_RCODE[0], 2, 2);
	header->TC = convert_bits_to_int(header->QR_to_RCODE[0], 1, 1);
	header->RD = convert_bits_to_int(header->QR_to_RCODE[0], 0, 0);
	header->RA = convert_bits_to_int(header->QR_to_RCODE[1], 7, 7);
	header->Z = convert_bits_to_int(header->QR_to_RCODE[1], 6, 4);
	header->RCODE = convert_bits_to_int(header->QR_to_RCODE[1], 3, 0);

	read_into_hex(header->QDCOUNT_as_char, 2, log, file_descriptor);
	header->QDCOUNT = convert_bits_to_int(header->QDCOUNT_as_char[0], 7, 0)*256 + convert_bits_to_int(header->QDCOUNT_as_char[1], 7, 0);
	read_into_hex(header->ANCOUNT_as_char, 2, log, file_descriptor);
	header->ANCOUNT = convert_bits_to_int(header->ANCOUNT_as_char[0], 7, 0)*256 + convert_bits_to_int(header->ANCOUNT_as_char[1], 7, 0);
	read_into_hex(header->NSCOUNT_as_char, 2, log, file_descriptor);
	header->NSCOUNT = convert_bits_to_int(header->NSCOUNT_as_char[0], 7, 0)*256 + convert_bits_to_int(header->NSCOUNT_as_char[1], 7, 0);
	read_into_hex(header->ARCOUNT_as_char, 2, log, file_descriptor);
	header->ARCOUNT = convert_bits_to_int(header->ARCOUNT_as_char[0], 7, 0)*256 + convert_bits_to_int(header->ARCOUNT_as_char[1], 7, 0);
}
