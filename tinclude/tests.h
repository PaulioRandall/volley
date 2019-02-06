
/**************************************************/
/* ^uti.h
/**************************************************/
void int_to_str___1();
void int_to_str___2();

void str_copy___1();

void str_cat___1();
void str_cat___2();
void str_cat___3();

void count_substr___1();
void count_substr___2();
void count_substr___3();
void count_substr___4();

void index_of___1();
void index_of___2();
void index_of___3();

void str_split___1();
void str_split___2();
void str_split___3();
void str_split__emptyStrAtEnd__reEmptyLastStr();

void str_trim__emptyStr__reEmptyStr();
void str_trim__strOfSpaces__reEmptyStr();
void str_trim__noSpaces__reInStr();
void str_trim__leadingSpacesOnly__reSubstr();
void str_trim__trailingSpacesOnly__reSubstr();
void str_trim__spacesOnBothSides__reSubstr();
void str_trim__spacesInMiddle__reSubstr();

void str_slice__startingSlice__reSubstr();
void str_slice__endingSlice__reSubstr();
void str_slice__midSlice__reSubstr();
void str_slice__sliceWholeStr__reInStr();

void max__multiTest();
void min__multiTest();

/**************************************************/
/* ^utihttp_test.h
/**************************************************/
void stringify_request__validRequest__expectedStr();
void stringify_request__withHeaders__expectedStr();
void stringify_request__withBody__expectedStr();

void process_response_fragment__progressComplete__returnsNegNum();
void process_response_fragment__progressNotComplete__returnsZero();
void process_response_fragment__emptyLineANDProgressNotBody__IncProgress();
void process_response_fragment__emptyLineANDProgressIsBody__progressIsBody();
void process_response_fragment__validStartLine__startLineParsed();
void process_response_fragment__badStartLine__startLineParsed();
void process_response_fragment__singleHeader__headerParsed();
