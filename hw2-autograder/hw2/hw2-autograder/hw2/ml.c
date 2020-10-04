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
double* multRow(double *matMult, double scalar, int dimension);
double* addRow(double *matAdd, double *matAdd2, int dimension);
double* subRow(double *matSub, double *matSub2, int dimension);
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
    //printf("%d\n%d\n", attributesNum, trainingNums);
    double **matrix = (double **)calloc(trainingNums, sizeof(double *));
    for (size_t i=0; i<trainingNums; i++){
      matrix[i] = (double *)calloc(attributesNum, sizeof(double));
    }
    double **result = (double **)calloc(trainingNums, sizeof(double *));
    for (size_t i=0; i<trainingNums; i++){
      result[i] = (double *)calloc(attributesNum, sizeof(double));
    }
    double **temp = (double **)calloc(trainingNums, sizeof(double *));
    for (size_t i=0; i<trainingNums; i++){
      temp[i] = (double *)calloc(attributesNum, sizeof(double));
    }
    double **priceVector = (double **)calloc(trainingNums, sizeof(double));
    for (size_t i=0; i<trainingNums; i++){
      temp[i] = (double *)calloc(1, sizeof(double));
    }

    //fill the matrix and pricevector with data from input
    for (size_t i = 0; i < trainingNums; i++) {
      for (size_t j = 0; j < attributesNum; j++) {
        //printf("%s", "Num: ");
        fscanf(fp, "%lf%*c", &matrix[i][j]);
        //printf("%lf\t", matrix[i][j]);
      }
      fscanf(fp, "%lf\n", &priceVector[i][0]);
      /*printf("%s\t", "Price: ");
      printf("%lf\n", priceVector[i]);
      printf("%s\n", "New Line: ");*/
    }

    result = transposeMatrix(matrix, trainingNums, attributesNum);
    result = multiplyMatrix(result, matrix, attributesNum, trainingNums, trainingNums, attributesNum);
    result = inverseMatrix(result, attributesNum);
    temp = transposeMatrix(matrix, trainingNums, attributesNum);
    result = multiplyMatrix(result, temp, attributesNum, attributesNum, attributesNum, trainingNums);
    result = multiplyMatrix(result, priceVector, attributesNum, attributesNum, trainingNums, 1);

  for (size_t i=0; i<trainingNums; i++){
    free(matrix[i]);
  }
  free(matrix);
  free(priceVector);
  }
	return 0;
}

double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2)
{
    double** result=malloc(r1*sizeof(double*));
    for (size_t i=0; i<r1; i++){
      result[i] = (double *)calloc(r1, sizeof(double));
    }

    for (size_t i = 0; i < r1-1; i++) {
      for (size_t j = 0; j < c2-1; j++) {
        for (size_t k = 0; k < r2; k++) {
          result[i][j] += matA[i][k]*matB[k][j];
        }
      }
    }
    return result;
}


double** transposeMatrix(double** mat, int row, int col)
{
	double** matTran=malloc(col*sizeof(double*));
  for (size_t i=0; i<row; i++){
    matTran[i] = (double *)calloc(row, sizeof(double));
  }

    for (size_t i = 0; i < row; i++) {
      for (size_t j = 0; j < col; j++) {
        matTran[j][i] = mat[i][j];
      }
    }

    return matTran;
}

double* multRow(double *matMult, double scalar, int dimension){
  double* temp = calloc(dimension, sizeof(double));
  for (size_t i = 0; i < dimension; i++) {
    temp[i] = matMult[i]*scalar;
  }
  return temp;
}

double* addRow(double *matAdd, double *matAdd2, int dimension){
  double* temp = calloc(dimension, sizeof(double));
  for (size_t i = 0; i < dimension; i++) {
    temp[i] = matAdd[i] + matAdd2[i];
  }
  return temp;
}

double* subRow(double *matSub, double *matSub2, int dimension){
  double* temp = calloc(dimension, sizeof(double));
  for (size_t i = 0; i < dimension; i++) {
    temp[i] = matSub[i] - matSub2[i];
  }
  return temp;
}

double** inverseMatrix(double **matA, int dimension)
{
    double** matI=malloc(dimension*sizeof(double*));
    for (size_t i=0; i<dimension; i++){
      matI[i] = (double *)calloc(dimension, sizeof(double));
    }

    //set matI to identity
    for (size_t i = 0; i < dimension; i++) {
      for (size_t j = 0; j < dimension; j++) {
        if(i==j){
          matI[i][j] = 1.0;
        }
        else{
          matI[i][j] = 0.0;
        }
      }
    }

    double f;
    double* temp;
    double* temp2;
    for (size_t p = 0; p < dimension-1; p++) {
      f = matA[p][p];
      matA[p] = multRow(matA[p], 1.0/f, dimension);
      matI[p] = multRow(matI[p], 1.0/f, dimension);
      for (size_t i = p+1; i < dimension-1; i++) {
        f = matA[i][p];
        temp = multRow(matA[p], f, dimension);
        temp2 = multRow(matI[p], f, dimension);
        matA[i] = subRow(matA[i], temp, dimension);
        matI[i] = subRow(matI[i], temp2, dimension);
      }
    }
    for (size_t p = dimension-1; p > 0; p--) {
      for (size_t i = p-1; i > 0; i--) {
        f = matA[i][p];
        temp = multRow(matA[p], f, dimension);
        temp2 = multRow(matI[p], f, dimension);
        matA[i] = subRow(matA[i], temp, dimension);
        matI[i] = subRow(matI[i], temp2, dimension);
      }
    }
	return matI;
}
