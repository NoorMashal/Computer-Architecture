#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23



int main(int argc, char *argv[]) {

    // float value = *(float *) &binary; // you are not allowed to do this.
    // unsigned int binary = *(unsigned int*) &value; // you are not allowed to do this.

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    float product = 1.0;


    for(int i = 0; i < 2; i++){

      char buff;
      char sign = 0;
      int e = 0;
      float m = 0.0;


      for (int i=EXP_SZ+FRAC_SZ; 0<=i; i--) { // read MSB first as that is what comes first in the file
          /* ... */
          fscanf(fp, "%c", &buff);

          if( i == EXP_SZ+FRAC_SZ ){
            if(buff - 48) sign = 1;
          }
          else if(i >= FRAC_SZ){
            e = e + (buff - 48)* pow(2, i - 23);
          }
          else{
              m =  m + (buff - 48)* pow(2, i - 23);
          }
      }

      if( e != 0 && e != 255){
        e = e - 127;
        m =  m + 1;
      }
      else{
        e = 1 - 127;
      }
      double number = ldexp ( m, e );
      number = sign ? -number : number;
      product = product*number;
      fscanf(fp, "%c", &buff);

    }

    bool sign = product<0.0;
    printf("%d_",sign);

    double frac = sign ? -product : product;

    unsigned short bias = (1<<(EXP_SZ-1))-1;

    signed int exp = 0;

    unsigned short e = 0;

      if(frac >= 1.0){

        for ( int i = 1; i <= 127; i++){

          if ( frac < 2 ) break;
          exp = i;
          frac = frac/2;

        }
         e = exp + bias;
      }
      else if(frac < 1.0 && frac != 0.0 ){

        for ( int i = -1; i >= -127; i--){

          if ( frac >= 1) break;
          exp = i;
          frac = frac*2;
        }
        e = exp + bias;

      }
      else{
         e = 0;
      }

      if ( e == 0) frac = frac/2;

      for (int i = 7; i >= 0; i--) {
        /* code */
        printf("%d", 0b1 & e>>i);
      }

      printf("_");

    bool frac_array[FRAC_SZ+1]; // one extra LSB bit for rounding

      for ( int i=FRAC_SZ; 0<=i; i-- ) {

        if(frac >= 1) frac = (frac -1);

          if( 2* (frac) >= 1){
            frac_array[i] = true;
          }
          else{
            frac_array[i] = false;
          }

          frac = frac*2;
      }



    for ( int frac_index=FRAC_SZ-1; 0<=frac_index; frac_index-- ) {
        int x  = frac_index+1;
          bool frac_bit = frac_array[x]; // skipping the extra LSB bit for rounding
          printf("%d", frac_bit);
      }
    return(EXIT_SUCCESS);

}