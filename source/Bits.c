#include <stdio.h>; 
/*
    2진수, 8진수, 그리고 16 진수 
    2진수는 0 과 1 로 이루어져있는 transistor 가 읽을수 있는 최소의 숫자 단위이자, 사실 현재 컴퓨터 프로그래밍에 들어가는 모든 연산의 근간이 되는 수의 단위이다. 
    우리가 프로그래밍 하는 모든 값에 대해서는, int, short, float, double, long, string, char, etc, 모든 값은 2진수로써 번역과정이 들어가며, 
    디버깅 하는 과정에서나, 특히 integer값을 다룰때에 16진수로 값을 표기하거나, 
    값을 추출해 내거나, 마지막으로는 값을 적는 방식에 대해서 익숙에 지는것이 좋다. 
    (어차피 디버깅을 할때에 메모리 주소값을 다룰때는 16진수투성이니)
*/
int main() { 
    int decVal = 129; 
    int hexVal = 0x00000081; 
    printf("%i, %i", decVal, hexVal); 
    return 0; 
}