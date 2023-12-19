#include <stdio.h>
#include <string.h> 
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>

typedef struct matrix
{
	char *name; 
	int row; 
	int column; 
	double *flattenMatrixValue; 
} matrix; 

bool UpdateFilenameToOut(matrix newMatrix, matrix* outBuffer); 
bool SaveFilenameToOut(char *fileName, matrix *outBuffer); 
void PrintMatrixWithName(double *result, char *fileName, int row, int column); 
bool ValidateMatrixDimension(FILE* input, int *outDimensionValue);
bool MultiplyAndOverwrite(matrix *multiplicand, matrix multiplier); 
bool SaveMatrixArrayToOut(FILE *input, int matrixDimInfo[], matrix *outMatrix); 

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Usage:/ Requires 2 arguments, input file"); 
		return 1; 
	}
	FILE* input = NULL; 
	int fileCount = argc -1;
    matrix ouputBuffer; 
    ouputBuffer.name = NULL; 
    ouputBuffer.flattenMatrixValue = NULL; 

    for (int count = 1; count <= argc -1; count++)
    {
        matrix newMatrixBuffer; 
        input = fopen(argv[count], "r");
		if (input == NULL)
		{
			printf("File Not Found in Current Directory %s", argv[count]); 
			return 1; 
		}
        if (!SaveFilenameToOut(argv[count], &newMatrixBuffer))
        {
            printf(" %s Text file name insert failed", argv[count]); 
            return 1; 
        }
		int matrixDimValue[2] = {0,}; 
		if (!ValidateMatrixDimension(input, &matrixDimValue))
		{
			printf("Matrix Value And or Dimension Not Valid LINE 61"); 
			return 1; 
		}
        if (!SaveMatrixArrayToOut(input, matrixDimValue, &newMatrixBuffer))
        {
            printf("Matrix value failed to be saved"); 
            return 1; 
        }
        if (!MultiplyAndOverwrite(&ouputBuffer, newMatrixBuffer))
        {
            printf("Multiplication logic error occured"); 
            return 1; 
        }
        if (!UpdateFilenameToOut(newMatrixBuffer, &ouputBuffer))
        {
            printf("Filename Appending went wrong, 60"); 
            return 1; 
        } 
        PrintMatrixWithName(newMatrixBuffer.flattenMatrixValue, newMatrixBuffer.name, newMatrixBuffer.row, newMatrixBuffer.column);
        count++; 
        free(newMatrixBuffer.flattenMatrixValue); 
        free(newMatrixBuffer.name); 
        fclose(input); 
    }
	PrintMatrixWithName(ouputBuffer.flattenMatrixValue, ouputBuffer.name, ouputBuffer.row, ouputBuffer.column);
	free(ouputBuffer.flattenMatrixValue); 
    free(ouputBuffer.name); 
}

/// <summary>
/// Retrives Y and X value from Matrix, also contest whether there's appropriate mount of data
/// </summary>
/// <param name="input"></param>
/// <param name="matInfo"></param>
/// <returns></returns>
bool ValidateMatrixDimension(FILE* input, int *outDimensionValue)
{
	int evaluatedValue; 
	int count = 0; 

    fseek(input, 0L, SEEK_SET); 
	while (fscanf(input, "%d", &evaluatedValue) != EOF)
	{
		if (count < 2)
		{
			outDimensionValue[count] = evaluatedValue;
			count++;
			continue; 
		}
		else
		{
			count++; 
		}
	}
	int total = outDimensionValue[0] * outDimensionValue[1]; 
	if (total == (count-2))
	{
		return true; 
	}
	else
	{
		printf("Invalid number of input"); 
		return false; 
	}
}

bool SaveMatrixArrayToOut(FILE *input, int matrixDimInfo[2], matrix *outMatrix)
{
	int size = matrixDimInfo[0] + matrixDimInfo[1]; 
    printf("\n %d, %d\n", matrixDimInfo[0], matrixDimInfo[1]); 
	double *matrixBuffer = malloc(sizeof(double) *size); 
	if (matrixBuffer == NULL)
	{
		return false; 
	}
    memset(matrixBuffer, 0.0, sizeof(double)*size); 
    fseek(input, 0L, SEEK_SET); 
    double val;
	int count = 0; 
	while (fscanf(input, "%lf", &val) != EOF)
	{
        if (count< 2) 
        {
            count++; 
            continue; 
        } 
		matrixBuffer[count-2] = val;
        count++; 
	}
    outMatrix->row = matrixDimInfo[0]; 
    outMatrix->column = matrixDimInfo[1]; 
    outMatrix->flattenMatrixValue = matrixBuffer; 
	return true; 
}
/// <summary>
/// Takes in previous matrix result * next matrix 
/// </summary>
/// <param name="next">next is treated like next matrix value</param>
/// <param name="result">result is first treated like prev</param>
/// <param name="refRow"></param>
/// <param name="refColumn"></param>
/// <returns></returns>
bool MultiplyAndOverwrite(matrix *multiplicand, matrix multiplier)
{
    if (multiplicand->flattenMatrixValue == NULL)
    {
        int Y = multiplier.row; 
		int X = multiplier.column;  
		multiplicand->row = Y; 
		multiplicand->column = X; 
		multiplicand->flattenMatrixValue = multiplier.flattenMatrixValue; 
        return true; 
    }
	int nextY = multiplier.row; 
	int nextX = multiplier.column; 
	int prevY = multiplicand->row;
	int prevX = multiplicand->column; 

	if (prevX != nextY)
	{
		printf("\n%d, %d \n", prevX, nextY); 
		printf("Matrix Size needs to be in order, such that a x b * c x d, b == c"); 
		return false; 
	} 

	int newY = prevY; 
	int newX = nextX; 
	double *destMat = malloc(sizeof(int) * (nextY * prevX));
	if (destMat == NULL)
	{
		printf("Line 131: Memory Shortage"); 
		return false;
	}
	for (int i = 0; i < newY; i++)
	{
		for (int j = 0; j < newX; j++)
		{
			double temp = 0;
			for (int k = 0; k < nextY; k++)
			{
				int leftIndex = k + (i * nextY); 
				int rightIndex =  k*newX + j; 
				temp += multiplicand->flattenMatrixValue[leftIndex] * multiplier.flattenMatrixValue[rightIndex]; 
			}
			int index = i*newX + j; // i * 
			destMat[index] = temp; 
		}
	}
	multiplicand->row = newY; 
	multiplicand->column = newX; 
	double* dispose = multiplicand->flattenMatrixValue;
	multiplicand->flattenMatrixValue = destMat;
	free(dispose);
	return true; 
}

/// @brief Simply Takes in the parameter value to print its array, Clears up heap value ON the matrix struct 
/// @param result Resulting address to the heap 
/// @param fileName resulting filename 
/// @param row in int 
/// @param column in int 
void PrintMatrixWithName(double *result, char *fileName, int row, int column)
{
	int index = 0; 
    int titleIndex = strlen(fileName) -4;
	while( fileName[index] != '\0')
	{
		printf("%c", fileName[index]);
		index++;
	} 
	printf("=\n"); 
    int count = 0; 
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			int index = j + (column * i); 
			printf("%.2f ", result[index]); 
		}
        count++; 
        if (count < row)
        {
            printf(" \n");
        }
	}
	printf("\n");  
}

bool SaveFilenameToOut(char *fileName, matrix *outBuffer)
{
	int titleIndex = strlen(fileName) -3;
	char *newName = malloc(sizeof(char) * titleIndex); 
	if (newName == NULL)
	{
		printf("Memory Shortage"); 
		return false; 
	}
    memset(newName, 0, sizeof(char)*titleIndex); 
	for (int i = 0; i < titleIndex; i++)
	{
		newName[i] = fileName[i]; 
	}
	newName[titleIndex-1] = '\0';
    outBuffer->name = newName; 
    return true; 
}

bool UpdateFilenameToOut(matrix newMatrix, matrix* outBuffer)
{
	if (outBuffer->name == NULL)
	{
        int titleIndex = strlen(newMatrix.name);
		char *copyName = malloc(sizeof(char) * titleIndex);
		if (copyName == NULL)
		{
			return false; 
		} 
        memset(copyName, 0, sizeof(char)*titleIndex); 
		strcpy(copyName, newMatrix.name); 
		outBuffer->name = copyName; 
		return true; 
	}
	int n = 0; 
    char *temp; 
	int wordLength = strlen(newMatrix.name); 
	int accumulated = strlen(outBuffer->name); 
	int formatLoc = wordLength - 4; 
	int newLength = accumulated + formatLoc +1; 

	temp = malloc(sizeof(char)*newLength); 
	if (temp == NULL)
	{
		printf("Line 174, Memory Shortage"); 
		return false; 
	}
    memset(temp, 0, sizeof(char)*newLength); 
    strcpy(temp, outBuffer->name); 
	for (int i = accumulated; i < newLength; i++)
	{
		temp[i] = newMatrix.name[i - accumulated]; 
	}
	temp[newLength -1] = '\0';
	char *dispose = outBuffer->name; 
	outBuffer->name = temp;
	free(dispose); 
	return true; 
}