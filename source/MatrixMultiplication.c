#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>
#include "./includes/MatrixMultiplication.h"

/// @brief Attempts to access matrix buffer from a given file directory, Prints result if successful
/// @param filePath string value
/// @param outMatrix matrix struct
/// @return true if success, else false 
bool TryGetMatrixData(char *filePath, matrix *outMatrix)
{
	int titleIndex = strlen(filePath) - 4;
    char *newName = malloc(sizeof(char) * (titleIndex+1));
    if (newName == NULL)
    {
        printf("Memory Shortage : Filename %s couldn't be parsed", filePath);
        return false;
    }
	memset(newName, '\0', titleIndex+1); 
	strncpy(newName, filePath, titleIndex); 
    outMatrix->name = newName;
    FILE *input = fopen(filePath, "r");
    if (input == NULL)
    {
        printf("Failed to open file in this directory, %s", filePath);
        return false;
    }
	fscanf(input, "%d", &(outMatrix->row)); 
	fscanf(input, "%d", &(outMatrix->column)); 
    int size = outMatrix->row * outMatrix->column;
    double *matrixData = malloc(sizeof(double) * size);
    if (matrixData == NULL)
    {
        fclose(input);
        return false;
    }
    double val;
	int count = 0; 
    while (fscanf(input, "%lf", &val) != EOF)
    {
        matrixData[count++] = val;
    }
    outMatrix->data = matrixData;
    fclose(input);
    return true;
}

/// @brief Computes matrix product given two valid matrices. If format is invalid, returns 0 on row ptr
/// @param multiplicand place in previous result 
/// @param multiplier new matrix value as multiplier
/// @return matrix index with updated name, row, column and data. returns 0 on data if results are invalid. 
bool GetMatrixProduct(matrix multiplicand, matrix multiplier, matrix *outProductData)
{
    if (multiplicand.data == NULL || multiplier.data == NULL)
    {
		return false; 
    }
    int prevY = multiplicand.row;
    int prevX = multiplicand.column;
    int nextY = multiplier.row;
    int nextX = multiplier.column;
    if (prevX != nextY)
    {
        printf("MULTIPLIER: %d, %d \n", nextY, nextX);
        printf("MULTIPLICAND: %d, %d \n", prevY, prevX);
        printf("Matrix Size needs to be in order, such that A x B * C x D, B == C\n");
        return false;
    }
    int newY = prevY;
    int newX = nextX;
    double *productMatData = malloc(sizeof(double) * (newY * newX));
    if (productMatData == NULL)
    {
        printf("Line 131: Memory Shortage");
        return false;
    }

    memset(productMatData, 0.0, sizeof(double) * (newY * newX));
    for (int i = 0; i < newY; i++)
    {
        for (int j = 0; j < newX; j++)
        {
            for (int k = 0; k < nextY; k++)
            {
            	int index = i * newX + j; // i *
                int leftIndex = k + (i * nextY);
                int rightIndex =  k * newX + j;
                productMatData[index] += multiplicand.data[leftIndex] * multiplier.data[rightIndex];
            }
        }
    }

    outProductData->row = newY;
    outProductData->column = newX;

    int newNameLength = strlen(multiplicand.name)+strlen(multiplier.name) +1;
    char *newName = malloc(sizeof(char) * newNameLength);
    if (newName == NULL)
    {
		free(productMatData); 
        printf("Memory Shortage");
        return false;
    }
	strcpy(newName, multiplicand.name); 
    strcat(newName, multiplier.name);

    outProductData->data = productMatData;
    outProductData->name = newName;
    return true;
}
void PrintMatrixData(matrix inputMatrixData)
{
	char *fileName = inputMatrixData.name; 
	double *result = inputMatrixData.data; 
	int row = inputMatrixData.row; 
	int column = inputMatrixData.column; 
	printf("%s =\n", inputMatrixData.name); 
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            int index = j + (column * i);
            printf("%.2f ", result[index]);
        }
        if (i + 1 < row)
        {
            printf(" \n");
        }
    }
    printf("\n");
}
void FreeMatrixAllocMemory(matrix matrixBuffer)
{
    if (matrixBuffer.data != NULL)
    {
        free(matrixBuffer.data);
		matrixBuffer.data = NULL; 
    }
    if (matrixBuffer.name != NULL)
    {
        free(matrixBuffer.name);
		matrixBuffer.name = NULL; 
    }
}