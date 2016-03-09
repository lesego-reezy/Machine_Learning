#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

int main(){
	int d,m,k,n;
	cin >> d >> m >> k >> n;

  double X[d][m+1];
  double W[k][m+1];
  double U[n][k+1];
  double A[d][k+1];
  double T[n];
  double Y[n];
  double sum=0;

  for(int i=0;i<d;i++){
  	for(int j=0;j<m;j++){
  		cin >> X[i][j];
  	}
  	X[i][m] = -1;
  	cin >> T[i];

  	for(int p=0;p<k+1;p++){
  		if(!m==3){
  		U[i][p] = ((rand()%20)/10)-1;
     	}else{
     	cin >> U[i][p];
     	}
  		A[i][p] = 0;
  	}
  	A[i][k] = -1;
  }
  //Where the algorithm starts

  for(int i=0;i<k;i++){
  	for(int j=0;j<m+1;j++){
  		if(m!=3)
  		W[i][j] = ((rand()%20)/10)-1;
 		else
 		cin >> W[i][j];
  	}
  }

  //Calculate the matrix a
  for(int i=0;i<d;i++){
  	for(int j=0;j<k;j++){
  		for(int l=0;l<m+1;l++){
  			A[i][j] += W[j][l]*X[i][l];
  			cout << "(" << W[j][l] << ")" << "(" << X[i][l] << ")";
  			if(l!=m)
  				cout << "+";
  		}
  		cout << " = " << A[i][j] ;
  	   //applying the sigmoid function
  		A[i][j]=1/(1+exp(-A[i][j]));
  		cout << " => " << A[i][j] <<endl;
  	}
  }
  //Now the final part
  for(int i=0;i<n;i++){
  	sum=0;
  	for(int j=0;j<k+1;j++){
  		sum+=U[i][j]*A[i][j];
  		cout << "(" << U[i][j] << ")" << "(" << A[i][j] << ")";
  			if(j!=k)
  			 cout << "+";
  	}
   Y[i] = 1/(1+exp(-sum));
   cout << " = " << sum << " => Y = " << Y[i] << endl;
  }
}