
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

/**************************************************/
/* ^uti.h
/**************************************************/
char* int_to_str(const int n) {

  int len;
  char* r;

  len = 1 + snprintf(NULL, 0, "%d", n);
  r = (char*) malloc(len);
  snprintf(r, len, "%d", n);

  return r;
}

/**************************************************/
/* ^uti.h
/**************************************************/
char* str_copy(char str[]) {

  int len;
  char *r;

  len = strlen(str);
  len++; // NULL_CHAR
  
  r = (char*) malloc(len);
  strcpy(r, str);

  return r;
}

/**************************************************/
/* ^uti.h
/**************************************************/
char* str_cat(char first[], char second[]) {

  int len;
  char *r;
  
  len = strlen(first) + strlen(second);
  len++; // NULL_CHAR

  r = (char*) malloc(len);
  strcpy(r, first);
  strcat(r, second);

  return r;
}

/**************************************************/
/* ^uti.h
/**************************************************/
int count_substr(char haystack[], char needle[]) {

  int r = 0;
  const char *ch = haystack;

  while(ch = strstr(ch, needle)) {
    r++;
    ch++;
  }

  return r;
}

/**************************************************/
/* ^uti.h
/**************************************************/
int indexof(char haystack[], char needle[]) {

  const char *ch;

  ch = strstr(haystack, needle);
  if(ch == NULL) {
    return NOT_FOUND;
  }

  return ch - haystack;
}

/**************************************************/
/* ^uti.h
/**************************************************/
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
    out[i][len] = NULL_CHAR;   

    end += delim_len;
    start = end;
  }

  strcpy(out[size-1], start);
  return size;
}

/**************************************************/
/* ^uti.h
/**************************************************/
void puts_f(const char str[], const char space_repl[]) {

  const char *l = str;

  for(;; l++) {

    switch (*l) {
      case ' ':
      printf("%s", space_repl);
      continue;

      case '\r':
      printf("\\r");
      continue;

      case '\0':
      printf("\\0");
      return;

      case '\n':
      printf("\\n");
      break;
    }

    printf("%c", *l);
  }

  printf("\n");
}

/**************************************************/
/* ^uti.h
/**************************************************/
int str_trim(char out[], char str[]) {

  // TODO: This function should also trim:
  // TODO: \t, \n, \r, \f and \v

  int len = strlen(str);
  char *first = NULL, *last = NULL;

  for(first = str; *first != NULL_CHAR; first++) {
    if(*first != ' ') {
      break;
    }
  }

  if(*first == NULL_CHAR) {
    // Only white space or length is 0
    out[0] = NULL_CHAR;
    return 0;
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
    // Spaces in middle but not at ends
    strcpy(out, str);
    return len;
  }

  if(last == NULL) {
    // Leading spaces only
    strcpy(out, first);
    return strlen(first);
  }

  if(first == NULL) {
    // Trailing spaces only
    len = last - str;
    str_slice(out, str, 0, len+1);
    return strlen(out);
  }

  len = last - first;
  str_slice(out, first, 0, len+1);
  return strlen(out);
}

/**************************************************/
/* ^uti.h
/**************************************************/
void str_slice(char out[], char str[], int start, int len) {

  // TODO: What should happen on invalid input?
  // TODO: What are the invalid input configurations?

  char *p;

  if(start == len) {
    out[0] = NULL_CHAR;
  } else {
    p = str + start;
    strncpy(out, p, len);
    out[len] = NULL_CHAR;
  }
}

/**************************************************/
/* ^uti.h
/**************************************************/
int max(int a, int b) {
  if(a > b) {
    return a;
  } else {
    return b;
  }
}

/**************************************************/
/* ^uti.h
/**************************************************/
int min(int a, int b) {
  if(a < b) {
    return a;
  } else {
    return b;
  }
}
