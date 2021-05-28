/*
 * util.c
 *
 *  Created on: 6 May 2021
 *      Author: USER
 */
#include "util.h"

// reads a hexadecimal number into the space at char* hex then prints it to the FILE* log
void read_into_hex(char* hex, int length, FILE* log, int file_descriptor){
	//printf("%d:\n", 	(int)read(file_descriptor, hex, length));
	for(int i=0;i<length;i++){
		if(fscanf(log, "%c", &hex[i])==1){
		}
	}
	static int number_of_zeros_in_a_row = 0;
	for(int i=0;i<length;i++){
		if(hex[i] == 0){
			number_of_zeros_in_a_row+=1;
		}
		else{number_of_zeros_in_a_row = 0;}
		if(number_of_zeros_in_a_row>100){
			printf("too many zeros\n");
			exit(EXIT_FAILURE);
		}
		print_byte_as_binary(hex[i]);
		//fprintf(log, "%c", hex[i]);
	}
}

// converts a unsigned char binary_number of 8 bits into an integer,
// where high and low are the start and finish positions of the required binary number,
// where position 0 is at the end of the binary number.
int convert_bits_to_int(unsigned char binary_number, int high, int low){
	int shift_up =sizeof(unsigned int)*8 - high -1;
	int shift_down = low;
	unsigned int c = binary_number;
	c = c << shift_up;
	c = c >> (shift_down +shift_up);
	return (int)c;
}


// prints a byte as a 8 bit binary number
void print_byte_as_binary(char byte){
	int bit2 = convert_bits_to_int(byte, 7, 7);
	int bit3 = convert_bits_to_int(byte, 6, 6);
	int bit4 = convert_bits_to_int(byte, 5, 5);
	int bit5 = convert_bits_to_int(byte, 4, 4);
	int bit6 = convert_bits_to_int(byte, 3, 3);
	int bit7 = convert_bits_to_int(byte, 2, 2);
	int bit8 = convert_bits_to_int(byte, 1, 1);
	int bit9 = convert_bits_to_int(byte, 0, 0);
	printf("byte = %d%d%d%d%d%d%d%d\n", bit2, bit3, bit4, bit5, bit6, bit7, bit8, bit9);
}

unsigned char set_bit(unsigned char byte, int new_bit_val, int bit_position){
	assert(new_bit_val ==0 || new_bit_val == 1);
	unsigned char bit_setter = 1>>bit_position;


	int current_bit_val = convert_bits_to_int(byte, bit_position, bit_position);
	if(current_bit_val == new_bit_val){
		return byte;
	}
	return byte^bit_setter;
}

unsigned char set_bits_in_byte_to_value(unsigned char byte, int high, int low, int value){
	assert(0<=value && value<=255);
	unsigned char value_as_char = (unsigned char)value;
	unsigned char new_byte = byte;
	for(int i =low; i<high+1;i++){
		int bit_at_i_of_value = convert_bits_to_int(value_as_char, i, i);
		new_byte = set_bit(new_byte, bit_at_i_of_value, i);
	}
	return new_byte;
 }

