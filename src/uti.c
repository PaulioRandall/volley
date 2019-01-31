
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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/uti.h"

/**
 * TODO: Investigate comments styles in C, Google doesn't seem to have
 * TODO: a pure C style or it's been moved. Function comments are
 * TODO: priority, find approaches for both header and source files
 */

/**
 * ^uti.h
 */
char* int_to_str(const int n) {

  int len;
  char* r;

  len = 1 + snprintf(NULL, 0, "%d", n);
  r = (char*) malloc(len);
  snprintf(r, len, "%d", n);

  return r;
}

/**
 * ^uti.h
 */
char* str_copy(char str[]) {

  int len;
  char *r;

  len = strlen(str);
  len++; // '\0'
  
  r = (char*) malloc(len);
  strcpy(r, str);

  return r;
}

/**
 * ^uti.h
 */
int count_substr(char haystack[], char needle[]) {

  int r = 0;
  const char *ch = haystack;

  while(ch = strstr(ch, needle)) {
    r++;
    ch++;
  }

  return r;
}

/**
 * ^uti.h
 */
int indexof(char haystack[], char needle[]) {

  const char *ch;

  ch = strstr(haystack, needle);
  if(ch == NULL) {
    return -1;
  }

  return ch - haystack;
}

/**
 * ^uti.h
 */
int str_split(int max_len, int line_len, char out[max_len][line_len], char str[], char delim[]) {

  int delim_len, size, i, len;
  char *start, *end;
  
  delim_len = strlen(delim);

  size = count_substr(str, delim);
  size++; // 1 more segment than the delimiter count
  size = min(max_len, size);

  start = str;
  for(i = 0; i < (size-1); i++) {

    end = strstr(start, delim);
    len = end - start;
    strncpy(out[i], start, len);
    out[i][len] = '\0';   

    end += delim_len;
    start = end;
  }

  strcpy(out[size-1], start);
  return size;
}

/**
 * ^uti.h
 */
void printf_with_symbols(const char str[], const char space_repl[]) {

  // TODO: Could this be more concise and readable using a switch?

  const char *l;

  for(l = str; *l != '\0'; l++) {
    if(*l == ' ') {
      printf("%s", space_repl);
      continue;
    }

    if(*l == '\r') {
      printf("\\r");
      continue;
    }
    
    if(*l == '\n') {
      printf("\\n");
    }

    if(*l == '\0') {
      printf("\\0");
    }

    printf("%c", *l);
  }

  printf("\\0\n");
}

/**
 * ^uti.h
 */
char* str_trim(char str[]) {

  // TODO: This could probably be more concise, write another
  // TODO: test or two and refactor
  
  int len = strlen(str);
  char *first = NULL, *last = NULL;
  char *r;

  for(first = str; *first != '\0'; first++) {
    if(*first != ' ') {
      break;
    }
  }

  if(*first == '\0') {
    // Only white space or length is 0
    return str_copy("");
  }

  if(first == str) {
    // No leading spaces
    first = NULL;
  }

  last = str + len - 1;
  for(; last != str; last--) {
    if(*last != ' ') {
      break;
    }
  }

  if(last == (str + len - 1)) {
    // No trailing spaces
    last = NULL;
  }

  if(first == NULL && last == NULL) {
    // No leading or trailing spaces
    return str_copy(str);
  }

  if(last == NULL) {
    // Leading spaces only
    return str_copy(first);
  }

  if(first == NULL) {
    // Trailing spaces only
    len = last - str + 1;
    r = (char*) malloc(len);
    str_slice(r, str, 0, len);
    return r;
  }

  len = last - first + 1;
  r = (char*) malloc(len);
  str_slice(r, first, 0, len);
  return r;
}

/**
 * ^uti.h
 */
void str_slice(char out[], char str[], int start, int len) {

  char *p;

  p = str + start;
  strncpy(out, p, len);
  out[len] = '\0';
}


/**
 * Returns the maximum of two integers
 * 
 * @a: First value
 * @b: Second value
 */
int max(int a, int b) {
  if(a > b) {
    return a;
  } else {
    return b;
  }
}

/**
 * Returns the minimum of two integers
 * 
 * @a: First value
 * @b: Second value
 */
int min(int a, int b) {
  if(a < b) {
    return a;
  } else {
    return b;
  }
}
