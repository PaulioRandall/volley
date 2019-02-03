
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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include "lua.h"
#include "../include/uti.h"
#include "../include/utilua.h"
#include "../include/utisocket.h"
#include "../include/utihttp.h"
#include "../include/funhttp.h"

/**
 * Waits for and reads a HTTP repsonse
 * from a socket
 */
struct HttpResponse* read_response(int sockfd) {

  const int BUFFER_SIZE = 1024 * 8;
  char buffer[BUFFER_SIZE];
  size_t read;
  int status;
  struct HttpResponse *response;

  response = malloc(sizeof(response));
  init_response(response);

  while (TRUE) {
    read = read_chunk(sockfd, buffer, BUFFER_SIZE);

    if(read < 0) {
      // TODO free response and its contents
      return NULL;
    }

    if(read == 0) {
      return response;
    }

    status = process_response_fragment(response, buffer);
    if(status != 0) {
      // TODO free response and its contents
      return NULL;
    }
  }
}

/**
 * Makes a HTTP GET request
 *
 * +Table: HTTP options to send
 *
 * @*lua: Lua state environment
 */
int ben_GET(lua_State *lua) {

  struct HttpRequest request;
  struct HttpResponse *response;
  char *request_str;
  char *err_msg;
  struct addrinfo *addr = NULL;
  int status;
  int sockfd;

  assert_arg_count(lua, "ben_GET(table)", 1);

  request.version = "1.1";
  request.method = "GET";
  request.host = "localhost:8080";
  request.path = "/";
  request.headers = NULL;
  request.body = NULL;

  // Find possible network addresses
  status = find_addresses("localhost", "8080", &addr);
  if(status < 0) {  
    panic(lua, "Unable to find any addresses");
  }

  // Attempt to make a connection
  sockfd = try_connect(addr);
  free(addr);
  addr = NULL;
  if(sockfd < 0) {
    panic(lua, "Unable to connect to any of the possible addresses");
  }

  // Send the request
  request_str = stringify_request(&request);
  send_data(sockfd, request_str);
  free(request_str);

  // Read the response
  response = read_response(sockfd);

  // TEMP
  lua_newtable(lua);
  keyed_str_into_table(lua, "Hello", "Lua");

  return 1;
}
