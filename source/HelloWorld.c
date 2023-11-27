#include <stdio.h>; 
/* Although C89 or ANSI C does not support the //, for sake of comfort (which I'm used to using c#, )
I'll be using // a LOT. */

/*In the CS50x, one of the first thing discussed is the idea of Libraries, where printf function, 
set of functions (defined or not I guess) ready to use is called libraries. here, standardinputoutput header file is used 
<> only imports header files in the project directories, 
"" where as this first scans project directories, and searches throught default C library. 
*/

int main() { 
    printf("Hello World!"); // Console.Write(str); 
    getchar(); //works similar to Console.GetKey(); 
}