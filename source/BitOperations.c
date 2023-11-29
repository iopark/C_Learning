#include <stdio.h>; 

/* 
    비트 연산자, Where magic happens 
    기억하자. 컴퓨터는 비트 연산을 사랑한다. 
*/
int main() { 
    char char_Val; 
    int temp_Color = 0xFF800080; 
    int color_Max = 0xFFFFFFFF; 

    /*AND & : can be utilized to extract specific color from it 
    Example : Get Value of R in ARGB buffer */

    int color_RStd = 0x00FF0000; 
    int red_Extract = (temp_Color & color_RStd) >> 16; // given each value is desribed in 0- 255, 
    //for values in that buffer, if a byte of info is converted into 4 bytes, would extract value in place.  

    // OR | in Unity, layer or utilizing flag computation 
    int first_Flag = 2;  // in (bin) 0010
    int second_Flag = 4; // in (bin) 0100 
    int combine_Flag = first_Flag | second_Flag; 
    // OR statement can be utilized to see if either of the flag is present
    // Checking if the presented buffer holds color one is looking for 
    int focus_Color = 0xFF400023; 
    int buffer_ = 0x00FF0000; 
    // Extract Color R, 
    int result = focus_Color | buffer_ ; 


    // XOR ^ : find the number represented by the char. 
        // where 0 = 48 in ASCII 
    
    char char_ToIntVal = '2'; 
    int char_Convert=  char_ToIntVal ^ 48; // == 2; 
    
    /* Bit Shift 
        Given a bit value, 1100, if shifted, would result in value ^ # 
        1100 = 12 
        11000 = 24
        this is true, because 
        1100 = 2^3 + 2^2 
        11000 = 2^3 * 2 + 2^2 *2 => 2(2^3 + 2^2); 
        thus, val << # where # > 1, val * 2^# 
        and this goes same for >> 
    */
    // <<
    int raw_Val = 16; 
    int raw_Double= raw_Val * 2; 
    int raw_bitDouble = raw_Val << 1; 
    // >>
    int raw_Val1 = 16; 
    int raw_Half = raw_Val1 /2 ; 
    int raw_bitHalf = raw_Val1 >> 1; 
    //Retrieving specific value from a buffer (alpha from color buffer (int))

} 