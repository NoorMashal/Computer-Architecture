#include <stdlib.h>
#include <stdio.h>
#include <float.h>

double fabs(double value) 
{
    return value < 0.0 ? -value : value;
}

int main(int argc, char *argv[]) {
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    double x;
    fscanf(fp, "%lf", &x);

    size_t n;
    fscanf(fp, "%ld", &n);

    double precision;
    fscanf(fp, "%lf", &precision);

    double guessMin = 0.0;
    double guessMax = x < 1.0 ? 1.0 : x;
    double guessAverage = (guessMin + guessMax) / 2.0;

    double err = DBL_MAX;

    while (precision/100 < fabs(err)) 
    {
        double power = 1.0;

        for (size_t i = 0; i < n; i++) 
        {
            power *= guessAverage;
        }

        err = power - x;

        if (err > 0) 
        {
            guessMax = guessAverage;
        } else 
        {
            guessMin = guessAverage;
        }

        guessAverage = (guessMin + guessMax) / 2.0;

    }

    printf("%.*f", DBL_DIG, guessAverage);

    return EXIT_SUCCESS;
}