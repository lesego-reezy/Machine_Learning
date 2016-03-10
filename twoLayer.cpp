#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

double sigmoid(double,double);

int main(){
/*Takes in the number of X vectors as d
*The number of inputs or elements of X as m
*The number of nodes for the hidden layer as k
*The number of outputs Y as n
* Read when everything manually, first give a list vectors X
* followed by the U weights 
* then the W weights
*/
srand(time(NULL));
int d,m,k,n; //extra variable d represents the number of input vector X to read
cout << "Please input the number of inputs, datapoint, nodes, and outputs\nin the form: \nd m k n";
cout << "\nwhere d=inputs,m = datapoints, k = nodes,and n = outputs" << endl;
cin >> d >> m >> k >> n;

double X[d][m+1];//d input vectors with m data points 
double W[k][m+1];//layer weights
double U[n][k+1];//hidden layer weights
double H[k];//Threshold
double A[k+1];//Activation function values correspoding to the threshhold
double T[d][n];//must correspond with X[d][m+1] to avoid repeated target
double Y[n];//Out puts
double L[n];//
double partialO[n];
double partialH[k+1];
double Error[d]; // error of the network
double sum=0;
double lr = 0.5; //The learning rate

for(int i=0;i<d;i++){
  for(int j=0;j<m;j++)
    cin >> X[i][j];//input vector X = [x1,...,xm]

  X[i][m] = -1; //augment -1 so X = [x1,...,xm,-1]
  
  for(int k=0;k<n;k++)
    cin >> T[i][k];//takes targets w.r.t input n
}
//array for randomizing input order
vector<int> order;
order.resize(m+1);
for(int i=0;i<=m;i++){
  order[i] = i;
}
//Where the algorithm starts
/*
*This marks the beggining of the forward propagation
*/
cout << "Number of nodes = " << k <<endl;
for(int input =0;input<d;input++){//for each input vector X and target T
    cout << "Output for Input " << input+1 << ":\n\t";
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
  // run for 100 iterations
  for(int iteration=0;iteration<10;iteration++){
    //randomize order of inputs
    random_shuffle(order.begin(),order.end());

  //Calculate the threshold 
    for(int j=0;j<k;j++){
      H[j] = 0;
      for(int l=0;l<m+1;l++){//calculate W*x = h=[h1,...,hp]
        H[j] += W[j][l]*X[input][order[l]];
      }
      A[j] = sigmoid(1,H[j]);//apply the activation function
                             // get a=[g(h1),...,g(hp)] 
      A[k] = -1; //Augment vector a with -1
    }
    for(int i=0;i<n;i++){
      L[i] = 0;
      for(int j=0;j<k+1;j++){//calculate U*a
        L[i]+=U[i][j]*A[j]; // get l = [l1,...,ln]
      }
      Y[i] = sigmoid(1,L[i]);//apply the activation function
    }
    //Backward propagation
    for(int i=0;i<n;i++){
      partialO[i] = Y[i]*(1.0-Y[i])*(T[input][i]-Y[i]);//partial w.r.t U
    }
    //second partial
    for(int j=0;j<k;j++){
      sum=0;
      for(int a=0;a<n;a++){
        sum+=U[a][j]*partialO[a];
      }
      partialH[k] = A[j]*(1.0-A[j])*sum; 
    }
    //Update the weights for the hidden layer
    for(int i=0;i<n;i++){
      for(int j=0;j<=k;j++){
        U[i][j] = U[i][j]+lr*partialO[i]*A[j];
      }
    }
    //update weight for the first layer
    for(int i=0;i<k;i++){
      for(int j=0;j<=m;j++){
        W[i][j] = W[i][j]+lr*partialH[i]*X[input][j];
      }
    }
    //calculate the error
    sum = 0;
    for(int i = 0;  i < n; i++)
        sum += pow(T[input][i] - Y[i],2);
    //Hence the error for (X,T) on the network
    Error[input] = 0.5*sum;   
  }
  cout << "\tWeights" << endl;
   for(int node=0;node<k;node++){  
  //Weight for the first layer
    cout << "\tNode: " << node << endl;
    cout << W[node][0] << ", " ;
      for(int j=1;j<m+1;j++){
        cout << W[node][j];
      }
      cout << endl;
    }
  cout << "\tError = " << Error[input] << endl; 
 }
}

double sigmoid(double beta,double h){
  return 1/(1+exp(-beta*h));
}