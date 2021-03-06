/*
 * dns_svr.c
 *
 *  Created on: 28 Apr 2021
 *      Author: Milo Nash
 */
#include "dns_svr.h"
#include <assert.h>

int main(int argc, char** argv){
	char* server_ip = argv[1];
	char* server_port = argv[2];
	FILE* log = fopen("dns_svr.log", "w+");
	int file_descriptor_for_linstening_to_connections_from_server, a;
	struct addrinfo hints2, *res2, *rp;


	// CREATE A SOCKET TO LISTEN TO CONNECTIONS FROM THE SERVER

	// Create address we're going to listen on (with given port number)
	memset(&hints2, 0, sizeof(hints2));
	hints2.ai_family = AF_UNSPEC;       // IPv6
	hints2.ai_socktype = SOCK_STREAM; // TCP
	hints2.ai_flags = AI_PASSIVE;     // for bind, listen, accept

	// node (NULL means any interface), service (port), hints2, res2
	a = getaddrinfo(server_ip, server_port, &hints2, &res2);
	if (a != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(a));
		exit(EXIT_FAILURE);
	}




	// CONNECT TO CLIENT

	int file_descriptor_to_listen_to_connections_from_client, file_descriptor_for_client, n, re, s;
	struct addrinfo hints, *res;
	struct sockaddr_storage client_address;
	socklen_t client_address_size;

	// Create address we're going to listen on (with given port number)
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET6;       // IPv6
	hints.ai_socktype = SOCK_STREAM; // TCP
	hints.ai_flags = AI_PASSIVE;     // for bind, listen, accept

	// node (NULL means any interface), service (port), hints, res
	char* client_port = "8053";
	s = getaddrinfo(NULL, client_port, &hints, &res);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	// Create socket
	printf("res->ai_family =%d, res->ai_socktypem =%d, res->ai_protocol =%d", res->ai_family, res->ai_socktype, res->ai_protocol);
	file_descriptor_to_listen_to_connections_from_client = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	if (file_descriptor_to_listen_to_connections_from_client < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	// Reuse port if possible
	re = 1;
	if (setsockopt(file_descriptor_to_listen_to_connections_from_client, SOL_SOCKET, SO_REUSEADDR, &re, sizeof(int)) < 0) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	// Bind address to the socket
	if (bind(file_descriptor_to_listen_to_connections_from_client, res->ai_addr, res->ai_addrlen) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(res);

	// start listening on my address for accepting from the client
    if (listen(file_descriptor_to_listen_to_connections_from_client, 10) == -1){
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    // get the size of the server address
    client_address_size = sizeof(client_address);




	while(1){
		FILE* recieved_from_client_for_debugging = fopen("from_client_for_debugging.txt","wb+");
		FILE* recieved_from_server_for_debugging = fopen("from_server_for_debugging.txt","wb+");
		FILE* recieved_from_client = fopen("from_client_for.txt","wb+");
		FILE* recieved_from_server = fopen("from_server.txt","wb+");

		// check all the possible places an adress may be to connect to the server
		for (rp = res2; rp != NULL; rp = rp->ai_next) {

			// create a socket to listen to connections from the server
			file_descriptor_for_linstening_to_connections_from_server = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
			if (file_descriptor_for_linstening_to_connections_from_server == -1)
				continue;

			// CONNECT TO SERVER

			if (connect(file_descriptor_for_linstening_to_connections_from_server, rp->ai_addr, rp->ai_addrlen) != -1)
				break; // success
		}
		if (rp == NULL||file_descriptor_for_linstening_to_connections_from_server<=0) {
			fprintf(stderr, "client: failed to connect\n");
			exit(EXIT_FAILURE);
		}



        // get the file descriptor for sending to the client and connect it to the client address and my file descriptor for accepting from client
        file_descriptor_for_client = accept(file_descriptor_to_listen_to_connections_from_client, (struct sockaddr*)&client_address, &client_address_size);
        if (file_descriptor_for_client == -1){
        	        perror("accept failed");
        	        exit(EXIT_FAILURE);

        }

        // if accept works
        if(file_descriptor_for_client!=-1){
            printf("file_descriptor_for_client = %d\n", file_descriptor_for_client);



			Message message_from_client;
			char chars_of_message_from_client[257];

			// read from the file descriptor and assign straight to char
			if (read(file_descriptor_for_client, chars_of_message_from_client, 256) ==0){
					perror("read failed to string");
					exit(EXIT_FAILURE);
			}

			// write the message up to a file
			for( int g =0;g<256;g++){
				if(fprintf(recieved_from_client, "%c", chars_of_message_from_client[g])==1){
				}
			}
			rewind(recieved_from_client);

			// parse the representation of the packet received
			read_into_message(&message_from_client, recieved_from_client, file_descriptor_for_client);

			char chars[message_from_client.header.length+2];
			Message_to_string(&message_from_client, chars);


			// if the message read in from the client is not a AAAA request respond appropriately
			int QTYPE = message_from_client.question.QTYPE[0]*256 + message_from_client.question.QTYPE[1];
			if(QTYPE !=28){
				// set up time
				time_t rawtime;
				struct tm *info;
				char buffer[80];
				time( &rawtime );
				info = localtime( &rawtime );
				strftime(buffer,80,"%FT%T%z", info);
				fprintf(log, "%s" , buffer);fflush(log);
				fprintf(log, " unimplemented request\n");fflush(log);
				// respond to the client with an error code RCODE = 4
				change_RCODE(&message_from_client, 4);
				message_from_client.header.QR_to_RCODE[0] = set_bit(message_from_client.header.QR_to_RCODE[0], 1, 7);
				char message_to_client_changed[message_from_client.header.length+2];
				Message_to_string(&message_from_client, message_to_client_changed);
				n = write(file_descriptor_for_client, message_to_client_changed , message_from_client.header.length+2);
				if (n < 0) {
					perror("socket");
					exit(EXIT_FAILURE);
				}
				break;
			}

			// if the message is a AAAA log it
			time_t rawtime;
			struct tm *info;
			char buffer[80];
			time( &rawtime );
			info = localtime( &rawtime );
			strftime(buffer,80,"%FT%T%z", info);
			fprintf(log, "%s requested " , buffer);fflush(log);
			char * domain_name = name_to_string(&(message_from_client.question.QNAME));
			fprintf(log, "%s\n" , domain_name);fflush(log);


			rewind(recieved_from_client);
			for( int g =0;g<message_from_client.header.length+2;g++){
				if(fprintf(recieved_from_client_for_debugging, "%c", chars_of_message_from_client[g])==1){
				}
			}
			// rewind the file for writing to print for debugging
			rewind(recieved_from_client_for_debugging);

			// write to the sever the message received from the client
			n = write(file_descriptor_for_linstening_to_connections_from_server, chars_of_message_from_client , message_from_client.header.length+2);
			if (n < 0) {
				perror("socket");
				exit(EXIT_FAILURE);
			}


			char chars_of_message_from_server[257];
			int r = read(file_descriptor_for_linstening_to_connections_from_server, chars_of_message_from_server, 256);
			if (r==0){
					perror("read  to chars_of_message_from_server failed");
					exit(EXIT_FAILURE);
			}

			// write out to a file
			for( int g =0;g<256;g++){
					if(fprintf(recieved_from_server, "%c", chars_of_message_from_server[g])==1){
					}
			}

			rewind(recieved_from_server);


			Message message_from_server;
			read_into_message(&message_from_server, recieved_from_server, file_descriptor_for_linstening_to_connections_from_server);
			rewind(recieved_from_server);
			char * domain_name_from_server = name_to_string(&(message_from_server.question.QNAME));

			// if the message has a an answer log it appropriately
			if(message_from_server.header.ANCOUNT>0){
				// set up time
				time_t rawtime;
				struct tm *info;
				char buffer[80];
				time( &rawtime );
				info = localtime( &rawtime );
				strftime(buffer,80,"%FT%T%z", info);
				fprintf(log, "%s " , buffer);fflush(log);
				fprintf(log, "%s is at %s\n",domain_name_from_server, message_from_server.answer->ip_address );fflush(log);

			}

			for( int g =0;g<message_from_server.header.length+2;g++){
					if(fprintf(recieved_from_server_for_debugging, "%c", chars_of_message_from_server[g])==1){
					}
			}

			rewind(recieved_from_server_for_debugging);

			n = write(file_descriptor_for_client, chars_of_message_from_server , message_from_server.header.length+2);
			if (n < 0) {
				perror("socket");
				exit(EXIT_FAILURE);
			}
			close(file_descriptor_for_client);
			//close(file_descriptor_for_linstening_to_connections_from_server);
        }
	}
    close(file_descriptor_to_listen_to_connections_from_client);

}
