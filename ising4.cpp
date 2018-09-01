#include<iostream>
#include<math.h>
#include<cstdlib>
#include<ctime>
#include<fstream>
int rand();
using namespace std;

double Energy(int H[1000][1000],int D)
{
double eu=0,ed=0,el=0,er=0,e=0;; int i,j,k,ii,jj,kk;
for(i=0;i<D;i++)
	{
	for(j=0;j<D;j++)//ii CONTROLS THE NEXT LATTICE POINT ALONG i,SIMILARLY jj
		{
			if(i==0)
				eu=H[i][j]*H[D-1][j];
			else
				eu=H[i][j]*H[i-1][j];
			if(i==D-1)
				ed=H[i][j]*H[0][j];
			else
				ed=H[i][j]*H[i+1][j];
			if(j==0)
				el=H[i][j]*H[i][D-1];
			else
				el=H[i][j]*H[i][j-1];
			if(j==D-1)
				er=H[i][j]*H[i][0];
			else
				er=H[i][j]*H[i][j+1];

			e+=eu+ed+er+el;
			
		}
	}
//e=e/(D*D);	
return (-e/2);
}

void Copy(int h1[1000][1000],int h2[1000][1000],int d)//COPIES ONE MATRIX TO ANOTHER
{
int i,j,k;
for(i=0;i<d;i++)
for(j=0;j<d;j++)
h2[i][j]=h1[i][j];
}

void Show(int H[1000][1000],int d)//pRINTS
{
int i,j,k;
for(i=0;i<d;i++)
{for(j=0;j<d;j++)
{if(H[i][j]==1)
cout<<"|"<<" ";
else
cout<<"-"<<" ";}
cout<<"\n";}
cout<<"\n\n";
return;
}


double Mag(int h[1000][1000],int d)//CALCULATES THE MAGNETIZATION
{
int i,j,m=0;
for(i=0;i<d;i++)
for(j=0;j<d;j++)
{m+=h[i][j];}//SUM OF ALL THE INDIVIDUAL SPIN VALUES
return abs(m);
}


int main()
{
srand(time(NULL));
int H1[1000][1000],H2[1000][1000];//H1 AND H2 CONTAIN THE MATRIX. H2 IS CHANGED AND COMPARED WITH H1
int i,j,k,D,n=0;//D AND n HOLD THE DIMENSION AND COUNTER FOR EvsN RESPECTIVELY
double r,E1=0,E2=0;//E1 AND E2 HOLD THE ENERGIES OF H1 AND H2 MATRICES
double mag=0,avgmag=0;//Takes on the values of total magnetization and average magnetization
int t,T;//t HOLD THE UPPER LIMIT FOR TEMPERATURE, T IS THE CHANGING TEMPERATURE
int tt;
cout<<"Input the dimension-";cin>>D;//iNPUTS FOR DIMENSION
cout<<"\nInput the starting temperature (times 100)-";cin>>t;//INPUT FOR UPPER LIMIT OF TEMPERATURE

ofstream out1;
out1.open("EvsN4.rtf");
ofstream out2;
out2.open("TvsM4.rtf");

for(i=0;i<D;i++)//ASSIGNING THE SPINS FOR THE LATTICE
{	for(j=0;j<D;j++)
	{
		r=((double)rand()/RAND_MAX);
		if(r>0.5)
			H1[i][j]=1;
		else
			H1[i][j]=-1;
	}
}
long c=0;//counts the number to be averaged

for(T=t;T>=0;T-=5)//CHANGING TEMPERATURE
{	
	c=0;mag=0;avgmag=0;n=0;//REINITIALIZE THE VARIABLES FOR EACH VALUE OF T
	for(k=1;k<=1000;k++)
	{
		for(i=0;i<D;i++)
		{	
			for(j=0;j<D;j++)
			{		
				H2[i][j]=-H2[i][j];//CHANGNG THE MATRIX
				E2=Energy(H2,D);//CALCULATES THE ENERGY OF THE NEW MATRIX
			//	Show(H1,D);
			//	Show(H2,D);
			//	cout<<E1<<"  "<<E2<<"  "<<exp((E2-E1)*100/T)<<"\n";
				r=((double)rand()/RAND_MAX);
				if(E2<E1)
					Copy(H2,H1,D);//Copy H2 to H1. So H1 now has the new config. 
				else if((E2>E1)&&(exp(((E1-E2)*100)/T)>r))
					Copy(H2,H1,D);//IF THE CONDITION IS MATCHED COPY H2 TO H1.
				else
					Copy(H1,H2,D);//If the above two conditions are false then replace the modified H2 with the original matrix and then contin

				E1=Energy(H1,D);		
				if((T==t)&&(n<10000))
				{
					n++;
					out1<<n<<"\t"<<E1<<"\n";
				}
				if(k>100)
				{
					mag+=(double)((Mag(H1,D))/(D*D));
					c++;
				}
				
			}
		}
	}
	cout<<"\nTemperature="<<T<<"  "<<"Energy="<<E1<<"\n";
//	Show(H1,D);
//	mag=mag*mag;
//	mag=sqrt(mag);
	avgmag=mag/c;//AVERAGE MAGNETIZATION
	out2<<T<<"\t"<<avgmag<<"\n";
}
}
			
