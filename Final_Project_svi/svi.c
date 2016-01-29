//----------------------------------------------------------------------------------
// Zishi Wu
// December 04, 2015
// svi.c
//
// Final Project: Create a Stream Editor called svi
//---------------------------------------------------------------------------------	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parseCommands.h"
#include "editCommands.h"
//----------------------------------------------------------------------------------	
int main (int argc, char *argv[]) {

	// User should input 2 arguments: svi and myCommand.txt
	// Otherwise, return following error message
	if (argc != 2) {
		printf("Proper syntax is: ./svi myCommands.txt\n");
		exit(1);
	}
	// Remember that CommandArray is an array of Command Pointers
	CommandArray cArray;
	int arraySize = 0;
		
	// open the file, extract commands into array, print out commands, close file, 
	// and return array size
	arraySize = getCommands(argv[1], cArray);

	String line;
	int lineNum = 1;
	int delete, commandNum;
	// while not at EOF of standard output
	while (fgets(line, MAX_STRING, stdin) != NULL ) {
		commandNum = 0;
		delete = 0;	
		// for each edit command that is not deleted
		while ( commandNum < arraySize ) {		
			// if checkRange returns 1, then perform edit command on line
			if ( checkRange(cArray[commandNum], line, lineNum) ) {
				
				// if command is delete operation, terminate the loop
				if (cArray[commandNum]->operation == 'd') {
					delete = 1;
					break;			
				}		
				// otherwise perform edit 
				doEdit(cArray[commandNum], line);
			}
			commandNum++;
		}	
		if ( line[strlen(line)-1] == '\n' ) 
			line[strlen(line)-1] = '\0';		

		// if line is not deleted, print line
		if (delete == 0) 
			printf("%s\n", line);
		
		lineNum++;
	}
	// free command array
	freeCommandArray(cArray, arraySize);
	
    return(EXIT_SUCCESS);
}
//----------------------------------------------------------------------------------
