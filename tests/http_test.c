
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../include/uti.h"
#include "../include/http.h"
#include "../tinclude/tests.h"

struct HttpRequest* new_req() {
  struct HttpRequest *req = malloc(sizeof(struct HttpRequest));
  init_request(req);

  req->method = "GET";
  req->path = "/index.html";
  req->version = "HTTP/1.1";
  req->host = "www.example.com";
  return req;
}

struct HttpResponse* new_res() {
  struct HttpResponse *res = malloc(sizeof(struct HttpResponse));
  init_response(res);
  return res;
}

void stringify_request___1() {
  puts("...stringify_request() when given a valid request filled only"
    " with the mandatory parameters (method, path, version and host),"
    " a new string allocation is returned with the parameters"
    " formatted as a HTTP request");

  char *actual;
  struct HttpRequest *req = new_req();
  char expected[] = "GET /index.html HTTP/1.1\r\n"
                    "Host: www.example.com\r\n"
                    "\r\n";

  actual = stringify_request(req);

  assert(strcmp(expected, actual) == 0);
  free(req);
  free(actual);
}

void stringify_request___2() {
  puts("...stringify_request() when given a valid request with additional"
      " headers, a new string allocation is returned with the parameters"
      " formatted as a HTTP request");

  char *actual;
  struct HttpRequest *req = new_req();
  char expected[] = "GET /index.html HTTP/1.1\r\n"
                    "Host: www.example.com\r\n"
                    "Rince: wind\r\n"
                    "Weather: wax\r\n"
                    "\r\n";

  req->header_count = 2;
  req->headers = malloc(sizeof(struct HttpHeader) * req->header_count);
  req->headers[0].name = "Rince";
  req->headers[0].value = "wind";
  req->headers[1].name = "Weather";
  req->headers[1].value = "wax";

  actual = stringify_request(req);

  assert(strcmp(expected, actual) == 0);
  free(req->headers);
  free(req);
  free(actual);
}

void stringify_request___3() {
  puts("...stringify_request() when given a valid request with a body,"
      " a new string allocation is returned with the parameters formatted"
      " as a HTTP request that includes a 'Content-Length' header and the"
      " given body");

  char *actual;
  struct HttpRequest *req;
  char *expected = (char*) malloc(250);
  char body[] = "Counterweight continent\n" //24
                "Quirm\n" //6
                "Ankh\n" //5
                "Pseudopolis\n"; //13
  strcpy(expected, "GET /index.html HTTP/1.1\r\n"
                    "Host: www.example.com\r\n"
                    "Content-Length: 47\r\n"
                    "\r\n");
  strcat(expected, body);

  req = new_req();
  req->body = body;
  actual = stringify_request(req);

  assert(strcmp(expected, actual) == 0);
  free(expected);
  free(actual);
  free(req);
}

void process_response_fragment___1() {
  puts("...process_response_fragment() when progress is COMPLETE and given"
      " a fragment to process, ERR is returned");

  int actual;
  struct HttpResponse *res = new_res();

  res->progress = COMPLETE;
  actual = process_response_fragment(res, "Rhapsody of fire", FALSE);

  assert(ERR == actual);
  free(res);
}

void process_response_fragment___2() {
  puts("...process_response_fragment() when progress is not COMPLETE and"
      " given, a fragment to process, OK is returned");

  int actual;    
  struct HttpResponse *res = new_res();

  res->progress = BODY;
  actual = process_response_fragment(res, "Rhapsody of fire", FALSE);

  assert(OK == actual);
  free(res);
}

void process_response_fragment___3() {
  puts("...process_response_fragment() when progress is HEADER and empty line"
      " is passed, progress changes to BODY");

  struct HttpResponse *res = new_res();

  res->progress = HEADERS;
  process_response_fragment(res, "\r\nRhapsody of fire", FALSE);

  assert(BODY == res->progress);
  free(res);
}

void process_response_fragment___4() {
  puts("...process_response_fragment() when progress is BODY and empty line"
      " is passed, progress stays as BODY");

  struct HttpResponse *res = new_res();

  res->progress = BODY;
  process_response_fragment(res, "\r\nRhapsody of fire", FALSE);

  assert(BODY == res->progress);
  free(res);
}

void process_response_fragment___5() {
  puts("...process_response_fragment() when a valid start line is passed, the"
      " result container will be populated with its parsed content");

  int err;
  struct HttpResponse *res = new_res();

  err = process_response_fragment(res, "HTTP/1.1 200 OK\r\nRince: wind", FALSE);

  assert(err == OK);
  assert(strcmp(res->version, "HTTP/1.1") == 0);
  assert(res->code == 200);
  assert(strcmp(res->status, "OK") == 0);
  assert(res->progress == HEADERS);
  assert(res->header_count == 0);
  assert(res->headers == NULL);
  free(res);
}

void process_response_fragment___6() {
  puts("...process_response_fragment() when an invalid start line is passed,"
      " ERR is returned");

  int err;
  struct HttpResponse *res = new_res();
    
  err = process_response_fragment(res, "HTTP/1.1 200OK\r\n", FALSE);

  assert(err == ERR);
  free(res);
}

void process_response_fragment___7() {
  puts("...process_response_fragment() when a full valid header line is"
      " passed, OK is returned and the header has been placed into the"
      " headers list of the result container");

  int err;
  struct HttpHeader *h;
  struct HttpResponse *res = new_res();
    
  err = process_response_fragment(
    res, 
    "HTTP/1.1 200 OK\r\nRince: wind\r\n",
    FALSE
  );

  assert(err == OK);
  assert(res->header_count == 1);

  h = res->headers;
  assert(strcmp(h[0].name, "Rince") == 0);
  assert(strcmp(h[0].value, "wind") == 0);
  free_response(res);
}
