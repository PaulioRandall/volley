
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
#include "../include/uti.h"
#include "../include/http.h"

/**************************************************/
/* ^http.h
/**************************************************/
void free_header(struct HttpHeader *header) {
  free_header_content(header);
  free(header);
}

/**************************************************/
/* ^http.h
/**************************************************/
void free_header_content(struct HttpHeader *header) {
  free(header->name);
  free(header->value);
}

/**************************************************/
/* ^http.h
/**************************************************/
void init_response(struct HttpResponse* res) {
  res->progress = START_LINE;
  res->unparsed = NULL;
  res->version = NULL;
  res->code = ERR;
  res->status = NULL;
  res->headers = NULL;
  res->header_count = 0;
  res->body = NULL;
  res->content_length = 0;
}

/**************************************************/
/* ^http.h
/**************************************************/
void free_response(struct HttpResponse *res) {

  struct HttpHeader *h;
  int i;

  if(res->unparsed != NULL) free(res->unparsed);
  if(res->version != NULL) free(res->version);
  if(res->status != NULL) free(res->status);
  if(res->body != NULL) free(res->body);
  if(res->headers != NULL) {
    h = res->headers;
    for(i = 0; i < res->header_count; i++) {
      free_header_content(h);
      h++;
    }
    free(res->headers);
  }

  free(res);
}

/**************************************************/
/* ^http.h
/**************************************************/
void init_request(struct HttpRequest* req) {
  req->method = NULL;
  req->path = NULL;
  req->version = NULL;
  req->host = NULL;
  req->headers = NULL;
  req->header_count = 0;
  req->body = NULL;
}

/**************************************************/
/* Creates the first part of a HTTP request and
/* returns a pointer to it
/*
/* *req: Request being made
/**************************************************/
char* init_request_str(struct HttpRequest *req) {

  int len = 0;
  char *result;

  // E.g. 'GET /index.html HTTP/1.1'

  len += strlen(req->method);
  len++; // ' ' (space)
  len += strlen(req->path);
  len++; // ' ' (space)
  len += strlen(req->version);
  len += 2; // HTTP_NEWLINE
  len++; // NULL_CHAR

  result = (char*) malloc(len);

  result[0] = NULL_CHAR;
  strcat(result, req->method);
  strcat(result, " ");
  strcat(result, req->path);
  strcat(result, " ");
  strcat(result, req->version);
  strcat(result, HTTP_NEWLINE);

  return result;
}

/**************************************************/
/* Adds a header to the request string returning a
/* pointer to the result; this may be the original
/* string or a reallocation of the original
/*
/* *req_str: Request to append headers to
/* name[]: Name of the header
/* value[]: Header value
/**************************************************/
char* add_header_to_request(char *req_str, const char name[], const char value[]) {

  // E.g. Host: www.example.com

  int len = 0;

  len += strlen(req_str);
  len += strlen(name);
  len += 2; // ': ' (Colon then space)
  len += strlen(value);
  len += 2; // HTTP_NEWLINE
  len++; // NULL_CHAR

  req_str = (char*) realloc(req_str, len);

  strcat(req_str, name);
  strcat(req_str, ": ");
  strcat(req_str, value);
  strcat(req_str, HTTP_NEWLINE);

  return req_str;
}

/**************************************************/
/* Adds all user specified headers to the request
/* string returning a pointer to the result; this
/* may be the original string or a reallocation of
/* the original
/*
/* *req_str: Request string so far
/* *req: Request struct containing the headers
/**************************************************/
char* add_headers_to_request(char *req_str, struct HttpRequest *req) {

  int i;
  struct HttpHeader *h;

  for(i = 0; i < req->header_count; i++) {
    h = &req->headers[i];
    req_str = add_header_to_request(req_str, h->name, h->value);
  }

  return req_str;
}

/**************************************************/
/* Adds the body to the request string returning a
/* pointer to the result; this may be the original
/* string or a reallocation of the original
/*
/* *req_str: Request string so far
/* body[]: Body to add
/**************************************************/
char* add_body_to_request(char *req_str, const char body[]) {

  int content_len, len = 0;
  char *content_len_str;

  content_len = strlen(body);
  req_str = add_header_to_request(
    req_str,
    "Content-Length",
    int_to_str(content_len)
  );

  len += strlen(req_str);
  len += 2; // HTTP_NEWLINE
  len += content_len;
  len++; // NULL_CHAR

  req_str = (char*) realloc(req_str, len);

  strcat(req_str, HTTP_NEWLINE);
  strcat(req_str, body);

  return req_str;
}

/**************************************************/
/* Adds final termination line to request returning
/* a pointer to the result; this may be the original
/* string or a reallocation of the original
/*
/* *req_str: Request string so far
/**************************************************/
char* finialise_request(char *req_str) {

  int len;

  len = strlen(req_str);
  len += 2; // HTTP_NEWLINE
  len++; // NULL_CHAR

  req_str = (char*) realloc(req_str, len);
  strcat(req_str, HTTP_NEWLINE);

  return req_str;
}

/**************************************************/
/* ^http.h
/**************************************************/
char* stringify_request(struct HttpRequest *req) {

  char *r;

  r = init_request_str(req);
  r = add_header_to_request(r, "Host", req->host);
  r = add_headers_to_request(r, req);

  if(req->body != NULL) {
    r = add_body_to_request(r, req->body);
  } else {
    r = finialise_request(r);
  }  

  return r;
}

/**************************************************/
/* Prepends any unparsed bytes from the previous 
/* call to the current fragment
/* 
/* *res: Represents the response entity being built
/* frag[]: Next chunk of of HTTP text to parse
/**************************************************/
char* prepend_unparsed(struct HttpResponse *res, char frag[]) {

  char *r;
  int len;

  if (res->unparsed == NULL) {
    len = strlen(frag);
    len++; // NULL_CHAR
    r = (char*) malloc(len);
    strcpy(r, frag);
    return r;
  }

  r = res->unparsed;
  res->unparsed = NULL;

  len = strlen(r);
  len += strlen(frag);
  len++; // NULL_CHAR
  r = (char*) realloc(r, len);
  strcat(r, frag);

  return r;
}

/**************************************************/
/* Parses the start line returning 0 if successful
/* or ERR if an error occurred
/* 
/* *res: Represents the response entity being built
/* line[]: Start line to parse
/**************************************************/
int parse_start_line(struct HttpResponse *res, char line[]) {

  int exp_len = 3, line_len = 255, len;
  char parts[exp_len][line_len], *ch;

  // HTTP/1.1 200 OK

  len = str_split(exp_len, line_len, parts, line, " ");

  if(len != exp_len) {
    return ERR;
  }

  res->version = str_copy(parts[0]);
  res->code = strtol(parts[1], NULL, 10);
  res->status = str_copy(parts[2]);

  return OK;
}

/**************************************************/
/* Parses the string into a HttpHeader struct
/* returning a pointer to the created header
/* 
/* str[]: String to parse
/**************************************************/
struct HttpHeader* append_header(struct HttpResponse *res, char str[]) {

  int exp_len = 2, line_len = 255, len;
  char parts[exp_len][line_len], tmp[line_len];
  struct HttpHeader *h;

  len = str_split(exp_len, line_len, parts, str, ":");

  h = malloc(sizeof(struct HttpHeader));
  str_trim(tmp, parts[0]);
  h->name = str_copy(tmp);
  str_trim(tmp, parts[1]);
  h->value = str_copy(tmp);

  if(res->header_count == 0) {
    res->headers = h;
    res->header_count = 1;

  } else {
    
    // TODO: This needs fixing next, store the length instead
    // TODO: try using a struct to keep the pointer and length
    // TODO: together

    len = res->header_count;
    len++;
    res->headers = realloc(res->headers, sizeof(struct HttpHeader) * len);
    res->headers[len - 1] = *h;
    res->header_count = len;
  }

  return h;
}

/**************************************************/
/* ^http.h
/**************************************************/
int process_response_fragment(struct HttpResponse *res, char *frag, int close) {

  struct HttpResponse *r;
  struct HttpHeader *h;
  int err = 0, exp_len = 3, line_len = 255, len, i;
  char *f, lines[exp_len][line_len];

  if (res->progress == COMPLETE) {
    return ERR;
  }

  f = prepend_unparsed(res, frag);
  len = str_split(exp_len, line_len, lines, f, HTTP_NEWLINE);
  free(f);

  for(i = 0; i < len; i++) {

    if(i+1 == len && close != TRUE) {
      return OK;
    }

    f = lines[i];

    if(res->progress == BODY) {
      // TODO: str_cat(a, b) concaternates 2 strings into a 3rd string
      res->unparsed = str_copy(f);
      continue;
    }

    if(strcmp(f, "") == 0 && res->progress == HEADERS) {
      res->progress++;
      continue;
    }

    switch (res->progress) {
      case START_LINE:
        err = parse_start_line(res, f);
        if(err == ERR) {
          return ERR;
        }
        res->progress++;
        break;
      
      case HEADERS:
        h = append_header(r, f);
        // TODO: Create case insensitive string check
        // -- If the header is 'Content-length'
        // --- Set 'HttpResponse->conent_length' as the content length
        // -- Process next line
        break;
    }
  }

  // For each line except the last

  // - If the 'HttpResponse->progress' is BODY
  // -- Append the fragment to 'HttpResponse->body'
  // -- If the ('HttpResponse->body' is bigger than 
  // --+ or equal to 'HttpResponse->content_length')
  // --+ or if the argument 'close' is 1
  // --- TODO!!!!!!!
  // -- Process next line
  //
  // If the 'HttpResponse->progress' is COMPLETE
  // - 
  // Set 'HttpResponse->unparsed' to equal the last line

  return OK;
}
