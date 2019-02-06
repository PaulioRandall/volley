
#include <stdio.h>
#include "../tinclude/tests.h"

int main ( int argc, char *argv[] ) {

    // TODO: It's probably about time to look for a proper
    // TODO: test framework, as lightweight and minimal
    // TODO: as possible

    printf("TEST SUITE STARTED\n");

    /**************************************************/
    /* ^uti.h
    /**************************************************/
    int_to_str___1();
    int_to_str__2();

    str_copy___1();

    str_cat__1();
    str_cat__2();
    str_cat__3();

    count_substr___1();
    count_substr___2();
    count_substr___3();
    count_substr___4();

    index_of__needleNotInHaystack__reMinusOne();
    index_of__needleInHaystack__reIndex();
    index_of__needleIsHaystack__reZero();

    str_split__singleLine__reSingleItem();
    str_split__severalParts__reSplitStr();
    str_split__emptyStr__reEmptyStr();
    str_split__emptyStrAtEnd__reEmptyLastStr();

    str_trim__emptyStr__reEmptyStr();
    str_trim__strOfSpaces__reEmptyStr();
    str_trim__noSpaces__reInStr();
    str_trim__leadingSpacesOnly__reSubstr();
    str_trim__trailingSpacesOnly__reSubstr();
    str_trim__spacesOnBothSides__reSubstr();
    str_trim__spacesInMiddle__reSubstr();

    str_slice__startingSlice__reSubstr();
    str_slice__endingSlice__reSubstr();
    str_slice__midSlice__reSubstr();
    str_slice__sliceWholeStr__reInStr();

    max__multiTest();
    min__multiTest();

    /**************************************************/
    /* ^utihttp_test.h
    /**************************************************/
    stringify_request__validRequest__expectedStr();
    stringify_request__withHeaders__expectedStr();
    stringify_request__withBody__expectedStr();

    process_response_fragment__progressComplete__returnsNegNum();
    process_response_fragment__progressNotComplete__returnsZero();
    process_response_fragment__emptyLineANDProgressNotBody__IncProgress();
    process_response_fragment__emptyLineANDProgressIsBody__progressIsBody();
    process_response_fragment__validStartLine__startLineParsed();
    process_response_fragment__badStartLine__startLineParsed();
    process_response_fragment__singleHeader__headerParsed();

    puts("ALL TESTS PASSED \\o/");
    return 0;
}