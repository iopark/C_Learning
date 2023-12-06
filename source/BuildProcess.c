/* 
Assumption: Given any 'declared' methods within the header files are to be expected to be shared. 
Thus, by #Include-ing various 'common' and local header files, with or without static linking process, 
we can expect compiler to present object code well suited for OS read and execute. 
Here, some of the common concerns or techniques in building a program rises, and thus, it is deemed for programmer to 
have some degree of knowledge of history and context behind the 'build'. 

Thus by understanding the core principle behind build process, I am learning, and preparing myself as a well-equipped developer. 

1. Pre-Process 
2. Compiler 
3. Assembler
4. The Linker. 

1. Pre-Process 
    Summary: Converts individual .c file to .pre, with the main purpose being presenting 
    compiler friendly file. 
    Key process include: 
        1. replacing #include with set of header file info for compiler to 'utilize' 
        2. removing all the comments 

2. Compiler & Assembler 
    Summary: While both differ in some parts, for sake of understanding general picture of build process, I'll group them together. 
    Main part of the compiler is in translating .pre file into .s, or .o file (.s as assembly language, vs .o native code file)
    .s file translates pre-processed .pre code into machine-native or specific assembly code, which assembler would translate into native code. 
    .o file, skips the .s, directly translates into .o file. 

    Some of the key points to remember in this process is essential especially as it deals with static functions across various scripts. 
    1. Not only does this convert each functions into set of codes to manipulate esp and ebp 
        (should expand further with studies behind Stack frame)
    2. It also creates goto function for 'pre-declared' functions (which later linker processes)
    3. Creates label for each of the 'defined' functions which linker uses to connect goto line to this specific function 
        (The label is used by the linker to identify and replace the pre-declared functions)

3. The Linker 
    replaces the previously labeled functions with the actual address to the memory in code region where function is defined 
*/