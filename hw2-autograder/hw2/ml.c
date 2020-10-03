/*
 *
 * This code calculates the house price of a house by learing from
 * training data. It uses pseudo inverse of a given matrix to find the
 * weight of different features.
 *
 * Predicted Price : Y = W0 + W1*x1 + W2*X2 + W3*X3 + W4*X4
 * Weight Matrix : W = pseudoInv(X)*Y
 * pseudoInv(X) = inverse(transpose(X)*X) * transpose(X)
 *
 * weight(w) = pseudoInv(X) * Y
 * 			where	X = Input data matrix
 * 					Y = Target vector
 *
 */

#include<stdio.h>
#include<stdlib.h>

// all methods declarations
double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2);
double** transposeMatrix(double** mat, int row, int col);
double** inverseMatrix(double **matA, int dimension);

// main method starts here
int main(int argc, char** argv){

  char* filename = argv[1];
  if(fopen(filename, "r") == NULL){
    printf("error");
  }
  else{
    FILE* fp = fopen(filename, "r");
    int attributesNum;
    int trainingNums;
    fscanf(fp, "%d\t%d\n", &attributesNum, &trainingNums);
    printf("%d\n%d\n", attributesNum, trainingNums);
    double matrix[attributesNum][trainingNums];
    double priceVector[trainingNums];
    double temp = 0.0;
    for (size_t i = 0; i < trainingNums; i++) {
      for (size_t j = 0; j < attributesNum; j++) {
        printf("%s", "Num: ");
        fscanf(fp, "%lf%*c", &matrix[i][j]);
        printf("%lf\n", matrix[i][j]);
      }
    }
  }
	return 0;
}

double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2)
{
    double** result=malloc(r1*sizeof(double*));

    // your code goes here

    return result;
}


double** transposeMatrix(double** mat, int row, int col)
{

	double** matTran=malloc(col*sizeof(double*));

    // your code goes here

    return matTran;
}

double** inverseMatrix(double **matA, int dimension)
{

    double** matI=malloc(dimension*sizeof(double*));

    // your code goes here

	return matI;
}
