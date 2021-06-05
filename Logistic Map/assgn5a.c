/**************************************************************************************************************************************************************************
***************************************************************************************************************************************************************************
Purpose: To plot a bifurcation map (Logistic Map) for an interesting range of r
Authors: Shashank Nag (EE19B118), M. Vigneshwaran (EE19B037), G Ch Sairam (EE19B081)
Inputs: None
Output: The program prints the points corresponding to the logistic map into a file, and calls gnuplot to plot them.
	A jpeg file with the file name "logistic_map.jpeg" will be saved in the folder.
Date: 26/09/19
**************************************************************************************************************************************************************************
****************************************************************************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define n 2000

void main()
{

	int rmin=1;						//Minimum value of r
	int rmax=4;////////////////////////////////////////////////Maximum value of r
	double curx;///////////////////////////////////////////////Current value of x
	double r=rmin;/////////////////////////////////////////////stores the present value of r
	double junk[10000];////////////////////////////////////////Array to find the saturation value of x
	double steadystates[n]={0};//////////////////////////////Array to store the oscillating values of x
	int flag=0;
	int j=1;
	FILE *fptr;
	fptr=fopen("logistic_plot.txt","w");//////////////////////Opening the file to print the points into it
	float inc=0.01;	//////////////////////////////////////////Increment value of r
	while(r<=rmax)
	{
	
		junk[0]=0.5;	//////////////////////////////////Starting with 0.5
		for(int i=1;i<10000;i++)
		{
			junk[i]=r*junk[i-1]*(1-junk[i-1]);
			
		}
		curx=junk[9999];/////////////////////////////////Saturation or one of the oscillating value
		steadystates[0]=curx;
		fprintf(fptr,"%lf %lf\n",r,steadystates[0]);
		for(int i=0;i<n;i++)
		{
			flag=0;		
			curx=r*curx*(1-curx);	/////////////////Finding the oscillating values
			/////////////////////////////////////////Checking if the present value of curx has already been stored into the file
			for(int h=0;h<j;h++)
				if(curx==steadystates[h])
					flag=1;
			if(flag!=1)///////////////////////////////////////////////////////flag=1 implies the point was already stored
			{	steadystates[j]=curx;	
				fprintf(fptr,"%lf %lf\n",r,steadystates[j]);////////////////If the current value of x hasn't been stored yet, the store it into the array and subsequently into the file
				j++;////////////////////////////////////////////////////////Moving to the next element of the array in which oscillating values are to be stored		
			}

					
		}
		r+=inc;	////////////////////////////////////////////////////Incrementing the value of r
	}
	
	system("gnuplot -p 'command.gnu'");/////////////////////////////////Calling the file which has the instructions for gnuplot. So the plot will directly be stored in the folder as a jpeg file
}	
