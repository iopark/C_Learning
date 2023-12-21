#include <stdio.h>

typedef struct matrix
{
    char *name;
    int row;
    int column;
    double *data;
} matrix;

bool TryGetMatrixData(char *filePath, matrix *outMatrix);
bool GetMatrixProduct(matrix multiplicand, matrix multiplier, matrix *outProductData);
void PrintMatrixData(matrix inputMatrixData);
void FreeMatrixAllocMemory(matrix matrixBuffer);