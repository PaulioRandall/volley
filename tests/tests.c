
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
    int_to_str___2();

    str_copy___1();

    str_cat___1();
    str_cat___2();
    str_cat___3();

    count_substr___1();
    count_substr___2();
    count_substr___3();
    count_substr___4();

    index_of___1();
    index_of___2();
    index_of___3();

    str_split___1();
    str_split___2();
    str_split___3();
    str_split___4();

    str_trim___1();
    str_trim___2();
    str_trim___3();
    str_trim___4();
    str_trim___5();
    str_trim___6();
    str_trim___7();

    str_slice___1();
    str_slice___2();
    str_slice___3();
    str_slice___4();
    str_slice___5();

    max___multi();
    min___multi();

    /**************************************************/
    /* ^utihttp_test.h
    /**************************************************/
    stringify_request___1();
    stringify_request___2();
    stringify_request___3();

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