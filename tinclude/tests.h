
/**************************************************/
/* ^uti.h
/**************************************************/
void int_to_str__posNum__exptStr();
void int_to_str__negNum__exptStr();

void str_copy__str__reEqualsIn();

void count_substr__needleBiggerThanHaystack__reZero();
void count_substr__needleSameAsHaystack__reOne();
void count_substr__noNeedlesInHaystack__reZero();
void count_substr__severalNeedlesInHaystack__reSeveral();

void index_of__needleNotInHaystack__reMinusOne();
void index_of__needleInHaystack__reIndex();
void index_of__needleIsHaystack__reZero();

void str_split__singleLine__reSingleItem();
void str_split__severalParts__reSplitStr();
void str_split__emptyStr__reEmptyStr();
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
