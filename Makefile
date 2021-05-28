dns_svr: dns_svr.c Message.c Header.c Question.c Resource_record.c NAME.c Label.c Linked_list.c util.c
	gcc -o dns_svr dns_svr.c Message.c Header.c Question.c Resource_record.c NAME.c Label.c Linked_list.c util.c -Wall
clean : 
	rm *.o *.exe *.log *.txt