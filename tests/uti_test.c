
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../include/uti.h"
#include "../tinclude/tests.h"

void int_to_str___1() {
  puts("...int_to_str() when given a positive number, the number is converted"
      " to a string and returned");

  char *actual = int_to_str(5);
  assert(0 == strcmp("5", actual));
  free(actual);
}

void int_to_str___2() {
  puts("...int_to_str() when given a negative number, the number is converted"
      " to a string and returned");

  char *actual = int_to_str(-5);
  assert(0 == strcmp("-5", actual));
  free(actual);
}

void str_copy___1() {
  puts("...str_copy() when given a string, a new string allocation is returned"
      " containing the same characters in the same order");

  char expected[] = "Gloryhammer";
  char *actual = str_copy(expected);

  assert(expected != actual);
  assert(0 == strcmp(expected, actual));
  free(actual);
}

void str_cat___2() {
  puts("...str_cat() when given two strings, a new string allocation is"
      " returned containing the concaternation of both input strings");

  char *result;
  char first[] = "Glory";
  char second[] = "hammer";
  char expected[] = "Gloryhammer";

  result = str_cat(first, second);
  assert(strcmp(expected, result) == 0);
  free(result);
}

void str_cat___3() {
  puts("...str_cat() when given two empty strings, a new string allocation is"
      " returned containing an empty string");

  char *result;
  char expected[] = "";

  result = str_cat(expected, expected);
  assert(strcmp(expected, result) == 0);
  free(result);
}

void count_substr___1() {
  puts("...count_substr() when given a needle bigger than the haystack, 0 is"
      " returned");

  int count = count_substr("short", "shortshort");
  assert(0 == count);
}

void count_substr___2() {
  puts("...count_substr() when given a needle that contains the same characters"
      " in the same order as the haystack, 1 is returned");

  char word[] = "Rincewind";
  int count = count_substr(word, word);
  assert(1 == count);
}

void count_substr___3() {
  puts("...count_substr() when given a needle that is shorter than the haystack"
      " but is not contained within it, 0 is returned");

  int count = count_substr("aaaaaaaaaa", "bbb");
  assert(0 == count);
}

void count_substr___4() {
  puts("...count_substr() when given a needle that is contained within the"
      " haystack multiple times, the correct count is returned");

  char haystack[] = "weatherwax tiger weatherwax tiger weatherwax";
  char needle[] = "weather";
  int count = count_substr(haystack, needle);
  assert(3 == count);
}

void index_of___1() {
  puts("...index_of() when given a needle not in the haystack, NOT_FOUND is"
      " returned");

  int i = indexof("weatherwax", "rincewind");
  assert(NOT_FOUND == i);
}

void index_of___2() {
  puts("...index_of() when given a needle within the haystack, the index of the"
      " first matching character within the haystack is returned");

  int i = indexof("weatherwax", "wax");
  assert(7 == i);
}

void index_of___3() {
  puts("...index_of() when given a needle that contains the same characters in"
      " the same order as the haystack, 0 is returned");

  int i = indexof("Rincewind", "Rincewind");
  assert(0 == i);
}

void str_split___1() {
  puts("...str_split() when given an input string that doesn't contain the"
      " delimiter, the returned length will be 1 and the output container will"
      " contain a copy of the input string as its first and only item");

  int max_len = 1, line_len = 20, len;
  char actual[max_len][line_len];
  char expected[] = "Gloryhammer";

  len = str_split(max_len, line_len, actual, expected, ",");

  assert(len == 1);
  assert(0 == strcmp(expected, *actual));
}

void str_split___2() {
  puts("...str_split() when given an input string containing several instances"
      " of the delimiter, the returned length will be the number of delimiters"
      " plus 1 and the output container will contain copies of the split input"
      " string in the order they appeared within that input string");

  int max_len = 3, line_len = 20, len;
  char actual[max_len][line_len];
  char str[] = "Rincewind\r\nWeatherwax\r\nVimes";

  len = str_split(max_len, line_len, actual, str, "\r\n");

  assert(len == 3);
  assert(0 == strcmp("Rincewind", actual[0]));
  assert(0 == strcmp("Weatherwax", actual[1]));
  assert(0 == strcmp("Vimes", actual[2]));
}

void str_split___3() {
  puts("...str_split() when given an empty input string, the returned length"
      " will be 1 and the output container will contain an empty string");

  int max_len = 1, line_len = 20, len;
  char actual[max_len][line_len];
  char expected[] = "";

  len = str_split(max_len, line_len, actual, expected, ",");

  assert(len == 1);
  assert(0 == strcmp(expected, *actual));
}

void str_split___4() {
  puts("...str_split() when given an input string ending with a delimiter, the"
      " returned length will be 2 and the first item in the output container"
      " will be a copy of the input string without the delimiter and the second"
      " item will be an empty string");

  int max_len = 2, line_len = 20, len;
  char actual[max_len][line_len];
  char str[] = "Discworld,";

  len = str_split(max_len, line_len, actual, str, ",");

  assert(len == 2);
  assert(0 == strcmp("Discworld", actual[0]));
  assert(0 == strcmp("", actual[1]));
}

void is_whitespace___1() {
  puts("...is_whitespace() when given a non-whitespace character, FALSE"
      " is returned");

  int result = is_whitespace('a');
  assert(FALSE == result);
}

void is_whitespace___2() {
  puts("...is_whitespace() when given a space character, TRUE is"
      " returned");

  int result = is_whitespace(' ');
  assert(TRUE == result);
}

void is_whitespace___3() {
  puts("...is_whitespace() when given a carrage return character, TRUE is"
      " returned");

  int result = is_whitespace('\r');
  assert(TRUE == result);
}

void is_whitespace___4() {
  puts("...is_whitespace() when given a newline character, TRUE is"
      " returned");

  int result = is_whitespace('\n');
  assert(TRUE == result);
}

void is_whitespace___5() {
  puts("...is_whitespace() when given a feed character, TRUE is"
      " returned");

  int result = is_whitespace('\f');
  assert(TRUE == result);
}

void is_whitespace___6() {
  puts("...is_whitespace() when given a vertical tab character, TRUE is"
      " returned");

  int result = is_whitespace('\v');
  assert(TRUE == result);
}

void str_trim___1() {
  puts("...str_trim() when given an empty string, the result container will"
      " contain an empty string");

  char actual[50], expected[] = "";
  int len;

  len = str_trim(actual, expected);
  assert(0 == strcmp(actual, expected));
}

void str_trim___2() {
  puts("...str_trim() when given a string only containing spaces, the result"
      " container will contain an empty string");

  char actual[50], in[] = "      ";
  int len;

  len = str_trim(actual, in);
  assert(0 == strcmp("", actual));
}

void str_trim___3() {
  puts("...str_trim() when given a string not containing any spaces, the result"
      " container will contain the input string");

  char actual[50], expected[] = "Discworld";
  int len;

  len = str_trim(actual, expected);
  assert(0 == strcmp(expected, actual));
}

void str_trim___4() {
  puts("...str_trim() when given a string containing leading spaces, the result"
      " container will contain the input string without the leading spaces");

  char actual[50], in[] = "   Discworld";
  int len;

  len = str_trim(actual, in);
  assert(0 == strcmp("Discworld", actual));
}

void str_trim___5() {
  puts("...str_trim() when given a string containing trailing spaces, the"
      " result container will contain the input string without the trailing"
      " spaces");

  char actual[50], in[] = "Discworld   ";
  int len;

  len = str_trim(actual, in);
  assert(0 == strcmp("Discworld", actual));
}

void str_trim___6() {
  puts("...str_trim() when given a string containing both leading and trailing"
      " spaces, the result container will contain the input string without any"
      " leading or trailing spaces");

  char actual[50], in[] = "   Discworld   ";
  int len;

  len = str_trim(actual, in);
  assert(0 == strcmp("Discworld", actual));
}

void str_trim___7() {
  puts("...str_trim() when given a string containing spaces within the centre"
      " but none leading or trailing, the result container will contain the"
      " input string");

  char actual[50], expected[] = "Disc world";
  int len;

  len = str_trim(actual, expected);
  assert(0 == strcmp("Disc world", actual));
}

void str_trim___8() {
  puts("...str_trim() when given a string containing leading tabs but no"
      " trailing whitespace, the result container will contain the input"
      " without the tabs");

  char actual[50], expected[] = "\t\tDiscworld";
  int len;

  len = str_trim(actual, expected);
  assert(0 == strcmp("Discworld", actual));
}

void str_trim___9() {
  puts("...str_trim() when given a string containing trailing tabs but no"
      " leading whitespace, the result container will contain the input"
      " without the tabs");

  char actual[50], expected[] = "Discworld\t\t";
  int len;

  len = str_trim(actual, expected);
  assert(0 == strcmp("Discworld", actual));
}

void str_trim___10() {
  puts("...str_trim() when given a string containing leading carrage returns"
      " but no trailing whitespace, the result container will contain the input"
      " without the carrage returns");

  char actual[50], expected[] = "\r\rDiscworld";
  int len;

  len = str_trim(actual, expected);
  assert(0 == strcmp("Discworld", actual));
}

void str_trim___11() {
  puts("...str_trim() when given a string containing trailing carrage returns"
      " but no leading whitespace, the result container will contain the input"
      " without the carrage returns");

  char actual[50], expected[] = "Discworld\r\r";
  int len;

  len = str_trim(actual, expected);
  assert(0 == strcmp("Discworld", actual));
}

void str_slice___1() {
  puts("...str_slice() when given a string and range that targets the beginning"
      " of the string, the result container will contain the targetted"
      " substring");
            
  char expected[] = "Rincewind";
  char actual[6];
  str_slice(actual, expected, 0, 5);

  assert(0 == strcmp("Rince", actual));
  assert(actual != expected);
}

void str_slice___2() {
  puts("...str_slice() when given a string and range that targets the end of"
      " the string, the result container will contain the targetted substring");

  char expected[] = "Rincewind";
  char actual[5];
  str_slice(actual, expected, 5, 4);

  assert(0 == strcmp("wind", actual));
  assert(actual != expected);
}

void str_slice___3() {
  puts("...str_slice() when given a string and range that targets the centre of"
      " the string without including the start or end, the result container"
      " will contain the targetted substring");

  char expected[] = "Twilight Force";
  char actual[6];
  str_slice(actual, expected, 3, 5);

  assert(0 == strcmp("light", actual));
  assert(actual != expected);
}

void str_slice___4() {
  puts("...str_slice() when given a string and range that targets the whole"
      " string, the result container will contain the input string");

  char expected[] = "Twilight Force";
  int len = strlen(expected);
  char actual[len + 1];
  str_slice(actual, expected, 0, len);

  assert(0 == strcmp("Twilight Force", actual));
  assert(actual != expected);
}

void str_slice___5() {
  puts("...str_slice() when given a string and range with a difference of 0,"
      " the result container will contain an empty string");

  char expected[] = "Twilight Force";
  int len = strlen(expected);
  char actual[1];
  str_slice(actual, expected, 5, 5);

  assert(0 == strcmp("", actual));
  assert(actual != expected);
}

void max___multi() {
  puts("...max() when given input values that are equal, that value is"
      " returned");
  assert(9 == max(9, 9));

  puts("...max() when the first value given is greater than the second, the"
      " first is returned");
  assert(21 == max(21, -9));

  puts("...max() when the first value given is less than the second, the second"
      " is returned");
  assert(21 == max(-9, 21));
}

void min___multi() {
  puts("...min() when given input values that are equal, that value is"
      " returned");
  assert(9 == min(9, 9));

  puts("...min() when the first value given is less than the second, the first"
      " is returned");
  assert(-9 == min(-9, 21));

  puts("...min() when the first value given is greater than the second, the"
      " second is returned");
  assert(-9 == min(21, -9));
}
