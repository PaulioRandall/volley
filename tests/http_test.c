
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

void stringify_request__validRequest__expectedStr() {
    puts("...stringify_request() valid request creates expected string");

    struct HttpRequest *req = new_req();
    char *actual, expected[] = "GET /index.html HTTP/1.1\r\n"
                                "Host: www.example.com\r\n"
                                "\r\n";

    actual = stringify_request(req);

    assert(strcmp(expected, actual) == 0);
    free(req);
    free(actual);
}

void stringify_request__withHeaders__expectedStr() {
    puts("...stringify_request() valid request with headers"
        " creates expected string");

    char *actual, expected[] = "GET /index.html HTTP/1.1\r\n"
                                "Host: www.example.com\r\n"
                                "Rince: wind\r\nWeather: wax\r\n"
                                "\r\n";
    struct HttpRequest *req = new_req();

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

void stringify_request__withBody__expectedStr() {
    puts("...stringify_request() valid request with body"
        " creates expected string");

    struct HttpRequest *req;
    char body[] = "Counterweight continent\n" //24
                "Quirm\n" //6
                "Ankh\n" //5
                "Pseudopolis\n"; //13
    char *actual, *expected = (char*) malloc(sizeof(char) * 250);
    expected[0] = '\0';
    strcat(expected, "GET /index.html HTTP/1.1\r\n"
                    "Host: www.example.com\r\n"
                    "Content-Length: 47\r\n"
                    "\r\n");
    strcat(expected, body);

    req = new_req();
    req->body = body;
    actual = stringify_request(req);

    assert(strcmp(expected, actual) == 0);
    free(expected);
    free(req);
    free(actual);
}

struct HttpResponse* new_res() {
  struct HttpResponse *res = malloc(sizeof(struct HttpResponse));
  init_response(res);
  return res;
}

void process_response_fragment__progressComplete__returnsNegNum() {
    puts("...process_response_fragment() when progress COMPLETE"
        " returned value is ERR");

    int actual;
    struct HttpResponse *res = new_res();

    res->progress = COMPLETE;
    actual = process_response_fragment(res, "Rhapsody of fire");

    assert(ERR == actual);
    free(res);
}

void process_response_fragment__progressNotComplete__returnsZero() {
    puts("...process_response_fragment() when progress not COMPLETE"
        " returned value is OK");

    int actual;    
    struct HttpResponse *res = new_res();

    res->progress = BODY;
    actual = process_response_fragment(res, "Rhapsody of fire");

    assert(OK == actual);
    free(res);
}

void process_response_fragment__emptyLineANDProgressNotBody__IncProgress() {
    puts("...process_response_fragment() when empty line passed and"
        " progress is HEADERS, progress is incremented");

    struct HttpResponse *res = new_res();

    res->progress = HEADERS;
    process_response_fragment(res, "\r\nRhapsody of fire");

    assert(BODY == res->progress);
    free(res);
}

void process_response_fragment__emptyLineANDProgressIsBody__progressIsBody() {
    puts("...process_response_fragment() when empty line passed and"
        " progress is BODY, progress is not incremented");

    struct HttpResponse *res = new_res();

    res->progress = BODY;
    process_response_fragment(res, "\r\nRhapsody of fire");

    assert(BODY == res->progress);
    free(res);
}

void process_response_fragment__validStartLine__startLineParsed() {
    puts("...process_response_fragment() when full start line passed"
        " it is parsed and values set in HttpResponse");

    int err;
    struct HttpResponse *res = new_res();

    err = process_response_fragment(res, "HTTP/1.1 200 OK\r\nRince: wind");

    assert(err == OK);
    assert(strcmp(res->version, "HTTP/1.1") == 0);
    assert(res->code == 200);
    assert(strcmp(res->status, "OK") == 0);
    assert(res->progress == HEADERS);
    free(res);
}

void process_response_fragment__badStartLine__startLineParsed() {
    puts("...process_response_fragment() when bad start line passed"
        " ERR is returned");

    int err;
    struct HttpResponse *res = new_res();
    
    err = process_response_fragment(res, "HTTP/1.1 200OK\r\n");

    assert(err == ERR);
    free(res);
}

void process_response_fragment__singleHeader__headerParsed() {
    puts("...process_response_fragment() when single header line passed"
        " OK is returned and header matches expected");

    int err;
    struct HttpHeader *h;
    struct HttpResponse *res = new_res();
    
    err = process_response_fragment(res, 
        "HTTP/1.1 200 OK\r\nRince: wind\r\n"
    );

    assert(err == OK);
    assert(res->header_count == 1);

    h = res->headers;
    assert(strcmp(h[0].name, "Rince") == 0);
    assert(strcmp(h[0].value, "wind") == 0);
    free_response(res);
}
