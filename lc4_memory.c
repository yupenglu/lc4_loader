#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lc4_memory.h"

/* notice, this linked list manipulates global pointers */
/* this isn't the best implementation if you wish to have
   more than 1 linked list instance in main () */

struct row_of_memory *head = NULL ;
struct row_of_memory *curr = NULL ;
struct row_of_memory *left = NULL ;
struct row_of_memory *right = NULL ;
int insert_at_head = 0 ;

struct row_of_memory* create_list_label(int address, char * label)
{
	/* create a list if the input is a label */
	struct row_of_memory* ptr =
		malloc(sizeof(struct row_of_memory));

	if (ptr == NULL)
	{
		fprintf (stderr, "ERROR: create_list: malloc failed") ;
		return NULL ;
	}
	memset(ptr, 0, sizeof(struct row_of_memory));

	ptr->address = address ;
	ptr->label = label;
	ptr->next  = NULL ;
	ptr->contents = 0;

	head = curr = ptr;
	return ptr ;

}

struct row_of_memory* create_list_contents(int address, short unsigned int contents)
{
	/* create a list if the input is a content */
	struct row_of_memory* ptr =
		malloc(sizeof(struct row_of_memory));

	if (ptr == NULL)
	{
		fprintf (stderr, "ERROR: create_list: malloc failed") ;
		return NULL ;
	}
	memset(ptr, 0, sizeof(struct row_of_memory));

	ptr->address = address ;
	ptr->label = NULL;
	ptr->contents = contents;
	ptr->next  = NULL ;

	head = curr = ptr ;
	return ptr ;
}


struct row_of_memory* add_to_list_label(int address, char * label)
{
	/* add a label to the memory list */
	struct row_of_memory* ptr = NULL ;

	// see if list exists, if not, create & return
	if (head == NULL)
		return (create_list_label(address, label)) ;

	// search the address provided in the memory list
	ptr = search_list(address);

	if (ptr == NULL)
	{
		if (insert_at_head == 0)
		{	
			// case of not inserting at head
			// allocate memory for new node
			ptr = malloc(sizeof(struct row_of_memory));
			if (ptr == NULL)
			{
				fprintf (stderr, "ERROR: add_to_list: malloc failed") ;
				return NULL ;
			}
			memset(ptr, 0, sizeof(struct row_of_memory));

			// insert the new node
			left->next = ptr;
			ptr->next = right ;
			ptr->address = address ;
			ptr->label = label ;
		}		
		else
		{
			// allocate memory for new node
			// memset(ptr, 0, sizeof(struct row_of_memory));
			ptr = malloc(sizeof(struct row_of_memory));
			if (ptr == NULL)
			{
				fprintf (stderr, "ERROR: add_to_list: malloc failed") ;
				return NULL ;
			}
			memset(ptr, 0, sizeof(struct row_of_memory));

			// insert the new node
			ptr->next = head;
			head = ptr;
			ptr->address = address ;
			ptr->label = label ;
		}
	}
	else
	{
		// if at given address memory is not empty, simply add/change the label
		// at given address
		ptr->label = label ;
	}

	return ptr ;
}

struct row_of_memory* add_to_list_contents(int address, short unsigned int contents)
{
	/* add a label to the memory list */
	struct row_of_memory* ptr = NULL ;

	// see if list exists, if not, create & return
	if (head == NULL)
		return (create_list_contents(address, contents)) ;

	// search the address provided in the memory list
	ptr = search_list(address);

	if (ptr == NULL)
	{
		if (insert_at_head == 0)
		{	
			// case of not inserting at head
			// allocate memory for new node

			ptr = malloc(sizeof(struct row_of_memory));
			if (ptr == NULL)
			{
				fprintf (stderr, "ERROR: add_to_list: malloc failed") ;
				return NULL ;
			}
			memset(ptr, 0, sizeof(struct row_of_memory));

			// insert the new node
			left->next = ptr ;
			ptr->next = right ;
			ptr->address = address ;
			ptr->contents = contents ;
		} 
		else
		{
			// allocate memory for new node
			ptr = malloc(sizeof(struct row_of_memory));			
			if (ptr == NULL)
			{
				fprintf (stderr, "ERROR: add_to_list: malloc failed") ;
				return NULL ;
			}
			memset(ptr, 0, sizeof(struct row_of_memory));

			// insert the new node
			ptr->next = head;
			head = ptr;
			ptr->address = address ;
			ptr->contents = contents ;
		}
	}
	else
	{
		// if at given address memory is not empty, simply add/change the content
		// at given address
		ptr->contents = contents ;
	}
	return ptr ;
}

struct row_of_memory* search_list(int address)
{
	/* searches for 1st instance of value
	   a weak search mechanism at best.
	   returns 1st node that matches search
	*/

	struct row_of_memory* ptr = head ;
	struct row_of_memory* tmp = NULL ;
	insert_at_head = 0 ;
	left = head;
	right = left->next ;

	while(ptr != NULL)
	{
		if (ptr->address == address) {
			return ptr ;
		} else if (ptr->address < address) {
			// don't move left at the first time
			if (left != ptr)
				left = left->next ;
			ptr = ptr->next ;
		} else {
			if (left == ptr)
				insert_at_head = 1 ;
			return NULL ;
		}
		right = left->next ;
	}
	return NULL ;
}

int delete_from_list(int address)
{
	// pointers to perform surgery on list with
	struct row_of_memory *ptr = head  ;
	struct row_of_memory *prev = NULL ;
	int found = 0 ;

	/* search list for 1st instance of "value" */
	/* yes...we could have just called our search! */
	while(ptr != NULL)
	{
		if(ptr->address == address) {
			found = 1 ;	 // we have found it!
			break ;		 // break out of while loop
		} else {
			prev = ptr ;
			ptr = ptr->next ;
		}
	}

	/* perform surgery on the list (remove item) */
	if (found == 1 ) {
		if (ptr == head)				// if "value" was in head node,
			head = head->next ;			//  re-point the head to 2nd node
		else 							// otherwise,
			prev->next = ptr->next ; 	// re-point the node before "node to delete"
										//  to node after "node to delete"

		if (ptr == head && ptr==curr)	// update "current" pointer
			curr=head ;					// if curr equaled old head ptr
		if (ptr == curr)
			curr=prev ;					// if curr equaled any other node
	}
	else return 1 ;						// if found = 0, don't do any surgery!

	/* surgery complete, return memory to heap */
	free (ptr) ;
	ptr = NULL ;

	return 0 ;
}

void delete_list()
{
	struct row_of_memory *ptr = NULL ;

	// must free node by node
	// but don't accidentally delete head node!
	while (head != NULL )
	{
		ptr = head ;
		head = ptr->next ;
		free (ptr) ;
	}

}

void print_list()
{
	/* print the memory contents in a formatted way */

	struct row_of_memory* ptr = head ;
	int longLabel = 0 ;		// use longLabel indicator for print out alignment

	// print the header of the memory table
	printf ("\n<label>\t\t<address>\t<contents>\n" );

	// when ptr == NULL, we reach the end of the linked list
	while (ptr != NULL )
	{
		//	 print label
		if (ptr->label != NULL)
			printf("%s", ptr->label);

		// determine whether the label is longer than a tab (8 spaces)
		if (ptr->label == NULL)
			longLabel = 0;
		else if (strlen(ptr->label) > 8)
			longLabel = 1;

		// print the label, address and contents
		if (longLabel)
			printf ("\t%04X\t\t%04X\n", ptr->address, ptr->contents) ;
		else
			printf ("\t\t%04X\t\t%04X\n", ptr->address, ptr->contents) ;

		// if label is present, free the corresponding heap memory
		if (ptr->label != NULL) {
			free (ptr->label);
			ptr->label = NULL;
		}

		// go to next row of memory
		ptr = ptr->next ;
	}
	printf("\n");
	return ;
}
