#ifndef PARSE_COMMANDS_H
#define PARSE_COMMANDS_H

//----Define types of variables-----------------------------------------------------------------

// define Pattern to hold <text> we are searching for that can be up to 80 chars 
#define MAX_PATTERN 80		
typedef char Pattern[MAX_PATTERN];

// Each line of input, and output after editing, will be maximally 256 characters long
#define MAX_STRING 256		
typedef char String[MAX_STRING];

/* There are three types of line range specifications: 
 *	   1. <text> range that applies to every line containing that <text>
 *     2. A numerical range that applies to: <start line num>,<end line num> (inclusive)
 *     3. No range specifications = applies to every line
 */
typedef enum {text, num, none} RangeType;

// define the union of line ranges
typedef union {
    Pattern pattern;     	// For text range
    int pair[2]; 			// For numerical range
	// range type none doesn't need to be defined since
	// if not the other two, then none = range
} unionRange;

// define a command 
typedef struct {
    RangeType 	type;
    unionRange 	range;
    char 		operation;
    String 		data;
} Command;

// define an array of Command Pointers to hold up to 100 commands
#define MAX_COMMANDS 100
typedef Command *CommandArray[MAX_COMMANDS];

//----Define methods to parse commands-----------------------------------------------------------------

// initializes command of range type text
// Arguments: Command *c to be initialized, String line containing info on command
void parseText(Command *c, String line);

// initializes command of range type pair
// Arguments: Command *c to be initialized, String line containing info on command
void parseNum(Command *c, String line);

// initializes command of range type none 
// Arguments: Command *c to be initialized, String line containing info on command
void parseNone(Command *c, String line);

// Gets a String nextLine and extracts specifications of the command
// Assume that all commands in myCommands.txt are formatted correctly
// Arguments: String nextLine to be parsed into a command
Command * parseLine(String nextLine);

// Free memory storing command array of length = size 
// Arguments: CommandArray cArray (array of Command pointers) to be freed, int size
void freeCommandArray(CommandArray cArray, int size);

// Convert enum of RangeType to a String (text, num, none)
// Arguments: Command *c with RangeType enum to be converted to String
char * enumToString(Command *c);

// Print an individual command within the command array
// Arguments: Command *c within the command array
void printCommand(Command *c);

// Prints contents of a Command array to make sure parseCommands works
// Arguments: CommandArray cArray to be printed, int lineCount = number of lines
void printCommandArray(CommandArray cArray, int lineCount);

// Opens command file for reading and extracts each line into the command array. 
// Returns 1 if failure. Otherwise close file and return the size of the Command Array
// Arguments: a file name to open
int getCommands(char *fileName, CommandArray c);

#endif
