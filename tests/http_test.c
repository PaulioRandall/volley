
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
    printf("...stringify_request() valid request creates expected string\n");
    char expected[] = "GET /index.html HTTP/1.1\r\nHost: www.example.com"
                      "\r\n\r\n";
    struct HttpRequest *req = new_req();
    char *actual = stringify_request(req);
    assert(strcmp(expected, actual) == 0);
    free(req);
    free(actual);
}

void stringify_request__withHeaders__expectedStr() {
    printf("...stringify_request() valid request with headers"
          " creates expected string\n");
    char expected[] = "GET /index.html HTTP/1.1\r\nHost: www.example.com"
                      "\r\nRince: wind\r\nWeather: wax\r\n\r\n";
    struct HttpRequest *req = new_req();
    req->header_count = 2;
    req->headers = malloc(sizeof(struct HttpHeader) * req->header_count);
    req->headers[0].name = "Rince";
    req->headers[0].value = "wind";
    req->headers[1].name = "Weather";
    req->headers[1].value = "wax";
    char *actual = stringify_request(req);
    assert(strcmp(expected, actual) == 0);
    free(req->headers);
    free(req);
    free(actual);
}

void stringify_request__withBody__expectedStr() {
    printf("...stringify_request() valid request with body"
          " creates expected string\n");
    char body[] = "Counterweight continent\n" //24
                "Quirm\r\n" //7
                "Ankh\r\n" //6
                "Pseudopolis\n"; //13
    char *expected = (char*) malloc(sizeof(char) * 250);
    expected[0] = '\0';
    strcat(expected, "GET /index.html HTTP/1.1\r\nHost: www.example.com"
                     "\r\nContent-Length: 49\r\n\r\n");
    strcat(expected, body);
    struct HttpRequest *req = new_req();
    req->body = body;
    char *actual = stringify_request(req);
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
    printf("...process_response_fragment() when progress COMPLETE"
          " returned value is -1\n");
    struct HttpResponse *res = new_res();
    res->progress = COMPLETE;
    int actual = process_response_fragment(res, "Rhapsody of fire");
    assert(-1 == actual);
    free(res);
}

void process_response_fragment__progressNotComplete__returnsZero() {
    printf("...process_response_fragment() when progress not COMPLETE"
          " returned value is 0\n");
    struct HttpResponse *res = new_res();
    res->progress = BODY;
    int actual = process_response_fragment(res, "Rhapsody of fire");
    assert(0 == actual);
    free(res);
}

void process_response_fragment__emptyLineANDProgressNotBody__IncProgress() {
    printf("...process_response_fragment() when empty line passed and"
            " progress is HEADERS, progress is incremented\n");
    struct HttpResponse *res = new_res();
    res->progress = HEADERS;
    process_response_fragment(res, "\r\nRhapsody of fire");
    enum ParseProgress actual = res->progress;
    assert(BODY == actual);
    free(res);
}

void process_response_fragment__emptyLineANDProgressIsBody__progressIsBody() {
    printf("...process_response_fragment() when empty line passed and"
            " progress is BODY, progress is not incremented\n");
    struct HttpResponse *res = new_res();
    res->progress = BODY;
    process_response_fragment(res, "\r\nRhapsody of fire");
    enum ParseProgress actual = res->progress;
    assert(BODY == actual);
    free(res);
}

void process_response_fragment__validStartLine__startLineParsed() {
    printf("...process_response_fragment() when full start line passed"
            " it is parsed and values set in HttpResponse\n");
    struct HttpResponse *res = new_res();
    int err = process_response_fragment(res, "HTTP/1.1 200 OK\r\nRince: wind");
    assert(err == 0);
    assert(strcmp(res->version, "HTTP/1.1") == 0);
    assert(res->code == 200);
    assert(strcmp(res->status, "OK") == 0);
    assert(res->progress == HEADERS);
    free(res);
}

void process_response_fragment__badStartLine__startLineParsed() {
    printf("...process_response_fragment() when bad start line passed"
            " -1 is returned\n");
    struct HttpResponse *res = new_res();
    int err = process_response_fragment(res, "HTTP/1.1 200OK\r\n");
    assert(err == -1);
    free(res);
}

void process_response_fragment__singleHeader__headerParsed() {
    printf("...process_response_fragment() when single header line passed"
            " 0 is returned and header matches expected\n");
    struct HttpResponse *res = new_res();
    int err = process_response_fragment(res, 
        "HTTP/1.1 200 OK\r\nRince: wind\r\n"
    );
    assert(err == 0);
    assert(res->header_count == 1);
    struct HttpHeader *h = res->headers;
    assert(strcmp(h[0].name, "Rince") == 0);
    assert(strcmp(h[0].value, "wind") == 0);
    free_response(res);
}
