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
int d,m,k,n; //extra variable d represents the number of input vector X to read
cin >> d >> m >> k >> n;

double X[d][m+1];
double W[k][m+1];
double U[n][k+1];
double H[k];
double A[k+1];
double T[d][n];//must correspond with X[d][m+1] to avoid repeated target
double Y[n];
double L[n];
double partialO[n];
double partialH[k+1];
double Error[n];
double Errorh[k];
double sum=0;
double lr = 0.5; //The learning rate

for(int i=0;i<d;i++){
  for(int j=0;j<m;j++)
    cin >> X[i][j];

  X[i][m] = -1;
  
  for(int k=0;k<n;k++)
    cin >> T[i][k];//takes targets w.r.t input n
}
//Where the algorithm starts
/*
*This marks the beggining of the forward propagation
*/
for(int input =0;input<d;input++){//for each input vector X
  //Initialize weights to random values for both layers
    for(int out=0;out<n;out++){
      for(int i=0;i<k+1;i++){
  //Weight fot the hidden layer
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
    for(int j=0;j<k;j++){
      for(int l=0;l<m+1;l++){
        H[j] += W[j][l]*X[input][l];
      }
  //applying the sigmoid function
      A[j] = 1/(1+exp(-H[j])); 
      A[k] = -1; //Augment vector a with zero
    }
  //Now the final part
    cout << "Output for Input " << input+1 << ":\n";
    for(int i=0;i<n;i++){
      L[i] = 0;
      for(int j=0;j<k+1;j++){
        L[i]+=U[i][j]*A[j];
        cout << "(" << U[i][j] << ")" << "(" << A[j] << ")";
        if(j!=k)
          cout << "+";
      }
      Y[i] = 1/(1+exp(-L[i]));
    // Error[i] = (T[i]-Y[i])*Y[i]*(1-Y[i]);//Error at output string
      cout << " = " << L[i] << " => Y = " << Y[i] << endl;
    }
    cout <<endl;
    //Backward propagation
    for(int i=0;i<n;i++){
      partialO[i] = Y[i]*(1.0-Y[i])*(T[input][i]-Y[i]);
    }

    for(int j=0;j<k;j++){
      sum=0;
      for(int a=0;a<n;a++){
        sum+=U[a][j]*partialO[a];
      }
      partialH[k] = A[j]*(1.0-A[j])*sum; 
    }
    //Update the weights
    for(int i=0;i<n;i++){
      for(int j=0;j<=k;j++){
        U[i][j] = U[i][j]+lr*partialO[i]*A[j];
      }
    }
    for(int i=0;i<k;i++){
      for(int j=0;j<=m;j++){
        W[i][j] = W[i][j]+lr*partialH[i]*X[input][j];
      }
    }
  }
}