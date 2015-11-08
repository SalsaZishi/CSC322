//-----------------------------------------------------------------------------
// Zishi Wu
// October 4, 2015
// Scuba.c
//-----------------------------------------------------------------------------
/* This program calculates the balance of oxygen versus nitrogen that a 
 * scuba diver's tank should have. An oxygen partial pressure of 1.4 or 
 * greater will result in the program returning a character after 'N',
 * meaning that the mixture of oxygen in the diver's tank is too strong.
 */
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h> 

#define FEET_PER_ATMOSPHERE 33     
#define MAX_PARTIAL_PRESSURE 1.4
#define CONTIGNENCY_PARTIAL_PRESSURE 1.6 

//-----------------------------------------------------------------------------
float calcAmbientPressure(int depth);
float calcOxyPressure(int oxyPercent, float ambientPressure);
void calcPartialPressure(float oxyPressure);
char calcOxyGroup(float oxyPressure);
//-----------------------------------------------------------------------------
int main(void) {

  int depth, oxyPercent;
  float ambientPressure, oxyPressure;
  char oxyGroup;
  
  printf("Enter depth and percentage O2: ");
  scanf("%d %d", &depth, &oxyPercent);
  
  ambientPressure = calcAmbientPressure(depth);
  printf("Ambient Pressure: %.1f\n", ambientPressure);
  
  oxyPressure = calcOxyPressure(oxyPercent, ambientPressure);
  printf("O2 Pressure: %.2f\n", oxyPressure);
  
  oxyGroup = calcOxyGroup(oxyPressure);
  printf("O2 Group: %c\n", oxyGroup);

  calcPartialPressure(oxyPressure);
  
  return(EXIT_SUCCESS);
}
//-----------------------------------------------------------------------------
float calcAmbientPressure(int depth) {

  float pressure = (depth * 1.0 / FEET_PER_ATMOSPHERE) + 1;
  return(pressure);
}
//-----------------------------------------------------------------------------
float calcOxyPressure(int oxyPercent, float ambientPressure) {

  float pressure = ( oxyPrecent / 100.0 ) * ambientPressure;
  return pressure;
}
//-----------------------------------------------------------------------------
void calcPartialPressure(int oxyPressure) {

  printf("Exceeds maximal O2 pressure: ");
    if (oxyPressure > MAX_PARTIAL_PRESSURE) { 
      printf("true\n");
	} else {
      printf("false\n");
    }
  printf("Exceeds contingency O2 pressure: ");
    if (oxyPressure > CONTINGENCY_PARTIAL_PRESSURE) {  
      printf("true\n");
	} else {
      printf("false\n");
    }
}
//-----------------------------------------------------------------------------
/* Returns a char representing the oxygen group based on oxygen pressure.
 * A is [0.0, 0.1)		0.0 to anything less than 0.1
 * B is [0.1, 0.2)		0.1 to anything less than 0.2
 * C is [0.2, 0.3)  	0.2 to anything less than 0.3
 * ...
 * N is [1.3, 1.4)		1.3 to anything less than 1.4
 * Anything after N is too strong
 *
 * 'A' is our starting/anchor value. To convert a float into a char, we first
 * cast it into an int. Then we do an arithmetic operation on the casted int 
 * with a char to convert it into a char.
 */
char calcOxyGroup(float oxyPressure) {

  char group = ((int)(oxyPressure * 10) + 'A');
  return(group);
}
//-----------------------------------------------------------------------------
