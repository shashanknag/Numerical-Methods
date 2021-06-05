/**************************************************************************************************************************************************************************
***************************************************************************************************************************************************************************
Purpose: To plot Predator Prey Model in gnuplot
Authors: Shashank Nag (EE19B118), M. Vigneshwaran (EE19B037), G Ch Sairam (EE19B081)
Inputs: None
Output: The program generates predator and prey values and puts them into file and calls gnuplot to plot them. Also predator vs time and prey vs time are plotted in same manner 
	3 jpeg file with the file names "PredatorPrey.jpeg"  "Prey.jpeg"  "Predator.jpeg" will be saved in the folder.
Date: 26/09/19
**************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>

void ppm(); // predator prey model


void main()
{
 ppm();
}




void ppm()
{
 double a=1.2,b=0.6,c=0.8,p=0.3,t=0.1,x[300],y[300]; // declaring all variable



 x[0]=2;// setting intial value of x
 y[0]=1;// setting initial value of y
 int i=0;

 FILE *fptr1, *fptr2 , *fptr3;// declaring 3 file pointers for three file namely .....
 
 fptr1 = fopen("A.txt","w");//Predator vs Prey
 fptr2 = fopen("B.txt","w");//Prey vs Time
 fptr3 = fopen("C.txt", "w");//Predator vs Time

 
 for(i=0;i<300;i++)
 {
  x[i+1]=x[i] + (a*x[i]-b*x[i]*y[i])*t;
  y[i+1]=y[i] + (-c*y[i]+p*x[i]*y[i])*t;
  fprintf(fptr1,"%lf %lf \n ",x[i],y[i]);
  fprintf(fptr2, "%lf %lf \n", i*t,x[i]);
  fprintf(fptr3, "%lf %lf \n", i*t,y[i]);
}


system("gnuplot -p 'D.txt'");/////////////////////////////////Calling the file which has the instructions for gnuplot. So the plot will directly be stored in the folder as a jpeg file
 }




