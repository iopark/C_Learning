#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
void PrintResult(int *result, char *fileName, int row, int column);
void SaveToHeap(FILE* input, int* address);
bool Init(FILE *input, int **result, int *out_row, int *out_column);
bool GetFormat(FILE* input, int *matInfo);
bool Multiply(FILE* input, int* result, int* refRow, int* refColumn, int **doubleResult);
bool AddFileName(char* val, char* fileName, char**initFile);
int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage:/ Requires 2 arguments, input file");
        return 1;
    }
    //Required Variables
    int* result = NULL;
    FILE* input = NULL;
    int r_Row = 0;
    int r_Column = 0;
    int inputText = argc;
    char* fileName = NULL;
    int count = 1;
    //First File
    input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("File on Invalid Path");
        return 1;
    }
    if (Init(input, &result, &r_Row, &r_Column))
    {
        if (!AddFileName(argv[1], fileName, &fileName))
        {
            printf("Failed To Init FileName");
            return 1;
        }
        fclose(input);
    }
    else
    {
        printf("Couldn't initialize a file");
        return 1;
    }
    count++;
    while (count <= argc -1)
    {
        input = fopen(argv[count], "r");
        if (!Multiply(input, result, &r_Row, &r_Column, &result))
        {
            printf("Multiiplication logic error occured");
            return 1;
        }
        if (!AddFileName(argv[count], fileName, &fileName))
        {
            printf("Filename Appending went wrong, 60");
            return 1;
        }
        count++;
        //free(input);
        fclose(input);
    }
    // Create an multidimensional array
    // Underlying assumptions
    // There will be no error resulting from
    // Attempt 1: Simply brute force my way into this code.
    // ATtempt 2: Strassen algorithm -> Divide and conquer until base case 2x2;
    if (result != NULL)
        PrintResult(result, fileName, r_Row, r_Column);
    else
    {
        printf("Input is somehow null");
        return 1;
    }
    free(result);
    free(input);
    fclose(input);
}
void SaveToHeap(FILE* input, int* address)
{
    int val;
    int count = 0;
    fseek(input, 0L, SEEK_SET);
    while (fscanf(input, "%d", &val) != EOF)
    {
        if (count< 2)
        {
            count++;
            continue;
        }
        address[count-2] = val;
        count++;
    }
}
bool Init(FILE* input, int **result, int *out_row, int *out_column)
{
    int matInfo[2] = { 0, };
    GetFormat(input, &matInfo[0]);
    if (out_row == NULL || out_column == NULL) return false;
    *out_row = matInfo[0];
    *out_column = matInfo[1];
    //NULL Exceptions prior to malloc
    int *temp = malloc((*out_row) * (*out_column) * sizeof(int));
    if (temp == NULL)
    {
        return false;
    }
    SaveToHeap(input, temp);
    *result = temp;
    return true;
}
/// <summary>
/// Retrives Y and X value from Matrix
/// </summary>
/// <param name="input"></param>
/// <param name="matInfo"></param>
/// <returns></returns>
bool GetFormat(FILE* input, int *matInfo)
{
    int val;
    int count = 0;
    fseek(input, 0L, SEEK_SET);
    while (fscanf(input, "%d", &val) != EOF)
    {
        if (count < 2)
        {
            matInfo[count] = val;
            count++;
            continue;
        }
        else
            break;
    }
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
bool Multiply(FILE *next, int *result, int *refRow, int *refColumn, int **doubleResult)
{
    if (result == NULL)
    {
        printf("result is Null");
    }
    int matInfo[2] = { 0, };
    GetFormat(next, &matInfo[0]);
    int nextY = matInfo[0];
    int nextX = matInfo[1];
    if (refRow == NULL || refColumn == NULL) return false;
    int* nextMat = (int*)malloc(sizeof(int) * (nextY * nextX));
    if (nextMat == NULL)
    {
        printf("Line 145: Memory Shortage");
        return false;
    }
    SaveToHeap(next, nextMat);
    int newY = *refRow;
    int newX = nextX;
    int *destMat = malloc(sizeof(int) * (newY * newX));
    if (destMat == NULL)
    {
        printf("Line 131: Memory Shortage");
        return false;
    }
    // i is equivalent to prev's rows value
    for (int i = 0; i < newY; i++)
    {
        // j is equivalent to next's column value
        for (int j = 0; j < newX; j++)
        {
            int temp = 0;
            //prev * next
            for (int k = 0; k < nextY; k++)
            {
                int leftIndex = k + (i * nextY);
                int rightIndex =  k*newX + j;
                //printf("\nLINE 197: %d, %d, right Index: %d", result[leftIndex], nextMat[rightIndex], rightIndex);
                temp += result[leftIndex] * nextMat[rightIndex];
            }
            int index = i*newX + j; // i *
            destMat[index] = temp;
        }
    }
    *refRow = newY;
    *refColumn = newX;
    int* dispose = result;
    *doubleResult = destMat;
    free(nextMat);
    free(dispose);
    return true;
}
/// <summary>
/// Adjustable, based on the format name
/// </summary>
/// <param name="val"></param>
/// <param name="fileName"></param>
/// <param name="index"></param>
/// <returns></returns>
bool AddFileName(char* val, char* fileName, char**initFile)
{
    //If its the first file ever===========================================
    if (fileName == NULL)
    {
        int length = strlen(val) - 3;
        char* tempCon = malloc(sizeof(char) * length);
        if (tempCon == NULL)
        {
            printf("Line 154, Memory shortage");
            return false;
        }
        for (int i = 0; i < length - 1; i++)
        {
            tempCon[i] = val[i];
        }
        tempCon[length-1] = '\0';
        *initFile = tempCon;
        return true;
    }
    //else ===============================================================
    int n = 0;
    char *temp;
    int wordLength = strlen(val);
    int fileNameLength = strlen(fileName);
    int formatLoc = wordLength - 4;
    int newLength = fileNameLength + formatLoc +1;
    temp = malloc(sizeof(char)*newLength);
    if (temp == NULL)
    {
        printf("Line 174, Memory Shortage");
        free(fileName);
        return false;
    }
    strcpy(temp, fileName);
    for (int i = fileNameLength; i < newLength; i++)
    {
        temp[i] = val[i - fileNameLength];
    }
    temp[newLength -1] = '\0';
    if (fileName != NULL)
    {
        char *dispose = fileName;
        free(dispose);
    }
    *initFile = temp;
    return true;
}
void PrintResult(int *result, char *fileName, int row, int column)
{
    printf("%s = \n", fileName);
    int count = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            int index = j + (column * i);
            printf("%d ", result[index]);
        }
        count++;
        if (count < row)
        {
            printf(" \n");
        }
    }
    free(result);
    free(fileName);
}