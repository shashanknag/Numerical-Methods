#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 10000
//for N cells
//Safely assuming buffer consists of both the half maximas at a time

//Validation from ssc left
//FInding meandata left
//Finding real time median left
// Applying noise filter left

void hmfinder(int x1,double y1,int x2, double y2,double y,double x)
{
	
	x=x1+ (y-y1)*(x2-x1)/(y2-y1);

}


void main()
{
	const double thresh=2700;
	double lowerpeak[3],upperpeak[3];//Stores value[1] and the corresponding real timecount[0] and location in buffer[2]    ////.....////check efficiency
	double lowerpeakhm,upperpeakhm; //Values to be calculated based on lowerpeak, upperpeak and average	
	double hm[2];//Stores the two points of half maximas of lower[0] and upper peaks[1]
	int fwhm;
	int *celllocations;//Stores location of cells, i.e., average of lowerpeak[1] and upperpeak[1]........................increment it after storing
	int *peakwidths;// Stores the fwhm,...........increment it after storing
	int timecount=-1;//Independent variable keeps updating on each iteration
	double curtime;	//Stores time of current peak
	double prevtime;	//Stores time of previous peak
	double junk;//useless
	double meantime;     /// mean of time between cells or peaks...........in real time
	double mediantime;	//median of same ............. in real time but don't know how to do
	double meanfwhm;		//mean of fwhm    in real time
	double meandata=2700; // mean of entire fsc data
	int j=0;
	int flag=0,flag2=0;



	celllocations=malloc(N*sizeof(int));
	peakwidths=malloc(N*sizeof(int));

	double circqueue[40][2];// [0] stores time [1] stores value
	int firstin=0;
	int lastin=0;
	int secondlastin=0;
	int thirdlastin=0;

	FILE *fptr;
	fptr=fopen("CompleteData_fsc_ssc_10um.txt","r");//////////////////////////////////////////////////////////check for test file
	
//Filling up buffer first


	while(fptr!=EOF)
	{

		timecount++;

///////////////////////////////////////////////////assuming it has reached steady state
/////////////////////////////////////////////////////////////////////////////////////////

		if(firstin<=999&&firstin>0)
		{
			fscanf(fptr,"%lf %lf",&circqueue[firstin][1],&junk);
			circqueue[firstin][0]=timecount;
			thirdlastin=secondlastin;	
			secondlastin=lastin;		
			lastin=firstin;
			firstin--;
			
		}
		else if(firstin==0)
		{
			fscanf(fptr,"%lf %lf",&circqueue[firstin][1],&junk);
			circqueue[firstin][0]=timecount;
			thirdlastin=secondlastin;
			secondlastin=lastin;			
			lastin=firstin;
			firstin=999;
		}
		


////////////////Remove noise





//////////////////Assuming now that q1 is free of noise




		if(circqueue[secondlastin][1]<circqueue[lastin][1]&&circqueue[secondlastin][1]<circqueue[thirdlastin][1]&&(abs(circqueue[secondlastin][1]-meandata)>thresh))    //something better meandata
		{
			//Lower Peak Detected
			lowerpeak[0]=circqueue[secondlastin][0];
			lowerpeak[1]=circqueue[secondlastin][1];
			lowerpeak[2]=secondlastin;
			continue;

		}


		else if(circqueue[secondlastin][1]>circqueue[lastin][1]&&circqueue[secondlastin][1]>circqueue[thirdlastin][1]&&(abs(circqueue[secondlastin][1]-meandata)>thresh))// something better meandata
		{
			//Upper Peak Detected
			upperpeak[0]=circqueue[secondlastin][0];
			upperpeak[1]=circqueue[secondlastin][1];
			upperpeak[2]=secondlastin;

			curtime=(upperpeak[0]+lowerpeak[0])/2;	
			celllocations[j]=curtime;
			meantime=(j*meantime+(curtime-prevtime))/(j+1);
			prevtime=curtime;
			flag=0;

		}

		else
			continue;

	
			


		if(flag<5)
		{
			flag++;
			continue;
		}
		
		else  				// Finding FWHM and related computations
		{

			for(int i=lowerpeak[2];i<40;i++)
			{
				if(circqueue[i][1]>lowerpeakhm)
				{	hmfinder(circqueue[i][0],circqueue[i][1],circqueue[i-1][0],circqueue[i-1][1],lowerpeakhm,&hm[0]);             //Check disco in loop
					flag2=1;
					break;
				}
				
			}
			if(flag2!=1)
			{
				for(int i=0;i<=firstin;i++)
				{
					if(circqueue[i][1]>lowerpeakhm)
					{	hmfinder(circqueue[i][0],circqueue[i][1],circqueue[i-1][0],circqueue[i-1][1],lowerpeakhm,&hm[0]);	//Check when discontinuity in loop
						break;
					}	
				}
			}
					
			for(int i=upperpeak[2];i<=0;i--)
			{
				if(circqueue[i][1]<upperpeakhm)
				{	hmfinder(i+1,circqueue[i+1][1],i,circqueue[i][1],upperpeakhm,hm[1]);
					flag2=1;
					break;
				}
				
			}
			if(flag2!=1)
			{
				for(int i=39;i>=lastin;i--)
				{
					if(circqueue[i][1]<upperpeakhm)
					{	
						hmfinder(i+1,circqueue[i+1][1],i,circqueue[i][1],upperpeakhm,hm[1]);
						break;
					}	
				}
			}

		fwhm=(hm[1]-hm[0]);
		peakwidths[j]=fwhm;
		meanfwhm=(j*meanfwhm+fwhm)/(j+1);
		j++;
		system("cls");
		printf("Mean Time is %lf\n",meantime);
		printf("Mean FWHM is %lf",meanfwhm);
		

		}
		
///////////////////end of reading from file..while loop.. and all major processes
	}






}
