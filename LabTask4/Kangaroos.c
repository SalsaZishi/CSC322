//-----------------------------------------------------------------------------
// Zishi Wu
// October 1, 2015
// Kangaroos.c
//-----------------------------------------------------------------------------
/* This program calculates the expected number of kangaroo casualties on an 
 * Australian road, given the number of kangaroos, the length of the road,
 * and the length of the side of the land (assumed to be a square).
 */
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h> 

#define ROADKILL_CONSTANT 1.47     
#define ROAD_WIDTH .01 

//-----------------------------------------------------------------------------
float calcKangarooDensity(int numKangaroos, float lengthOfSide);
float calcRoadSurfaceArea(float lengthOfRoads);
//-----------------------------------------------------------------------------
int main(void) {

  float lengthOfSide;
  float lengthOfRoads;
  int numKangaroos;
  float expectedKills;
  
  printf("Enter side of square in km: ");
  scanf("%f", &lengthOfSide);
  
  printf("Enter road length in km: ");
  scanf("%f", &lengthOfRoads);
  
  printf("Enter number of kangaroos: ");
  scanf("%d", &numKangaroos);
  
  expectedKills = calcKangarooDensity(numKangaroos, lengthOfSide)
                * calcRoadSurfaceArea(lengthOfRoads) * ROADKILL_CONSTANT;
				
  printf("Expected number of kills is: %.1f\n", expectedKills);
  
  return(EXIT_SUCCESS);
}
//-----------------------------------------------------------------------------
/* Returns a float value equal to the expected number of kangaroos per 
 * square mile
 */
float calcKangarooDensity(int numKangaroos, float lengthOfSide) {

  float density;
  density = numKangaroos / (lengthOfSide * lengthOfSide);
  return(density);
}
//-----------------------------------------------------------------------------
/* Returns a float value equal to the area of the road 
 */
float calcRoadSurfaceArea(float lengthOfRoads) {

  float area;
  area = lengthOfRoads * ROAD_WIDTH;
  return(area);
}
//-----------------------------------------------------------------------------
