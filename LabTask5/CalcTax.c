//-----------------------------------------------------------------------------
// Zishi Wu
// October 15, 2015
// CalcTax.c
//-----------------------------------------------------------------------------
/* This is a simplified tax calculator. The user inputs positive numbers 
 * representing income and negative numbers representing deductions. These
 * are summed and then evaluated to assess the user's income bracket, which
 * will then determine what rate their income will be taxed. The results 
 * of these computations are then printed.
 */
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

// income brackets
#define SUPER_RICH 500000  
#define QUITE_RICH 200000
#define MIAMI_POOR 100000
#define AVERAGE 50000
#define REALISTIC 20000     
#define POOR 20000  

// tax rate for various income brackets
#define SUPER_RICH_RATE .25
#define QUITE_RICH_RATE .25
#define MIAMI_POOR_RATE .10
#define AVERAGE_RATE .03
#define REALISTIC_RATE .03
#define POOR_RATE 0.0 

// tax ceiling
#define MAX_TAX 50000 
//---------------------------------------------------------------------------------
// METHODS DECLARED
void IncomeAndDeduction(float *income, float *deduction);
float computeTaxable(float income, float deduction);
char taxGroup(float taxable);
float computeTax(char group, float taxable);
void display(float income, float deduction, float taxable, char group, float tax);
//---------------------------------------------------------------------------------
/* Include pointers on the input variables for this function since it will update 
 * the values of income and deduction based on the positive and negative values 
 * that the user inputs.
 */
void IncomeAndDeduction(float *income, float *deduction){
	
	float nextAmount = 1.0; 
  
	while (nextAmount != 0.0) {
    printf("Enter next amount: ");
	 	scanf("%f", &nextAmount);
      if (nextAmount > 0) {
    	  *income += nextAmount;
    	} else {
        *deduction += abs(nextAmount);
    	}
  }
}
//----------------------------------------------------------------------------------
/* Returns the amount of the taxable income, which equals income minus deduction
 * If taxable income is less than zero, then return 0. Of course, a person who 
 * has negative money (loses money) probably needs aid, not taxes.
 */
float computeTaxable(float income, float deduction){
	
  	float taxableIncome = income - deduction;
  	if (taxableIncome < 0) {
	 	return 0.0;
	  } 
  	return taxableIncome;
}
//-----------------------------------------------------------------------------------
/* Returns a capital letter that signifies the tax group the user belongs to,
 * based on their taxable income.
 */
char taxGroup (float taxable) {
	
char group;
	if (taxable >= SUPER_RICH) {
		group = 'S';
	} else if (taxable >= QUITE_RICH) {
		group = 'Q';
	} else if (taxable >= MIAMI_POOR) {
		group = 'M';
	} else if (taxable >= AVERAGE) {
		group = 'A';
	} else if (taxable >= REALISTIC) {
		group = 'R';
  	} else {  // condition is if (taxable < POOR)
		group = 'P';
	}		
	return group;	
}
//-----------------------------------------------------------------------------------
/* Returns the amount of tax that user must pay, depending on their tax group and 
 * taxable income. The maximum amount of taxes is capped at $50,000.
 */
float computeTax (char group, float taxable){

	float taxRate;
	float tax = 0.0;
  
	if (group == 'S') {
		taxRate = SUPER_RICH_RATE;
  	} else if (group == 'Q') {
    	taxRate =  QUITE_RICH_RATE;
  	} else if (group == 'M') {
  		taxRate = MIAMI_POOR_RATE;
  	} else if (group == 'A') {
		taxRate = AVERAGE_RATE;
	} else if (group == 'R') {
		taxRate = REALISTIC_RATE;
	} else { // condition is (group == 'P') 
		taxRate = POOR_RATE;
	}
	
	tax = taxable * taxRate;
	if (tax > MAX_TAX) {
		tax = MAX_TAX;
	}
	return tax;
}
//-----------------------------------------------------------------------------------
/* Display the income, deduction, taxable income, tax group, and tax owed properties
 * of user based on aggregate inputted incomes and deductions
 */
 void display(float income, float deduction, float taxable, char group, float tax) {
	printf("Income         = $%14.2f\n", income);
	printf("Deduction      = $%14.2f\n", deduction);
	printf("Taxable Income = $%14.2f\n", taxable);
	printf("Tax Group      = %c\n", group);
	printf("Tax Owed       = $%14.2f\n", tax);
}
//-----------------------------------------------------------------------------------
int main(void) {

  	float income, deduction, taxable, tax;
  	char group;
	
	// initialize then get income and deduction
	income = deduction = 0.0;
  	IncomeAndDeduction(&income, &deduction);

	// get taxable income
	taxable = computeTaxable(income, deduction);

	// get tax group
	group = taxGroup(taxable);

	// get tax owed
	tax = computeTax(group, taxable);

	// display info
	display(income, deduction, taxable, group, tax);
	
  	return(EXIT_SUCCESS);
}
//----------------------------------------------------------------------------------
