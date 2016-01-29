#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "parseCommands.h"
//----------------------------------------------------------------------------------
void parseText(Command *c, String line) {
	
	// example: /blah/Ineedle noddle noo 
	// Initialize command with line range specification of type text
	c->type = text;	

	// get pointer to char array starting with the first slash
	char *firstSlash = strchr(line, '/');
	
	// get pointer to char array starting from second slash
	char *secondSlash = strchr(firstSlash + 1, '/');
	
	// get pointer to chars between first and second slash
	char *p = strtok(firstSlash + 1, "/");
	
	// copy pattern up to 80 chars
	strncpy(c->range.pattern, p, MAX_PATTERN);
	
	// get edit operation that comes right after second slash
	c->operation = *(secondSlash + 1);
	
	// in the case of replace, /<old text>/<new text>/ has 3 char spaces taken up by '/'
	// so allow for copying of 3 more chars
	if (c->operation == 's') {
		strncpy(c->data, secondSlash+2, MAX_PATTERN+3);
	}
	strncpy(c->data, secondSlash+2, MAX_PATTERN);
}
//----------------------------------------------------------------------------------
void parsePair(Command *c, String line) {

	// example: 1,1/OThe Title
	// Initialize command with line range specification of type pair
	c->type = num;
	
	// strtol (const char *str, char **endptr, int base) converts the initial part 
	// of the string in str to a long int value according to the given base, and 
	// assigns endptr the memory address to a char array starting after the int value
	char *comma;
	char *firstSlash;
	c->range.pair[0] = strtol(line, &comma, 10);
	c->range.pair[1] = strtol(comma+1, &firstSlash, 10);
	
	// get edit operation that comes right after first slash
	c->operation = *(firstSlash + 1);
	
	// in the case of replace, /<old text>/<new text>/ has 3 char spaces taken up by '/'
	// so allow for copying of 3 more chars
	if (c->operation == 's') {
		strncpy(c->data, firstSlash+2, MAX_PATTERN+3);
	}
	strncpy(c->data, firstSlash+2, MAX_PATTERN);
}
//----------------------------------------------------------------------------------
void parseNone(Command *c, String line) {
	
	// Ex: Ahello jim
	// Initialize command with line range specification of type none
	c->type = none;	
	
	// get first char which is the edit operation
	c->operation = line[0];
	
	// in the case of replace, /<old text>/<new text>/ has 3 char spaces taken up by '/'
	// so allow for copying of 3 more chars
	if (c->operation == 's') {
		strncpy(c->data, line+1, MAX_PATTERN+3);
	}
	strncpy(c->data, line+1, MAX_PATTERN);
}
//----------------------------------------------------------------------------------
void freeCommandArray(CommandArray cArray, int size)
{
    int i = 0;
    while (i < size) 
        free(cArray[i++]);
}
//----------------------------------------------------------------------------------
char * enumToString(Command *c) {

	RangeType rt = c->type;
	switch(rt) {
	case text:
		return("text");
		break;
	case num:
		return("num");
		break;
	default:
		return("none");
		break;
	}
}
//----------------------------------------------------------------------------------
void printCommand(Command *c) {
	
	char * rangeType = enumToString(c);
	printf("Range Type: %s\n", rangeType);
	
	// print the range depending on type
	if (!strcmp(rangeType, "text")) {
        printf("Union Range: %s\n", c->range.pattern);
    } else if (!strcmp(rangeType, "num")) {
        printf("Union Range: %d,%d\n", c->range.pair[0], c->range.pair[1]);
    } else {
		printf("Union Range: none\n");
	}
	
	printf("Operation: %c\n", c->operation);
	printf("Data: %s\n\n", c->data);	
}
//----------------------------------------------------------------------------------
void printCommandArray(CommandArray cArray, int lineCount) {
	
	int i = 0;
	while (i <= lineCount) 
		printCommand(cArray[i++]);
	
}
//----------------------------------------------------------------------------------
Command * parseLine(String line) {
	
	Command *c = malloc(sizeof(Command));
	// create initial dummy command 
	c->type = text;			// default case for range type (none)
	c->operation = 'A';		// default case will be append
	c->data[0] = '\0';		// default case for data
	
	// condition for range type text
	if (line[0] == '/') {
		parseText(c, line);
	}	
	// condition for range type pair (of line numbers)
	else if (isdigit(line[0])) {
		parsePair(c, line);
	}	
	// condition for range type none
	else {
		parseNone(c, line);
	}	
	return c;
}		
//----------------------------------------------------------------------------------
int getCommands(char *fileName, CommandArray cArray) {

	// open file
    FILE *f = fopen(fileName, "r");
    if (f == NULL) {
        perror("Error: Unable to open commands file");
        exit(0);
    }
    // extract commands	
	int lineCount = -1;
	String nextLine;
	while (fgets(nextLine, MAX_STRING, f) != NULL) {
		lineCount++;
		nextLine[strlen(nextLine)-1] = '\0';
        cArray[lineCount] = parseLine(nextLine);	
	}	
	// close file
	fclose(f); 

	// return length of cArray
	return lineCount+1;
}
//----------------------------------------------------------------------------------
