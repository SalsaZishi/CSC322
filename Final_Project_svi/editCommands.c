#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "parseCommands.h"
//----------------------------------------------------------------------------------
int checkRange(Command *c, String line, int lineNum) {	
	
	// check if this command applies to this line
	switch (c->type) {
		// if String pattern is a substring of line
		case text: 
			if (strstr(line, c->range.pattern))
				return 1;
			break;
		// if lineNum is included in the pair of start/end line numbers
		case num:
			if ((c->range.pair[0]) <= lineNum && (c->range.pair[1] >= lineNum)) 
				return 1;
			break;
		// if command has range type none, do edit
		case none:
			return 1;
			break;
		default:	
			break;
	}
	// otherwise, don't perform edit
	return 0;
}
//----------------------------------------------------------------------------------
void replaceText(String data, String line, String temp) {

	// extract /<old text>/<new text>/ - Working
	String holder;
	memcpy(holder, data, sizeof(String));
	char *old = strtok(holder, "/");
    char *new = strtok(NULL, "/");
	
	// while line contains <old text>, replace
	while ( strstr(line, old) ) {
		// printf("contains old text: %s\n", old);
		char *string = line;
		char *substring = strstr(string, old);
		int startIndex = substring - string;
		// printf("start index: %d\n", startIndex);
		
		// Find index where <old text> starts in line 
		strncpy(temp, line, startIndex);
		// copy chars from line up to but not including start index into temp
		strncat(temp, new, strlen(new));
		// copy the substring that comes after <old text> into temp, up to 256 chars
		strncat(temp, substring+strlen(substring), MAX_STRING - strlen(temp));	
		// Finally copy contents of temp into line
		strncpy(line, temp, strlen(temp));
	}
}
//----------------------------------------------------------------------------------
void doEdit(Command *c, String line) {
	
	// The edited standard input is output to standard output. Each line of input, 
	// and output after editing, will be maximally 256 characters long
	String temp = "";
	switch (c->operation) {
		case 's':
			// replace <old text> with <new text>. 
			replaceText(c->data, line, temp);
			break;
		case 'A':
			// Append at end of line - Working		
			// Copy contents of c->data into line, up to strlen(line) = 256
			// if strlen(data) + strlen(line) exceeds 256, copy only the first 256 - strlen(line) chars
			if ( strlen(c->data) + strlen(line) >= MAX_STRING ) {
				strncat(line, c->data, MAX_STRING - strlen(line));
			} else {	
				strncat(line, c->data, strlen(c->data));
			}			
		break;
		case 'I':		
			// Insert at start of line - Working	
			// First copy contents from String data into temp
			// printf("data: %s.end\n", c->data);
			strncpy(temp, c->data, strlen(c->data));
			
			// Then copy contents from String line into temp, up to strlen(temp) = 256
			strncat(temp, line, MAX_STRING - strlen(temp));	
			
			// Finally copy contents of temp into line
 			strncpy(line, temp, MAX_STRING);			
		break;
		case 'O':		
			// Insert at new line before current line - Working	
			if ( c->data[strlen(c->data)-1] == '\n' ) 
				c->data[strlen(c->data)-1] = '\0';

			// Simply print out the data which will come before String line
			printf("%s\n", c->data);		
		break;		
		default:
			break;
	}
}
//----------------------------------------------------------------------------------
