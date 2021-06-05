/**********************************************************************************************************************
***********************************************************************************************************************

Let u=x'     v=y'

equations













************************************************************************************************************************
*******************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>


void euler()
{
int N=200000;
double x[200000];
double y[200000];
double u[200000];
double v[200000];
/*
x=malloc(N*sizeof(double));
y=malloc(N*sizeof(double));
u=malloc(N*sizeof(double));
v=malloc(N*sizeof(double));
*/


const double w2=1.467;//////omega square
const double ws=0.021697;//// 2 omega' sin(phi)   -4 0
double dt=0.01;///////////////////////////////////Step time size

//Setting initial values


x[0]=0.67;
y[0]=0;
u[0]=0;
v[0]=0;

	FILE *fptr=fopen("eulerfocault.txt","w");
	
	for(int i=0;i<N-1;i++)
	{
		x[i+1]=x[i]+(u[i]*dt);
		y[i+1]=y[i]+(v[i]*dt);
		u[i+1]=u[i]+(dt*(-(w2*x[i])+(v[i]*ws)));
		v[i+1]=v[i]+(dt*(-(w2*y[i])-(u[i]*ws)));
		
		fprintf(fptr,"%lf %lf\n",x[i+1],y[i+1]);
	}

system("gnuplot -p 'euler.gnu'");/////////////////////////////////Calling the file which has the instructions for gnuplot. So the plot will directly be stored in the folder as a jpeg file

}


void heun()
{
int N=100000;
double x[100000];
double y[100000];
double u[100000];
double v[100000];
/*
x=malloc(N*sizeof(double));
y=malloc(N*sizeof(double));
u=malloc(N*sizeof(double));
v=malloc(N*sizeof(double));
*/


const double w2=1.467;//////omega square
const double ws=0.021697;//// 2 omega' sin(phi)   -4 0
double dt=0.01;///////////////////////////////////Step time size

//Setting initial values


x[0]=0.67;
y[0]=0;
u[0]=0;
v[0]=0;
double xp,yp;
	FILE *fptr=fopen("heunfocault.txt","w");
	
	for(int i=0;i<N-1;i++)
	{
		xp=x[i]+(dt*u[i]);
		u[i+1]=u[i]+(dt*(-(w2*xp)+(v[i]*ws)));
		x[i+1]=x[i]+(dt/2)*(u[i]+u[i+1]);
		
		yp=y[i]+(dt*v[i]);
		v[i+1]=v[i]+(dt*(-(w2*yp)-(u[i]*ws)));
		y[i+1]=y[i]+(dt/2)*(v[i]+v[i+1]);

/*
		u[i+1]=u[i]+(dt/2)*((-(w2*x[i])+(v[i]*ws))+(-(w2*x[i+1])+(v[i+1]*ws)));
		v[i+1]=v[i]+(dt/2)*((-(w2*y[i])+(u[i]*ws))+(-(w2*y[i+1])-(u[i+1]*ws)));
*/		
		fprintf(fptr,"%lf %lf\n",x[i+1],y[i+1]);
	}

system("gnuplot -p 'heun.gnu'");/////////////////////////////////Calling the file which has the instructions for gnuplot. So the plot will directly be stored in the folder as a jpeg file

}

void rungekutta()
{
int N=50000;
double x[50000];
double y[50000];
double u[50000];
double v[50000];
/*
x=malloc(N*sizeof(double));
y=malloc(N*sizeof(double));
u=malloc(N*sizeof(double));
v=malloc(N*sizeof(double));
*/


const double w2=1.467;//////omega square
const double ws=0.021697;//// 2 omega' sin(phi)   -4 0
double dt=0.01;///////////////////////////////////Step time size

//Setting initial values


x[0]=0.67;
y[0]=0;
u[0]=0;
v[0]=0;
dt=0.01;
double k1x,k1y,k1u,k1v,k2x,k2y,k2u,k2v,k3x,k3y,k3u,k3v,k4x,k4y,k4u,k4v;
	FILE *fptr=fopen("rungefocault.txt","w");
	
	for(int i=0;i<N-1;i++)
	{

		k1x=dt*u[i];
		k1y=dt*v[i];
		k1u=dt*(-w2*x[i]+v[i]*ws);
		k1v=dt*(-w2*y[i]-u[i]*ws);

		k2x=dt*(u[i]+(k1u/2));
		k2y=dt*(v[i]+(k1v/2));
		k2u=dt*(-w2*(x[i]+(k1x/2))+(v[i]+(k1v/2))*ws);	
		k2v=dt*(-w2*(y[i]+(k1y/2))-(u[i]+(k1u/2))*ws);

		k3x=dt*(u[i]+(k2u/2));
		k3y=dt*(v[i]+(k2v/2));
		k3u=dt*(-w2*(x[i]+(k2x/2))+(v[i]+(k2v/2))*ws);	
		k3v=dt*(-w2*(y[i]+(k2y/2))-(u[i]+(k2u/2))*ws);

		k4x=dt*(u[i]+(k3u));
		k4y=dt*(v[i]+(k3v));
		k4u=dt*(-w2*(x[i]+(k3x))+(v[i]+(k3v))*ws);	
		k4v=dt*(-w2*(y[i]+(k3y))-(u[i]+(k3u))*ws);

		x[i+1]=x[i]+(k1x/6)+(k2x/3)+(k3x/3)+(k4x/6);
		y[i+1]=y[i]+(k1y/6)+(k2y/3)+(k3y/3)+(k4y/6);		
		u[i+1]=u[i]+(k1u/6)+(k2u/3)+(k3u/3)+(k4u/6);
		v[i+1]=v[i]+(k1v/6)+(k2v/3)+(k3v/3)+(k4v/6);


		fprintf(fptr,"%lf %lf\n",x[i+1],y[i+1]);
	}

system("gnuplot -p 'runge.gnu'");/////////////////////////////////Calling the file which has the instructions for gnuplot. So the plot will directly be stored in the folder as a jpeg file

}


void rk45()
{
int N=200000;
double x[200000];
double y[200000];
double u[200000];
double v[200000];
/*
x=malloc(N*sizeof(double));
y=malloc(N*sizeof(double));
u=malloc(N*sizeof(double));
v=malloc(N*sizeof(double));
*/


const double w2=0.1467;//////omega square
const double ws=0.0021697;//// 2 omega' sin(phi)   -4 0
double dt=0.1;///////////////////////////////////Step time size

//Setting initial values


x[0]=0.67;
y[0]=0;
u[0]=0.005;
v[0]=0.005;
dt=0.001;
double k1x,k1y,k1u,k1v,k2x,k2y,k2u,k2v,k3x,k3y,k3u,k3v,k4x,k4y,k4u,k4v,k5x,k5y,k5u,k5v,k6x,k6y,k6u,k6v,e=100000,xinter;
	FILE *fptr=fopen("rk45focault.txt","w");
	
	for(int i=0;i<N-1;i++)
	{

		k1x=dt*u[i];
		k1y=dt*v[i];
		k1u=dt*(-w2*x[i]+v[i]*ws);
		k1v=dt*(-w2*y[i]+u[i]*ws);

		k2x=dt*(u[i]+(k1u/4));
		k2y=dt*(v[i]+(k1v/4));
		k2u=dt*(-w2*(x[i]+(k1x/4))+(v[i]+(k1v/4))*ws);	
		k2v=dt*(-w2*(y[i]+(k1y/4))-(u[i]+(k1u/4))*ws);

		k3x=dt*(u[i]+((3/32)*k1u+(9/32)*k2u));
		k3y=dt*(v[i]+((3/32)*k1v+(9/32)*k2v));
		k3u=dt*(-w2*(x[i]+((3/32)*k1x+(9/32)*k2x))+(v[i]+((3/32)*k1v+(9/32)*k2v))*ws);	
		k3v=dt*(-w2*(y[i]+((3/32)*k1y+(9/32)*k2y))-(u[i]+((3/32)*k1u+(9/32)*k2u))*ws);

		k4x=dt*(u[i]+((1932/2197)*k1u-(7200/2197)*k2u+(7296/2197)*k3u));
		k4y=dt*(v[i]+((1932/2197)*k1v-(7200/2197)*k2v+(7296/2197)*k3v));
		k4u=dt*(-w2*(x[i]+((1932/2197)*k1x-(7200/2197)*k2x+(7296/2197)*k3x))+(v[i]+((1932/2197)*k1v-(7200/2197)*k2v+(7296/2197)*k3v))*ws);	
		k4v=dt*(-w2*(y[i]+((1932/2197)*k1y-(7200/2197)*k2y+(7296/2197)*k3y))-(u[i]-((1932/2197)*k1u-(7200/2197)*k2u+(7296/2197)*k3u))*ws);

		k5x=dt*(u[i]+((439/216)*k1u-(8)*k2u+(3680/513)*k3u-(845/4104)*k4u));
		k5y=dt*(v[i]+((439/216)*k1v-(8)*k2v+(3680/513)*k3v-(845/4104)*k4v));
		k5u=dt*(-w2*(x[i]+((439/216)*k1x-(8)*k2x+(3680/513)*k3x-(845/4104)*k4x))+(v[i]+((439/216)*k1v-(8)*k2v+(3680/513)*k3v-(845/4104)*k4v))*ws);	
		k5v=dt*(-w2*(y[i]+((439/216)*k1y-(8)*k2y+(3680/513)*k3y-(845/4104)*k4y))-(u[i]-((439/216)*k1u-(8)*k2u+(3680/513)*k3u-(845/4104)*k4u))*ws);


		k6x=dt*(u[i]+(-(8/27)*k1u+(2)*k2u+(3544/2565)*k3u+(1859/4104)*k4u-(11/40)*k5u));
		k6y=dt*(v[i]+(-(8/27)*k1v+(2)*k2v+(3544/2565)*k3v+(1859/4104)*k4v-(11/40)*k5v));
		k6u=dt*(-w2*(x[i]+(-(8/27)*k1x+(2)*k2x+(3544/2565)*k3x+(1859/4104)*k4x-(11/40)*k5x))+(v[i]+(-(8/27)*k1v+(2)*k2v+(3544/2565)*k3v+(1859/4104)*k4v-(11/40)*k5v))*ws);	
		k6v=dt*(-w2*(y[i]+(-(8/27)*k1y+(2)*k2y+(3544/2565)*k3y+(1859/4104)*k4y-(11/40)*k5y))-(u[i]-(-(8/27)*k1u+(2)*k2u+(3544/2565)*k3u+(1859/4104)*k4u-(11/40)*k5u))*ws);


		x[i+1]=x[i]+(16*k1x/135)+(6656*k3x/12825)+(28561*k4x/56430)-(9*k5x/50)+(2*k6x/55);
		y[i+1]=y[i]+(16*k1y/135)+(6656*k3y/12825)+(28561*k4y/56430)-(9*k5y/50)+(2*k6y/55);		
		u[i+1]=u[i]+(16*k1u/135)+(6656*k3u/12825)+(28561*k4u/56430)-(9*k5u/50)+(2*k6u/55);
		v[i+1]=v[i]+(16*k1v/135)+(6656*k3v/12825)+(28561*k4v/56430)-(9*k5v/50)+(2*k6v/55);

		xinter=x[i]+(25*k1x/216)+(1408*k3x/2565)+(2197*k4x/4104)-19*k5x/5;
		//dt=dt*(0.840896*pow((e*dt/(abs(x[i+1]-xinter))),0.25));

		fprintf(fptr,"%lf %lf\n",x[i+1],y[i+1]);
	}

system("gnuplot -p 'rk.gnu'");/////////////////////////////////Calling the file which has the instructions for gnuplot. So the plot will directly be stored in the folder as a jpeg file

}



void main()
{


	euler();
	heun();
	rungekutta();
	rk45();
}


	


