
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

#include <stdio.h>
#include "../tinclude/tests.h"

int main ( int argc, char *argv[] ) {

  // TODO: It's probably about time to look for a proper
  // TODO: test framework, as lightweight and minimal
  // TODO: as possible and should be able to handle
  // TODO: errors and faults

  printf("TEST SUITE STARTED\n");

  /**************************************************/
  /* ^uti.h
  /**************************************************/
  int_to_str___1();
  int_to_str___2();

  str_copy___1();

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

  is_whitespace___1();
  is_whitespace___2();
  is_whitespace___3();
  is_whitespace___4();
  is_whitespace___5();
  is_whitespace___6();

  str_trim___1();
  str_trim___2();
  str_trim___3();
  str_trim___4();
  str_trim___5();
  str_trim___6();
  str_trim___7();
  str_trim___8();
  str_trim___9();
  str_trim___10();
  str_trim___11();

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

  process_response_fragment___1();
  process_response_fragment___2();
  process_response_fragment___3();
  process_response_fragment___4();
  process_response_fragment___5();
  process_response_fragment___6();
  process_response_fragment___7();
    
  puts("ALL TESTS PASSED \\o/");
  return 0;
}