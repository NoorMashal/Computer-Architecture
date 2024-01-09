#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 11
#define FRAC_SZ 52

int main(int argc, char *argv[]) {

    // SETUP
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    double value;
    fscanf(fp, "%lf", &value);
  



    bool sign = value<0.0;
    printf("%d_",sign);


    double fraction = sign ? -value : value;

    unsigned short bias = (1<<(EXP_SZ-1))-1;

    signed int exp = 0;

    unsigned short e = 0;

      if(fraction >= 1.0){
      
        for ( int i = 1; i <= 1023; i++){

          if ( fraction < 2 ) break;

          fraction = fraction/2;
          exp = i;

        }
         e = exp + bias;
      }
      else if(fraction < 1.0 && fraction != 0.0 ){
      
        for ( int i = -1; i >= -1023; i--){

          if ( fraction >= 1) break;

          fraction = fraction*2;
          exp = i;
        }
        e = exp + bias;

      }
      else{
         e = 0;
      }

      if ( e == 0) fraction = fraction/2;

      for (int i = 10; i >= 0; i--) {
      
        printf("%d", 0b1 & e>>i);
      }

      printf("_");

    bool frac_array[FRAC_SZ+1]; // SKIP LSB FOR ROUNDING

      for ( int frac_index=FRAC_SZ; 0<=frac_index; frac_index-- ) {

        if(fraction >= 1) fraction = (fraction -1);

          if( 2* (fraction) >= 1){
            frac_array[frac_index] = true;
          }
          else{
            frac_array[frac_index] = false;
          }

          fraction = fraction*2;
      }



    for ( int frac_index=FRAC_SZ-1; 0<=frac_index; frac_index-- ) {

          bool frac_bit = frac_array[frac_index+1]; // SKIP LSB
          printf("%d", frac_bit);
      }

}