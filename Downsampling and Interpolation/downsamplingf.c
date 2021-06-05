/******************************************************************************************************************************************
Purpose: To downsample the data in the file 'out1_test0.csv' by taking every 50th point and then regenerating the intermediate points by interpolation using cubic splines and and comparing the root mean square error between the actual data set and the interpolated points.
Authors: Karthikeyan (EE19B103), Shashank Nag (EE19B118), Surya Prasad S. (EE19B121)
Date   : 4th September,2019
Input  : The data from the file 'out1_test0.csv'.
Output : 
*******************************************************************************************************************************************/


#include <stdio.h>
#include <math.h>

int xi;
double p[502], q[502], L[50];

void printMatrix(int m, int n, double matrix[m][n]);
void tridiagonalCubicSplineGen(int n, double h[n], double a[n - 1][n], double y[n + 1]);
void gaussEliminationLS(int m, int n, double a[m][n], double x[n - 1]);  //Function to perform Gauss elimination
void cSCoeffCalc(int n, double h[n], double sig[n + 1], double y[n + 1], double a[n], double b[n], double c[n], double d[n]);
void cerror();  //Function to find RMS error

void main()
{
    double y[50], h[49], result, temp2; //y array to store the y-axis points, h array to store the successive interval widths
    int x[50], temp1; //x array to store x-axis points, temp variables are for taking in the values from the file

    FILE* fptr;
    fptr = fopen("datapoints_downsampled.txt", "r");

    for (int i = 0; i < 50; i++) {
        fscanf(fptr, "%d\n%lf", &temp1, &temp2);
        x[i] = temp1;
        y[i] = temp2;
        
    }

    fclose(fptr);

    for (int i = 0; i < 49; i++) {
        h[i] = x[i + 1] - x[i];
    }

    double a[49], b[49], c[49], d[49]; //arrays to store the a,b,c,d values
    double sig[50]; //array to store Si's
    double sigTemp[48]; //array to store the Si's except S0 and Sn
    double tri[48][49]; //matrix to store the tridiagonal system of equations that will solve for Si's
    for(int i=0;i<48;i++){
        for(int j=0;j<49;j++){
            tri[i][j]=0;
        }
    }
    sig[0] = 0;
    sig[49] = 0;

    tridiagonalCubicSplineGen(49, h, tri, y); //to initialize tri[n-1][n]
    gaussEliminationLS(48, 49, tri, sigTemp); //Perform Gauss Elimination

    for (int i = 1; i < 49; i++) {
        sig[i] = sigTemp[i - 1];
    }

    FILE* fptr2;
    fptr2 = fopen("result.txt", "w");

    cSCoeffCalc(49, h, sig, y, a, b, c, d); //calculate the values of ai's, bi's, ci's, and di's

    for (int i = 0; i < 49; i++) {
        for (int j = (i * 10); j < ((i + 1) * 10); j++) {
            printf("%lf             %lf         %lf            %lf \n",a[i],b[i],c[i],d[i]);    
            result = a[i] * pow((j - x[i]), 3) + b[i] * pow((j - x[i]), 2) + c[i] * (j - x[i]) + d[i];

            fprintf(fptr2, "%lf\n", result);
        }
    }

    cerror();
}


/*****************************
Function to calculte RMS error
******************************/
void cerror()
{
    double x1, x2, e = 0;

FILE *fptr1, *fptr2;    
    fptr1 = fopen("samplef.txt", "r");
    fptr2 = fopen("out1_test0.txt", "r");

    while (fscanf(fptr1, "%lf\n", &x1) != EOF) {
        fscanf(fptr2, "%lf\n", &x2);
        e += ((x1 - x2) * (x1 - x2));
    }

    e /= 502;
    e = pow(e, 0.5);
    printf("   %lf", e);
}


/************************************
Function to perform Gauss elimination
************************************/
void gaussEliminationLS(int m, int n, double a[m][n], double x[n - 1])
{   double term;
    int i, j, k;
    for (i = 0; i < m - 1; i++) {

        //Begin Gauss Elimination
        for (k = i + 1; k < m; k++) {
            term = a[k][i] / a[i][i];
            for (j = 0; j < n; j++) {
                a[k][j] = a[k][j] - term * a[i][j];
            }
        }
    }


    //Begin Back-substitution
    for (i = m - 1; i >= 0; i--) {
        x[i] = a[i][n - 1];
        for (j = i + 1; j < n - 1; j++) {
            x[i] = x[i] - a[i][j] * x[j];
        }
        x[i] = x[i] / a[i][i];
    }
}


/********************
Cubic Spline coefficients calculator
Function that calculates the values of ai, bi, ci, and di's for the cubic splines: ai(x-xi)^3+bi(x-xi)^2+ci(x-xi)+di
********************/
void cSCoeffCalc(int n, double h[n], double sig[n + 1], double y[n + 1], double a[n], double b[n], double c[n], double d[n])
{
    int i;
    for (i = 0; i < n; i++) {
        d[i] = y[i];
        b[i] = sig[i] / 2.0;
        a[i] = (sig[i + 1] - sig[i]) / (h[i] * 6.0);
        c[i] = (y[i + 1] - y[i]) / h[i] - h[i] * (2 * sig[i] + sig[i + 1]) / 6.0;
    }
}


/********************
Function to generate the tridiagonal augmented matrix 
for cubic spline 
********************/
void tridiagonalCubicSplineGen(int n, double h[n], double a[n - 1][n], double y[n + 1])
{
    int i;
    for (i = 0; i < n - 1; i++) {
        a[i][i] = 2 * (h[i] + h[i + 1]);

    }
    for (i = 0; i < n - 2; i++) {
        a[i][i + 1] = h[i + 1];
        a[i + 1][i] = h[i + 1];
    }
    for (i = 1; i < n; i++) {
        a[i - 1][n - 1] = (y[i + 1] - y[i]) * 6.0 / (double)h[i] - (y[i] - y[i - 1]) *( 6.0 / (double)h[i - 1]);
    }

}



