#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include "./includes/MatrixMultiplication.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("Usage:/ Requires at least 3 arguments, 2 file directories for multiplication");
        return 1;
    }
    matrix outputMatrix;   
	if (!TryGetMatrixData(argv[1], &outputMatrix))
    {
        printf("Matrix value failed to be saved");
        return 1;
    }
	PrintMatrixData(outputMatrix); 
    for (int count = 2; count < argc; count++)
    {
		matrix prevMatrixData = outputMatrix; 
        matrix newMatrixInput;
        if (!TryGetMatrixData(argv[count], &newMatrixInput))
        {
			FreeMatrixAllocMemory(outputMatrix); 
            printf("Matrix value failed to be saved");
            return 1;
        }
		PrintMatrixData(newMatrixInput);
        if (!GetMatrixProduct(prevMatrixData, newMatrixInput, &outputMatrix))
        {
            printf("Multiplication logic error occured");
            return 1;
        }
        FreeMatrixAllocMemory(newMatrixInput);
		FreeMatrixAllocMemory(prevMatrixData); 
    }
    PrintMatrixData(outputMatrix);
    FreeMatrixAllocMemory(outputMatrix);

    return 0; 
}