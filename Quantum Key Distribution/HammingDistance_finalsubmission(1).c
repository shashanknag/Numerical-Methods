/***********************************************************************************************************************
************************************************************************************************************************
Purpose  : To develop a model of Quantum Key Distribution to predict the true offset
Authors  : Shashank Nag (EE19B118), M. Vigneshwaran (EE19B037), G Ch V Sairam(EE19B081)
Inputs   : N ,number of bits in sender array ie Alice, p , probabilty of bits received by Bob , q , probability of error in received array on the command line
Outputs  : Actual and calculated offset
Date     : 12-10-2019
***********************************************************************************************************************
********************************************************************************************************************* */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void main(int *argc, char **argv)
{
	
	srand(time(0));         
	float p=atof(argv[2]); // p is probabilty of bits recceived
	float q=atof(argv[3]); // q is error probability
	int maxstep=0;

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//Generating data file with the quantum key distribution A


	int N=atoi(argv[1]); // N is total number of bits , here 1 million
	int *A;  // A is the array sender has ie Alice
        A=malloc(N*sizeof(int)); // Allocating space for A 
	
	for(int i=0;i<N;i++)
	{
		
		if(rand()%2==0)
			A[i]=0;        //This is an algorithm which assigns 0s and 1s to A in a random manner
		else
			A[i]=1;
	}
   
	printf("Please be patient....This might take a few minutes....");
        
	

	int M; // M is offset
	M=(int)((N/10)+(float)rand()*0.8*N*1.0/RAND_MAX); // M is anywhere between N/10 to N , but we have restricted here till 0.9N for logical purpose

	int *B; 
	B=malloc((N-M)*sizeof(int));// Allocating memory for B, B has N-M bits


	for(int i=0;i<N-M;i++)
	{
 		B[i]=A[i+M];  // Giving B its bits(but here there is no error bits included, error with probability q is inserted in next set of code)
	}	

	

	const int Q=q*(N-M); // Calculating number of Bits that should have error
	int num;
	for(int j=0;j<Q;j++)
	{
		num=(N-M)*(float)rand()*1.0/RAND_MAX;
		if(B[num]==0)
			B[num]=1;                          //This is an algorithm which randomly inserts error in B array
		else
			B[num]=0;
	}

	
	
	const int P= p*(N-M); //Calculating number of bits Bob receives
	int flag; // used to get unique locations , see inside for loop to see its use
	int C[2][P]; // Storing location of bit and value of bit
	int k=0;
	while(k<P)
	{
		flag=0;
		num=(int)((N-M)*(float)rand()*1.0/RAND_MAX); // a location is chosen at random
		for(int j=0;j<k;j++){
			if(C[0][k]==num)      //if the location has already been chosen it searches for another location
				flag=1;
		}
		if(flag==1)
			continue;

		C[0][k]=num;					//Storing the relative distance from the offset
		C[1][k]=B[num];                                 // The value of the bit
		k++;
		if(num>maxstep)
			maxstep=num;// this is actually a smart move to reduce compilation time
			// we get what is the largest location index whose value is altered so that we dont have to check the hamming diatance after this index as it will be 0 only 
			//printf("\n %d",maxstep);//////////////////////////////////////debug
	}
	
	
	int *hamming; // this array stores hamming distance for different values of offset which are then used to find minimum offset 
        hamming=malloc((N-maxstep)*sizeof(int));// Allocating memeory for hamming array

	
	FILE *fptr=fopen("hammingdistance.txt","w");  // declaring a file pointer to open file called hammingdistance and store offset vs hamming distance in it   


	///////////////////////////////////////////////////Now calculating hamming distance

	for(int testoffset=N/10;testoffset<=N-maxstep;testoffset++) // starting from N/10 till (N - maxstep) , maxstep is already discussed in previous comments
	{
		hamming[testoffset]=0;
		
		for(int i=0;i<P;i++)
		{
			if(A[testoffset+C[0][i]]!=C[1][i])
				hamming[testoffset]++;

		}
	fprintf(fptr,"%d %d\n",testoffset,hamming[testoffset]); // writing in file


	}
		
	///////////////////////////////////////////////////Now finding least hamming distance

	


	// Calculating least hamming distance and its index
	int minvalue=hamming[N/10];
	int mincount=N/10;
	for(int i=N/10;i<=N-maxstep;i++)
	{
		if(hamming[i]<minvalue)
		{
			minvalue=hamming[i];   
			mincount=i;
		}		
	
	
	}



	printf("The predicted offset value is %d and actual value of offset is %d",mincount,M);
	
	free(A);
	free(B);
	free(hamming);


	//Plotting in gnuplot

	FILE *pipe1;// pipe1 will plot the hamming distance vs offset
	pipe1=popen("gnuplot -persist","w");
	fprintf(pipe1, "set xlabel 'Offset'\n");	//Setting xlabel
	fprintf(pipe1, "set ylabel 'Hamming Distance'\n");	//Setting ylabel
	fprintf(pipe1, "set title 'Hamming Distance vs. Offset'\n");		//Setting title
	fprintf(pipe1, "plot 'hammingdistance.txt' u 1:2 with lines \n");

}	



	






