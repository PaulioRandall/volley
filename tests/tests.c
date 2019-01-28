
#include <stdio.h>
#include "../tinclude/tests.h"

int main ( int argc, char *argv[] ) {

    printf("TEST SUITE STARTED\n");

    /**
     * uti_test.c
     */
    int_to_str__posNum__expectedStr();
    int_to_str__negNum__expectedStr();

    str_copy__str__outputEqualsInput();

    count_substr__needleBiggerThanHaystack__returnsZero();
    count_substr__needleSameAsHaystack__returnsOne();
    count_substr__noNeedlesInHaystack__returnsZero();
    count_substr__severalNeedlesInHaystack__returnsSeveral();

    index_of__needleNotInHaystack__returnsMinusOne();
    index_of__needleInHaystack__returnsIndex();
    index_of__needleIsHaystack__returnsZero();

    null_ended_array_len__inputOfLenZero__returnsZero();
    null_ended_array_len__inputWithNonZeroLen__returnsLen();

    str_split__singleLine__returnsSingleItem();
    str_split__severalParts__returnsSplitString();
    str_split__emptyStr__returnsEmptyStr();
    str_split__emptyStrAtEnd__returnsEmptyLastStr();

    str_trim__emptyStr__returnsEmptyStr();
    str_trim__whitespaceStr__returnsEmptyStr();
    str_trim__leadingSpacesOnly__returnsSubstr();
    str_trim__trailingSpacesOnly__returnsSubstr();
    str_trim__spacesOnBothSides__returnsSubstr();

    str_slice__startingSlice__returnsSubstr();
    str_slice__endingSlice__returnsSubstr();
    str_slice__midSlice__returnsSubstr();
    str_slice__sliceWholeStr__returnsOriginalStr();

    /**
     * utihttp_test.c
     */
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

    printf("ALL TESTS PASSED \\o/\n");
    return 0;
}