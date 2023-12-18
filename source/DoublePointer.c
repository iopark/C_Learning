#include <stdio.h>
#include <stdlib.h>

/* 
더블 포인터스 
매개변수 값이 더블 포인터인 경우에, 특정 매개변수인 싱글 포인터에 대한 주소값을 참조가 가능해진다. 
따라서 동적할당 당시 참조되는 값을 바꿔야 하는경우 용이하게 사용될 수 있겠다. 
*/
void ChangePtrV1(int *ptr); 
void ChangePtrV2(int *ptr); 
void DoulbePtr(int **ptr); 
int main(void)
{
    int *ptr = NULL;
    int *ptrv2 = NULL; 
    int *ptrv3 = NULL; 
    ChangePtrV1(ptr); 
    ChangePtrV2(&ptrv2); 
    DoulbePtr(&ptrv3); 
    if (ptr != NULL)
    {
        printf("V1 : %d", ptr[1]); 
    }
    if (ptrv2 != NULL)
    {
        printf("V2 : %d", ptrv2[1]); 
    }
    if (ptrv3 != NULL)
    {
        printf("V3 : %d", ptrv3[1]); 
    }
}

void ChangePtrV1(int *ptr)
{
    int *temp = malloc(sizeof(int)* 5); 
    for (int i =0; i < 5; i++)
    {
        temp[i] = 5; 
    }
    ptr = temp; 
}

void ChangePtrV2(int *ptr)
{
    int *temp = malloc(sizeof(int)* 5); 
    for (int i =0; i < 5; i++)
    {
        temp[i] = 5; 
    }
    ptr = temp; 
}

void DoulbePtr(int **ptr)
{
    int *temp = malloc(sizeof(int)* 5); 
    for (int i =0; i < 5; i++)
    {
        temp[i] = 5; 
    }
    *ptr = temp; 
}