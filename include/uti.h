
/*
 Volley: https://github.com/PaulioRandall/volley
 Copyright (c) 2018 - 2019 Paul Williams

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

/**************************************************/
/* Converts an integer to a string
/*
/* num: Number to stringify
/* @Heap
/**************************************************/
char* int_to_str(const int num);

/**************************************************/
/* Returns a copy of a string
/*
/* str[]: Copies a string
/* @Heap
/**************************************************/
char* str_copy(char str[]);

/**************************************************/
/* Counts the number of substrings within a string
/* 
/* haystack[]: String to search in
/* needle[]: String to search for
/**************************************************/
int count_substr(char haystack[], char needle[]);

/**************************************************/
/* Finds the index of the first occurrence of the
/* needle within the haystack. If no index can be
/* found -1 will be returned
/* 
/* haystack[]: String to search in
/* needle[]: String to search for
/**************************************************/
int indexof(char haystack[], char needle[]);

/**************************************************/
/* Splits the string on each '\r\n'
/* 
/* max_len: Maximum length of the result array
/* line_len: Maximum length of each result line
/*            including null terminator
/* out[][]: Container for the result
/* str[]: String to split
/* delim[]: Delimiter to split on
/**************************************************/
int str_split(int max_len, int line_len, char out[max_len][line_len], char str[], char delim[]);

/**************************************************/
/* Prints the string but shows the symbols.
/* Symbols such as '\r' will be printed as
/* characters but without causing a carrage
/* return. Spaces will be replaced with the
/* supplied string for better debugging
/* 
/* str[]: String to print
/* space_repl[]: String to replace spaces with
/**************************************************/
void print_str_with_symbols(const char str[], const char space_repl[]);

/**************************************************/
/* Removes spaces from the start and end of the
/* input string
/* 
/* str[]: String to trim
/* @Heap
/**************************************************/
char* str_trim(char str[]);

/**************************************************/
/* Slices the string using the specified range
/* 
/* out[]: Result container
/* str[]: String to slice
/* start: Index indicating the first char of the
/*        substring
/* len: Length of the slice
/**************************************************/
void str_slice(char out[], char str[], int start, int len);

/**************************************************/
/* Returns the maximum of two integers
/* 
/* a: First value
/* b: Second value
/**************************************************/
int max(int a, int b);

/**************************************************/
/* Returns the minimum of two integers
/* 
/* a: First value
/* b: Second value
/**************************************************/
int min(int a, int b);