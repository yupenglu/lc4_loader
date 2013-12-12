#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lc4_memory.h"
#define MAX_FILENAME_LEN 100


int convert(unsigned char hexNumber)
{
	/* convert a one-byte char of hexadecimal number to a unsigned integer */
	unsigned int temp = 0 ;
	switch(hexNumber) {
		case 'a':
		return 10 ;
		case 'b':
		return 11 ;
		case 'c':
		return 12 ;
		case 'd':
		return 13 ;
		case 'e':
		return 14 ;
		case 'f':
		return 15 ;	
	}
	temp = hexNumber ;
	return temp ;
}

int convertTwoByte(unsigned char hexNumber[2])
{
	/* convert a two-byte char hexadecimal number to unsigned integer */
	unsigned int temp = 0 ;
	int a = convert(hexNumber[1]) ;
	int b = convert(hexNumber[0]) ;
	temp = b * 256 + a ;
	return temp ;
}

int main()
{
	char fileName [MAX_FILENAME_LEN];
	char bufferOneByte[1] ;
	unsigned char bufferTwoByte[2] ;

	// ask user to enter the file name and then open the file
	printf ("Enter File Name\n");
	scanf ("%s", fileName);
	FILE * filePtr = fopen (fileName, "r");
	if (filePtr == NULL) {return 1;}

	// in each round read two byte in the file until reach the end of the file
	while (fread(bufferTwoByte, 2, 1, filePtr))
	{
		// if "CADE", then add to contents
	    if (bufferTwoByte[0] == 0xca && bufferTwoByte[1] == 0xde)
	    {
	    	// read address
			fread (bufferTwoByte, 2, 1, filePtr);
			int address = convertTwoByte(bufferTwoByte);

			// read length
			fread (bufferTwoByte, 2, 1, filePtr);
			int length = convertTwoByte(bufferTwoByte);

			// read contents
			for (int i = 0; i < length; i++)
			{
				fread (bufferTwoByte, 2, 1, filePtr);
				int contents = convertTwoByte(bufferTwoByte);
				add_to_list_contents(address, contents);
				address++;
			}
	    }

	    // if "DADA", then add to data
	    if (bufferTwoByte[0] == 0xda && bufferTwoByte[1] == 0xda)
	    {
	    	// read address
			fread (bufferTwoByte, 2, 1, filePtr);
			int address = convertTwoByte(bufferTwoByte);

			// read length
			fread (bufferTwoByte, 2, 1, filePtr);
			int length = convertTwoByte(bufferTwoByte);

			// read data
			for (int i = 0; i < length; i++)
			{
				fread (bufferTwoByte, 2, 1, filePtr);
				int contents = convertTwoByte(bufferTwoByte);
				add_to_list_contents(address, contents);
				address++;
			}
	    }

	    // if "C3B7", then add to label
	    if (bufferTwoByte[0] == 0xc3 && bufferTwoByte[1] == 0xb7)
	    {
	    	// read address
			fread (bufferTwoByte, 2, 1, filePtr);
			int address = convertTwoByte(bufferTwoByte);

			// read length
			fread (bufferTwoByte, 2, 1, filePtr);
			int length = convertTwoByte(bufferTwoByte);

			// allocate memory for label
			char *label;
			label = malloc(length + 1);

			// read label
			for (int i = 0; i < length; i++)
			{
				fread (bufferOneByte, 1, 1, filePtr);
				label[i] = (char)bufferOneByte[0];
			}
			// add NULL to the end of the label string
			label[length] = '\0';
			add_to_list_label(address, label);
	    }
	}
	// print out the memory list
	print_list();

	// perform delete_list to free the memory allocated
	delete_list();

	// check whether file is closed
	if ( fclose(filePtr) != 0) return 3;
 	
	return 0;
}


