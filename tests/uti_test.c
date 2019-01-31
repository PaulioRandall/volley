
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../include/uti.h"
#include "../tinclude/tests.h"

void int_to_str__posNum__expectedStr() {
    printf("...int_to_str() positive number creates expected string\n");
    char expected[] = "5";
    char *actual = int_to_str(5);
    assert(strcmp(expected, actual) == 0);
    free(actual);
}

void int_to_str__negNum__expectedStr() {
    printf("...int_to_str() negative number creates expected string\n");
    char expected[] = "-5";
    char *actual = int_to_str(-5);
    assert(strcmp(expected, actual) == 0);
    free(actual);
}

void str_copy__str__outputEqualsInput() {
    printf("...str_copy() creates expected copy\n");
    char expected[] = "Gloryhammer";
    char *actual = str_copy(expected);
    assert(strcmp(expected, actual) == 0);
    free(actual);
}

void count_substr__needleBiggerThanHaystack__returnsZero() {
    printf("...count_substr() needle bigger than haystack returns 0\n");
    char haystack[] = "short";
    char needle[] = "shortshort";
    int count = count_substr(haystack, needle);
    assert(count == 0);
}

void count_substr__needleSameAsHaystack__returnsOne() {
    printf("...count_substr() needle equals haystack returns 1\n");
    char haystack[] = "Rincewind";
    int count = count_substr(haystack, haystack);
    assert(count == 1);
}

void count_substr__noNeedlesInHaystack__returnsZero() {
    printf("...count_substr() no needles in haystack returns 0\n");
    char haystack[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    char needle[] = "bbb";
    int count = count_substr(haystack, needle);
    assert(count == 0);
}

void count_substr__severalNeedlesInHaystack__returnsSeveral() {
    printf("...count_substr() several needles in haystack returns 3\n");
    char haystack[] = "weatherwax tiger weatherwax tiger weatherwax";
    char needle[] = "weather";
    int count = count_substr(haystack, needle);
    assert(count == 3);
}

void index_of__needleNotInHaystack__returnsMinusOne() {
    printf("...index_of() needle not in haystack returns -1\n");
    char haystack[] = "weatherwax";
    char needle[] = "rincewind";
    int i = indexof(haystack, needle);
    assert(i == -1);
}

void index_of__needleInHaystack__returnsIndex() {
    printf("...index_of() needle in haystack returns index\n");
    char haystack[] = "weatherwax";
    char needle[] = "wax";
    int i = indexof(haystack, needle);
    assert(i == 7);
}

void index_of__needleIsHaystack__returnsZero() {
    printf("...index_of() needle in haystack returns 0\n");
    char haystack[] = "Rincewind";
    char needle[] = "Rincewind";
    int i = indexof(haystack, needle);
    assert(i == 0);
}

void str_split__singleLine__returnsSingleItem() {
    printf("...str_split() single line input is returned unchanged\n");

    int max_len = 1, line_len = 20, len;
    char actual[max_len][line_len];
    char expected[] = "Gloryhammer";

    len = str_split(max_len, line_len, actual, expected, ",");

    assert(len == 1);
    assert(strcmp(expected, *actual) == 0);
}

void str_split__severalParts__returnsSplitString() {
    printf("...str_split() multi line returns many lines\n");

    int max_len = 3, line_len = 20, len;
    char actual[max_len][line_len];
    char str[] = "Rincewind\r\nWeatherwax\r\nVimes";

    len = str_split(max_len, line_len, actual, str, "\r\n");

    assert(len == 3);
    assert(strcmp("Rincewind", actual[0]) == 0);
    assert(strcmp("Weatherwax", actual[1]) == 0);
    assert(strcmp("Vimes", actual[2]) == 0);
}

void str_split__emptyStr__returnsEmptyStr() {
    printf("...str_split() empty string input returns empty string\n");

    int max_len = 1, line_len = 20, len;
    char actual[max_len][line_len];
    char expected[] = "";

    len = str_split(max_len, line_len, actual, expected, ",");

    assert(len == 1);
    assert(strcmp(expected, *actual) == 0);
}

void str_split__emptyStrAtEnd__returnsEmptyLastStr() {
    printf("...str_split() string with empty line at end returns"
            " array where last string item is empty\n");

    int max_len = 2, line_len = 20, len;
    char actual[max_len][line_len];
    char str[] = "Discworld,";

    len = str_split(max_len, line_len, actual, str, ",");

    assert(len == 2);
    assert(strcmp("Discworld", actual[0]) == 0);
    assert(strcmp("", actual[1]) == 0);
}

void str_trim__emptyStr__returnsEmptyStr() {
    printf("...str_trim() empty string returns empty string"
            " as a new allocation\n");
    char expected[] = "";
    char *actual = str_trim(expected);
    assert(strcmp(actual, expected) == 0);
    assert(actual != expected);
    free(actual);
}

void str_trim__whitespaceStr__returnsEmptyStr() {
    printf("...str_trim() whitespace string returns empty string"
            " as a new allocation\n");
    char expected[] = "      ";
    char *actual = str_trim(expected);
    assert(strcmp("", actual) == 0);
    assert(actual != expected);
    free(actual);
}

void str_trim__noSpaces__returnsOriginalStr() {
    printf("...str_trim() string with no spaces at the start"
            " or end returns the input string as a new allocation\n");
    char expected[] = "Discworld";
    char *actual = str_trim(expected);
    assert(strcmp(actual, expected) == 0);
    assert(actual != expected);
    free(actual);
}

void str_trim__leadingSpacesOnly__returnsSubstr() {
    printf("...str_trim() string with leadings spaces returns"
            " the expected substring as a new allocation\n");
    char expected[] = "   Discworld";
    char *actual = str_trim(expected);
    assert(strcmp("Discworld", actual) == 0);
    assert(actual != expected);
    free(actual);
}

void str_trim__trailingSpacesOnly__returnsSubstr() {
    printf("...str_trim() string with trailing spaces returns"
            " the expected substring as a new allocation\n");
    char expected[] = "Discworld   ";
    char *actual = str_trim(expected);
    assert(strcmp("Discworld", actual) == 0);
    assert(actual != expected);
    free(actual);
}

void str_trim__spacesOnBothSides__returnsSubstr() {
    printf("...str_trim() string with both leading and trailing"
            " spaces returns the expected substring as a new allocation\n");
    char expected[] = "   Discworld   ";
    char *actual = str_trim(expected);
    assert(strcmp("Discworld", actual) == 0);
    assert(actual != expected);
    free(actual);
}


void str_trim__spacesInMiddle__returnsSubstr() {
    printf("...str_trim() string with space in middle"
            " returns the expected substring as a new allocation\n");
    char expected[] = "Disc world";
    char *actual = str_trim(expected);
    assert(strcmp("Disc world", actual) == 0);
    assert(actual != expected);
    free(actual);
}

void str_slice__startingSlice__returnsSubstr() {
    printf("...str_slice() start is 0 and len is less than total"
            " returns the expected substring as a new allocation\n");
    char expected[] = "Rincewind";
    char actual[6];
    str_slice(actual, expected, 0, 5);
    assert(strcmp("Rince", actual) == 0);
    assert(actual != expected);
}

void str_slice__endingSlice__returnsSubstr() {
    printf("...str_slice() start is not the str start and len goes"
            " to the end of the string, returns the expected"
            " substring as a new allocation\n");
    char expected[] = "Rincewind";
    char actual[5];
    str_slice(actual, expected, 5, 4);
    assert(strcmp("wind", actual) == 0);
    assert(actual != expected);
}

void str_slice__midSlice__returnsSubstr() {
    printf("...str_slice() start is not the str start and"
            " len doesn't reach the end of the string, returns"
            " the expected substring as a new allocation\n");
    char expected[] = "Twilight Force";
    char actual[6];
    str_slice(actual, expected, 3, 5);
    assert(strcmp("light", actual) == 0);
    assert(actual != expected);
}

void str_slice__sliceWholeStr__returnsOriginalStr() {
    printf("...str_slice() start is 0 and len is total"
            " returns the original str as a new allocation\n");
    char expected[] = "Twilight Force";
    int len = strlen(expected);
    char actual[len + 1];
    str_slice(actual, expected, 0, len);
    assert(strcmp("Twilight Force", actual) == 0);
    assert(actual != expected);
}
