/*
 * util.h
 *
 *  Created on: 6 May 2021
 *      Author: USER
 */

#ifndef UTIL_H_
#define UTIL_H_
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

void read_into_hex(char* hex, int length, FILE* log, int file_descriptor);
int convert_bits_to_int(unsigned char bits, int low, int high);
void print_byte_as_binary(char byte);
unsigned char set_bit(unsigned char byte, int new_bit_val, int bit_position);
unsigned char set_bits_in_byte_to_value(unsigned char byte, int high, int low, int value);

#endif /* UTIL_H_ */
