
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../include/uti.h"
#include "../tinclude/tests.h"

void int_to_str__posNum__exptStr() {
    printf("...int_to_str() positive number creates expected string\n");

    char *actual = int_to_str(5);
    assert(0 == strcmp("5", actual));
    free(actual);
}

void int_to_str__negNum__exptStr() {
    printf("...int_to_str() negative number creates expected string\n");

    char *actual = int_to_str(-5);
    assert(0 == strcmp("-5", actual));
    free(actual);
}

void str_copy__str__reEqualsIn() {
    printf("...str_copy() creates expected copy\n");

    char expected[] = "Gloryhammer";
    char *actual = str_copy(expected);
    assert(0 == strcmp(expected, actual));
    free(actual);
}

void count_substr__needleBiggerThanHaystack__reZero() {
    printf("...count_substr() needle bigger than haystack returns 0\n");
    assert(0 == count_substr("short", "shortshort"));
}

void count_substr__needleSameAsHaystack__reOne() {
    printf("...count_substr() needle equals haystack returns 1\n");

    char word[] = "Rincewind";
    assert(1 == count_substr(word, word));
}

void count_substr__noNeedlesInHaystack__reZero() {
    printf("...count_substr() no needles in haystack returns 0\n");
    assert(0 == count_substr("aaaaaaaaaa", "bbb"));
}

void count_substr__severalNeedlesInHaystack__reSeveral() {
    printf("...count_substr() several needles in haystack returns 3\n");

    char haystack[] = "weatherwax tiger weatherwax tiger weatherwax";
    char needle[] = "weather";
    assert(3 == count_substr(haystack, needle));
}

void index_of__needleNotInHaystack__reMinusOne() {
    printf("...index_of() needle not in haystack returns NOT_FOUND\n");
    assert(NOT_FOUND == indexof("weatherwax", "rincewind"));
}

void index_of__needleInHaystack__reIndex() {
    printf("...index_of() needle in haystack returns index\n");
    assert(7 == indexof("weatherwax", "wax"));
}

void index_of__needleIsHaystack__reZero() {
    printf("...index_of() needle in haystack returns 0\n");
    assert(0 == indexof("Rincewind", "Rincewind"));
}

void str_split__singleLine__reSingleItem() {
    printf("...str_split() single line input is returned unchanged\n");

    int max_len = 1, line_len = 20, len;
    char actual[max_len][line_len];
    char expected[] = "Gloryhammer";

    len = str_split(max_len, line_len, actual, expected, ",");

    assert(len == 1);
    assert(strcmp(expected, *actual) == 0);
}

void str_split__severalParts__reSplitStr() {
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

void str_split__emptyStr__reEmptyStr() {
    printf("...str_split() empty string input returns empty string\n");

    int max_len = 1, line_len = 20, len;
    char actual[max_len][line_len];
    char expected[] = "";

    len = str_split(max_len, line_len, actual, expected, ",");

    assert(len == 1);
    assert(strcmp(expected, *actual) == 0);
}

void str_split__emptyStrAtEnd__reEmptyLastStr() {
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

void str_trim__emptyStr__reEmptyStr() {
    printf("...str_trim() empty string returns empty string\n");

    char expected[] = "";
    int exp_len = strlen(expected), len;
    char actual[exp_len+1];

    len = str_trim(actual, expected);

    assert(exp_len == len);
    assert(0 == strcmp(actual, expected));
}

void str_trim__strOfSpaces__reEmptyStr() {
    printf("...str_trim() whitespace string returns empty string\n");

    char in[] = "      ";
    int exp_len = 0, len;
    char actual[exp_len+1];

    len = str_trim(actual, in);

    assert(exp_len == len);
    assert(0 == strcmp("", actual));
}

void str_trim__noSpaces__reInStr() {
    printf("...str_trim() string with no spaces at the start"
            " or end returns the input string\n");

    char expected[] = "Discworld";
    int exp_len = strlen(expected), len;
    char actual[exp_len+1];

    len = str_trim(actual, expected);

    assert(exp_len == len);
    assert(0 == strcmp(expected, actual));
}

void str_trim__leadingSpacesOnly__reSubstr() {
    printf("...str_trim() string with leadings spaces returns"
            " the expected substring\n");

    char in[] = "   Discworld";
    int exp_len = 9, len;
    char actual[exp_len+1];

    len = str_trim(actual, in);

    assert(exp_len == len);
    assert(0 == strcmp("Discworld", actual));
}

void str_trim__trailingSpacesOnly__reSubstr() {
    printf("...str_trim() string with trailing spaces returns"
            " the expected substring\n");

    char in[] = "Discworld   ";
    int exp_len = 9, len;
    char actual[exp_len+1];

    len = str_trim(actual, in);

    assert(exp_len == len);
    assert(0 == strcmp("Discworld", actual));
}

void str_trim__spacesOnBothSides__reSubstr() {
    printf("...str_trim() string with both leading and trailing"
            " spaces returns the expected substring\n");

    char in[] = "   Discworld   ";
    int exp_len = 9, len;
    char actual[exp_len+1];

    len = str_trim(actual, in);

    assert(exp_len == len);
    assert(0 == strcmp("Discworld", actual));
}

void str_trim__spacesInMiddle__reSubstr() {
    printf("...str_trim() string with space in middle"
            " returns the expected substring\n");

    char expected[] = "Disc world";
    int exp_len = 10, len;
    char actual[exp_len+1];

    len = str_trim(actual, expected);

    assert(exp_len == len);
    assert(0 == strcmp("Disc world", actual));
}

void str_slice__startingSlice__reSubstr() {
    printf("...str_slice() start is 0 and len is less than total"
            " returns the expected substring as a new allocation\n");
            
    char expected[] = "Rincewind";
    char actual[6];
    str_slice(actual, expected, 0, 5);

    assert(strcmp("Rince", actual) == 0);
    assert(actual != expected);
}

void str_slice__endingSlice__reSubstr() {
    printf("...str_slice() start is not the str start and len goes"
            " to the end of the string, returns the expected"
            " substring as a new allocation\n");

    char expected[] = "Rincewind";
    char actual[5];
    str_slice(actual, expected, 5, 4);

    assert(strcmp("wind", actual) == 0);
    assert(actual != expected);
}

void str_slice__midSlice__reSubstr() {
    printf("...str_slice() start is not the str start and"
            " len doesn't reach the end of the string, returns"
            " the expected substring as a new allocation\n");

    char expected[] = "Twilight Force";
    char actual[6];
    str_slice(actual, expected, 3, 5);

    assert(strcmp("light", actual) == 0);
    assert(actual != expected);
}

void str_slice__sliceWholeStr__reInStr() {
    printf("...str_slice() start is 0 and len is total"
            " returns the original str as a new allocation\n");

    char expected[] = "Twilight Force";
    int len = strlen(expected);
    char actual[len + 1];
    str_slice(actual, expected, 0, len);

    assert(strcmp("Twilight Force", actual) == 0);
    assert(actual != expected);
}

void max__multiTest() {
    printf("...max() multi-test\n");

    assert(9 == max(9, 9));
    assert(21 == max(21, -9));
    assert(21 == max(-9, 21));
}

void min__multiTest() {
    printf("...min() multi-test\n");

    assert(9 == min(9, 9));
    assert(-9 == min(21, -9));
    assert(-9 == min(-9, 21));
}
