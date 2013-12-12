#ifndef LC4_MEMORY_H
#define LC4_MEMORY_H

struct row_of_memory {
	unsigned int address;
	char * label;
	short unsigned int contents;
	struct row_of_memory *next;
 }; 

struct row_of_memory* create_list_label(int address, char * label);
struct row_of_memory* create_list_contents(int address, short unsigned int contents);
struct row_of_memory* add_to_list_label(int address, char * label);
struct row_of_memory* add_to_list_contents(int address, short unsigned int contents);
int                   delete_from_list(int address) ;
void				  delete_list() ;
struct row_of_memory* search_list(int address) ;
void                  print_list () ;



#endif
