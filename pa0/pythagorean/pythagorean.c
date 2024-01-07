#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]) {

  // Open the filename given as the first command line argument for reading
  FILE* fp = fopen(argv[1], "r");
  if (!fp) {
    perror("fopen failed");
    return EXIT_FAILURE;
  }

  char buf[256];

  char* string = fgets(buf, 256, fp);
  int big = atoi(string);
  char* string1 = fgets(buf, 256, fp);
  int smol = atoi(string1);
  big = big*big;
  smol = smol*smol;
  
  if (smol > big)
  {
  	int x = big;
  	big = smol;
  	smol = x;
  }
  
  int thirdSideI = (int) sqrt(big+smol);
  double thirdSideD = sqrt(big+smol);
  
  if ( (double) thirdSideI == thirdSideD )
  {
  	printf( "%d\n", (int) thirdSideI );
  }
  else
  {  	
  	thirdSideI = (int) sqrt(big-smol);
	thirdSideD = sqrt(big-smol);
	if ( (double) thirdSideI == thirdSideD )
  	{
  		printf( "%d\n", (int) thirdSideI );
  	
  	}
  	else 
  	{
  		printf( "-1" );
  	}
  }
  

  // Printing in C.
  // %d is the format specifier for integer numbers.
  // \n is the newline character
  //printf( "%d\n", big );
  //printf( "%d\n", smol);
  return EXIT_SUCCESS;

}
