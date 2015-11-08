//----------------------------------------------------------------------------------
// Zishi Wu
// October 30, 2015
// ExtractComments.c
//----------------------------------------------------------------------------------
/* This program extracts valid comments from a file. I am hesitant to say 
 * "ALL" valid comments. There might be a clever invalid comment that my 
 * program will accidently catch. If you find such an exceptional case, be
 * sure to post of comment of that case. Always room for improving code!
 
 * For a good file to test your own program, try using the test.txt file
 * which is also located in the LabTask 7 folder. Compile your program
 * into an executable. Then redirect the test.txt file as input to the 
 * executable like so:
 * 			./executable < test.txt
 * 
 * This program was quite difficult and took 10 hours, so good luck!
 */ 
//----------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
//-----------------------------------------------------------------------------
// LabTask7: ExtractComments.c
//-----------------------------------------------------------------------------
int detect(char c1, char c2);
//-----------------------------------------------------------------------------
int detect(char c1, char c2) {
	// condition for End of Line Comment = case 0
	if (c2 == '\n')
		return 0;
	// condition for Beginning of Line Comment = case 1
	if ( (c1 == '/') && (c2 == '/') ) 
		return 1;
	// condition for Beginning of Block Comment = case 2
	else if ( (c1 == '/') && (c2 == '*') ) 
		return 2;
	// condition for End of Block Comment = case 3
	else if ( (c1 == '*') && (c2 == '/') ) 
		return 3;
	// condition for double quote = case 4
	else if (c2 == '"')
		return 4;
	// condition for single quote = case 5
	else if (c2 == '\'')
		return 5;
	// nothing we want
	else 
		return 6;
}
//-----------------------------------------------------------------------------
int main(void){

	int c1, c2;
	int BC = 0;                       /* block comment */
	int LC = 0;	    	          /* line comment */
	int dQ = 0;	                  /* double quote */
	int sQ = 0;		          /* single quote */
	int comment = 0;                  /* Are we in a comment? */
	int quote = 0;		          /* Are we in a quote? */
	int wasCommentNowEndline = 0;	  /* Was there a comment before newline? */
	int oddSingleQuote = 0;	          /* Are we in a line with odd number of single quotes? */
	int oddDoubleQuote = 0; 	  /* Are we in a line with odd number of double quotes */
	
	while ((c2 = getchar()) != EOF) {
		comment = LC || BC;
		quote = sQ || dQ;
		switch (detect(c1,c2)) {
			// End Line 
			case 0:
				// end line resets everything if we are not in a block comment
				if (!BC) {
					LC = 0;
					sQ = 0;
					dQ = 0;
				}
				/* If a comment existed in this line, print c2 = newline. 
				 * Otherwise this leads to unnecessary spacing between comments 
				 * extracted and empty newlines that represent the non-comment
				 * lines that we skipped over.
				 */
				 if (wasCommentNowEndline) {
					putchar(c2);	
					wasCommentNowEndline = 0;
				 }
				break;
			// Beginning Line Comment
			case 1:	
				/* if we're not in quotes or comments already, 
				 * then we are now in a line comment */
				if (!comment && !quote) {
					putchar(c1);
					LC = 1;
					wasCommentNowEndline = 1;
				} 
				/* if we're in an odd number of single quotes or double quotes
				 * then a comment can be made that overrides the fact that we
				 * were in a single quote since it takes two (even number)
				 * quotes to encapsulate a comment
				 */
				else if ( (oddSingleQuote) || (oddDoubleQuote) ) {
			           	putchar(c1);
				  	wasCommentNowEndline = 1;
					if ( (oddSingleQuote) ) {
					  sQ = 0;
					  LC = 1;
					}
					if ( (oddDoubleQuote) ) {
					  dQ = 0;
					  LC = 1;
					}
				}
				break;
			// Beginning Block Comment
			case 2: 
				/* if we're not in quotes or comments already, 
				 * then we are now in a block comment */
				if (!comment && !quote) {
					putchar(c1);
					BC = 1;
					wasCommentNowEndline = 1;
				}
				/* if we're in an odd number of single quotes or double quotes
				 * then a comment can be made that overrides the fact that we
				 * were in a single quote since it takes two (even number)
				 * quotes to encapsulate a comment
				 */
				else if ( (oddSingleQuote) || (oddDoubleQuote) ) {
			           	putchar(c1);
				  	wasCommentNowEndline = 1;
					if ( (oddSingleQuote) ) {
					  sQ = 0;
					  BC = 1;
					}
					if ( (oddDoubleQuote) ) {
					  dQ = 0;
					  BC = 1;
					}
				}
				break;
			// End Block Comment
			case 3: 
				/* if we're in block comment, then this closes block comment 
				 * and then we get out of block comment. We need to print 
				 * both c1 = * and c2 = /, since we reset BC = 0	
				 */
				if (BC) {
					putchar(c1);
					putchar(c2);
					BC = 0;
					wasCommentNowEndline = 1;

					// If we're in odd number of quotes and block comment is now closed,
					// we are now back into single quotes or double quotes
					if ( (oddSingleQuote) ) {
					  sQ = 1;
					}
					if ( (oddDoubleQuote) ) {
					  dQ = 1;
					}
				}
				// if we're in a line comment, then end block comment chars  must be printed
				if (LC) {
					putchar(c1);
				}
				break;	
			// Double Quote
			case 4: 	
				// if we're in double quotes already, then this new double quote
				// will close the quote so we reset dQ = 0
				if (dQ) {
					dQ = 0;
					oddDoubleQuote = 0;
				}
				// if we're not in quotes or comments already, 
				// then we are now in a double quote (odd number of double quotes)
				else if (!comment && !quote) {
					dQ = 1;
					oddDoubleQuote = 1;
				}
				break;
			// Single Quote
			case 5: 	
				// if we're in single quotes already, then this new single quote
				// will close the quote so we reset sQ = 0
				if (sQ) {
					sQ = 0;
					oddSingleQuote = 0;
				}
				// if we're not in quotes or comments already, 
				// then we are now in a single quote (odd number of single quotes)
				else if (!comment && !quote) {
					sQ = 1;
					oddSingleQuote = 1;
				}
				break;
			// Encountering none of the above characters
			default:
				break;
		}
		// If we are in a comment, print c2
		if (BC || LC) {
			putchar(c2);
		}
		// Set c1 = c2 and c2 will become next char for next iteration
		c1 = c2;
	}
	// Newline after extracted comments makes output look nicer
	putchar('\n');
	
	return(EXIT_SUCCESS);
}
//----------------------------------------------------------------------------
