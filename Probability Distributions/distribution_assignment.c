/*************************************************************************************************
Purpose: To create Gaussian,Rayleigh, Poissonian and Lorentzian Distributions from a uniform distribution(random number generator)
Authors: Shashank Nag(EE19B118), Surya Prasad(EE19B121), P Karthikeyan(EE19B103)
Date: 28/08/19
Inputs: Number of random numbers to be generated, type of distribution
Outputs: txt file containing the mid value of bin and the corresponding probability distribution
**************************************************************************************************
**************************************************************************************************/




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include<string.h>

double *z, maxi, mini, x;
double u1, u2;
void gauss();
void lorenzian();
void rayleigh();
void pois();
void bin();

void main(int argc, char** argv)
{
    x = atoi(argv[1]);
    z = malloc(x * sizeof(double));
    char ch=argv[2][0];

    srand(time(0));

    if (ch == 'g')
        gauss();
    else if (ch == 'l')
        lorenzian();
    else if (ch == 'r')
        rayleigh();
    else if (ch == 'p')
        pois();
    else
        printf("unknown distribution");

    free(z);
}

void gauss()
{
    for (int i = 0; i < x; i++) 
    {   u1 = rand() *(1.0/RAND_MAX);
        u2 = rand() *(1.0/RAND_MAX);
        z[i] = sqrt(-2.0 * log(u1)) * cos(2 * 3.14 * u2); printf("%g \n",z[i]);
    }
    bin();
}

void lorenzian()
{
    for (int i = 0; i < x; i++) 
    {   z[i] = rand() * (1.0 / RAND_MAX);
        z[i] = tan(3.14 * (z[i] - 0.5));
    }
    bin();
}

void rayleigh()
{
    for (int i = 0; i < x; i++) 
    {   z[i] = rand() * (1.0 / RAND_MAX);
        z[i] = sqrt(-2.0 * 2.303 * log(z[i]));
    }
    bin();
}

void pois()
{
    int n = 0, *y, ma, mi;
    double p = 1.0;
    y=malloc(x*sizeof(int));
    for (int i = 0; i < x; i++) 
    {   u1 = rand() * (1.0 / RAND_MAX);
        p *= u1;

        if (p > (exp(-1))) 
        {   n++;
            continue;
        }

        y[i] = n;
        n = 0;
        p = 1;
    }

    ma = y[0];
    mi = y[0];

    for (int i = 1; i < x; i++) 
    {   if (ma < y[i])
            ma = y[i];
        if (mi > y[i])
            mi = y[i];
    }
    int cntterm[ma - mi + 1];
    for (int i = mi; i <= ma; i++) 
    {   cntterm[i] = 0;
        for (int j = 0; j < x; j++)
            if (y[j] == i)
                cntterm[i]++;
    }

    cntterm[0] = 0;
    FILE* fptr;
    fptr = fopen("random.txt", "w");

    for (int i = mi; i <= ma; i++) 
        fprintf(fptr, "%d %d \n", i, cntterm[i]);
}

void bin()
{
    maxi = z[0];
    mini = z[0];

    for (int i = 1; i < x; i++) 
    {   if (maxi < z[i])
            maxi = z[i];
        if (mini > z[i])
            mini = z[i];
    }

    int numbin;
    numbin = 1 + (3.322 * log(x));
    double binsize = (maxi - mini) / numbin;
    int cntbin[numbin];

    for (int j = 0; j < numbin; j++) 
    {   cntbin[j] = 0;
        for (int i = 0; i < x; i++)
            if ((z[i] >= (mini + j * binsize)) && (z[i] < mini + (j + 1) * binsize))
                cntbin[j]++;
    }
    cntbin[numbin - 1]++;

    FILE* fptr;
    fptr = fopen("random.txt", "w");

    for (int i = 0; i <= numbin; i++) 
       fprintf(fptr, "%g %g \n", mini + ((2 * i + 1) / 2) * binsize, cntbin[i] * (1.0 / x));
    
}

