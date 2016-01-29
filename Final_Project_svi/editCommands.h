#ifndef PARSE_COMMANDS_H
#define PARSE_COMMANDS_H

#include "parseCommands.h"
//----Define edit commands-----------------------------------------------------------------

// returns 1 if command range is applicable to the line, 0 otherwise
// Arguments: Command *c, String line to checked for editing, and lineNumber
int checkRange(Command *c, String line, int lineNum);

// performs edit operation on the String line
// Arguments: Command *c, String line to be edited
void doEdit(Command *c, String line);

// performs replace edit operation on the String line
void replaceText(String data, String line, String temp);

#endif
