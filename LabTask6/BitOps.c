//----------------------------------------------------------------------------------
// Zishi Wu
// October 26, 2015
// BitOps.c
//----------------------------------------------------------------------------------
/* This program contains 3 macro expressons: 
 * 1) Check if X is an odd number
 * 2) Check if the Nth digit (starting from 0) of X is turned on (digit = 1)
 * 3) Check if all digits of X from S to E are on 
 
 * For an in-depth explanation on the 3rd macro expression, check out the 
 * Explanations file. This task involves a lot of thinking in binary.
 */ 
//----------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#define ODD(X) ((X) & 01)
#define BITON(X,N) ((X) & (1<<N))
#define ALLON(X,S,E) ( ((X) & ( (1<<(E+1))-(1<<(S)) )) == ( (1<<(E+1))-(1<<(S)) ) )
//-----------------------------------------------------------------------------------
int main(void) {

    unsigned int U1,BitNumber,Start,End;

    printf("Enter an integer : ");
    scanf("%ud",&U1);
    printf("%u is %s\n",U1,ODD(U1)?"odd":"even");

    printf("Enter an integer and a bit number : ");
    scanf("%u %d",&U1,&BitNumber);
    printf("%u has bit %d %s\n",U1,BitNumber,BITON(U1,BitNumber)?"on":"off");

    printf("Enter an integer, start and end bit numbers : ");
    scanf("%u %u %u",&U1,&Start,&End);
    printf("%u has %s those bits on\n",U1,ALLON(U1,Start,End)?"all":"not all");

    return(EXIT_SUCCESS);
}
//----------------------------------------------------------------------------------
