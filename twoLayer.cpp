#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

int main(){
/*Takes in the number of X vectors as d
*The number of inputs or elements of X as m
*The number of nodes for the hidden layer as k
*The number of outputs Y as n
*
*Read when everything manually, first give a list vectors X
* followed by the U weights 
* then the W weights
*/
srand(time(NULL));
int d,m,k,n;
cin >> d >> m >> k >> n;

double X[d][m+1];
double W[k][m+1];
double U[n][k+1];
double A[d][k+1];
double T[n];
double Y[n];
double Error[n];
double Errorh[k];
double sum=0;

for(int i=0;i<d;i++){
  for(int j=0;j<m;j++){
    cin >> X[i][j];
  }
  X[i][m] = -1;
  cin >> T[i];

  for(int p=0;p<k+1;p++){
    A[i][p] = 0;
  }
  A[i][k] = -1;
}
//Where the algorithm starts
/*
*This marks the beggining of the forward propagation
*/
for(int input =0;input<d;input++){
//Initialize weights to random values for both layers
for(int out=0;out<n;out++){
  for(int i=0;i<k+1;i++){
//Weight fot the second layer
    U[out][i] = (rand()%20)/10.0-1.0;
  }
}
for(int node=0;node<k;node++){  
//Weight for the first layer
  for(int j=0;j<m+1;j++){
    W[node][j] = (rand()%20)/10.0-1.0;
  }
}

//Calculate the matrix a
for(int i=0;i<d;i++){
  for(int j=0;j<k;j++){
    for(int l=0;l<m+1;l++){
      A[i][j] += W[j][l]*X[i][l];
    }
//applying the sigmoid function
    A[i][j]=1/(1+exp(-A[i][j]));
  }
}
cout << endl;
//Now the final part
  cout << "Output for Input " << input+1 << ":\n";
  for(int i=0;i<n;i++){
    sum=0;
    for(int j=0;j<k+1;j++){
      sum+=U[i][j]*A[input][j];
      cout << "(" << U[i][j] << ")" << "(" << A[input][j] << ")";
      if(j!=k)
        cout << "+";
    }
    Y[i] = 1/(1+exp(-sum));
    Error[i] = (T[i]-Y[i])*Y[i]*(1-Y[i]);//Error at output string
    cout << " = " << sum << " => Y = " << Y[i] << endl;
  }
  cout <<endl;

  /*
   *Now backward propagation
   *
   *
   */

}

}