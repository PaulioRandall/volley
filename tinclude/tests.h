
/**
 * uti_test.c
 */
void int_to_str__posNum__expectedStr();
void int_to_str__negNum__expectedStr();

void str_copy__str__outputEqualsInput();

void count_substr__needleBiggerThanHaystack__returnsZero();
void count_substr__needleSameAsHaystack__returnsOne();
void count_substr__noNeedlesInHaystack__returnsZero();
void count_substr__severalNeedlesInHaystack__returnsSeveral();

void index_of__needleNotInHaystack__returnsMinusOne();
void index_of__needleInHaystack__returnsIndex();
void index_of__needleIsHaystack__returnsZero();

void null_ended_array_len__inputOfLenZero__returnsZero();
void null_ended_array_len__inputWithNonZeroLen__returnsLen();

void str_split__singleLine__returnsSingleItem();
void str_split__severalParts__returnsSplitString();
void str_split__emptyStr__returnsEmptyStr();
void str_split__emptyStrAtEnd__returnsEmptyLastStr();

void str_split_new__singleLine__returnsSingleItem();
void str_split_new__severalParts__returnsSplitString();
void str_split_new__emptyStr__returnsEmptyStr();
void str_split_new__emptyStrAtEnd__returnsEmptyLastStr();

void str_trim__emptyStr__returnsEmptyStr();
void str_trim__whitespaceStr__returnsEmptyStr();
void str_trim__leadingSpacesOnly__returnsSubstr();
void str_trim__trailingSpacesOnly__returnsSubstr();
void str_trim__spacesOnBothSides__returnsSubstr();

void str_slice__startingSlice__returnsSubstr();
void str_slice__endingSlice__returnsSubstr();
void str_slice__midSlice__returnsSubstr();
void str_slice__sliceWholeStr__returnsOriginalStr();

void str_slice_new__startingSlice__returnsSubstr();
void str_slice_new__endingSlice__returnsSubstr();
void str_slice_new__midSlice__returnsSubstr();
void str_slice_new__sliceWholeStr__returnsOriginalStr();

/**
 * utihttp_test.c
 */
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
