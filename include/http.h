
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

/*
 * Represents a HTTP header
 */
struct HttpHeader {
  char *name;
  char *value;
};

/*
 * Represents a HTTP request
 */
struct HttpRequest {
  char *version;
  char *method;
  char *host;
  char *path;
  struct HttpHeader *headers;
  int header_count;
  char *body;
};

/*
 * Represents the progress of the response parser
 */
enum ParseProgress {
  STATUS_LINE = 0,
  HEADERS = 1,
  BODY = 2,
  COMPLETE = 3
};

/*
 * Represents a HTTP response
 */
struct HttpResponse {
  enum ParseProgress progress;
  char *unparsed;
  char *version;
  int code;
  char *status;
  struct HttpHeader *headers;
  int header_count;
  char *body;
  int content_length;
};

/**
 * Frees a HttpHeader struct
 * 
 * @*header: HttpHeader struct to free
 */
void free_header_content(struct HttpHeader *header);

/**
 * Initialises a HttpResponse struct
 * 
 * @*response: HttpResponse struct to initialise
 */
void init_response(struct HttpResponse *res);

/**
 * Frees a HttpResponse struct
 * 
 * @*res: HttpResponse struct to free
 */
void free_response(struct HttpResponse *res);

/**
 * Initialises a HttpRequest struct
 * 
 * @*req: HttpRequest struct to initialise
 */
void init_request(struct HttpRequest *req);

/*
 * Converts the HTTP request structure into
 * a HTTP request string ready for transmission
 *
 * @*request: Request structure to convert
 */
char* stringify_request(struct HttpRequest *req);

/*
 * https://stackoverflow.com/questions/2773396/whats-the-content-length-field-in-http-header
 * READ answer by username: spender
 *
 * "The Content-Length header is a number denoting an the exact
 * byte length of the HTTP body. The HTTP body starts immediately
 * after the first empty line that is found after the start-line
 * and headers.
 *
 * Generally the Content-Length header is used for HTTP 1.1 so
 * that the receiving party knows when the current response* has
 * finished, so the connection can be reused for another request.
 *
 * * ...or request, in the case of request methods that have a body,
 * such as POST, PUT or PATCH
 *
 * Alternatively, Content-Length header can be omitted and a chunked
 * Transfer-Encoding header can be used.
 *
 * If both Content-Length and Transfer-Encoding headers are missing,
 * then at the end of the response the connection must be closed."
 * 
 * 
 * 
 * Converts chunks of the HTTP response text into a HTTP
 * response struct returning 0 if parsing was successful
 * and -1 if an error occurred. Processing is done line
 * by line ('\r\n') with the last line being placed within
 * 'HttpResponse->unparsed' so it can be processed in the
 * next call. The 'HttpResponse->progress' field is set
 * to indicate the current progress of the response parsing
 * and will be set to 'COMPLETE' (3) once the response is
 * fully built
 *
 * @*res: Represents the response entity being built
 * @*frag: Next chunk of of HTTP text to parse
 * @close: 1 if no more fragments will be passed after the
 * current call, usually because the connection to the
 * response source was closed
 */
int process_response_fragment(
  struct HttpResponse *res,
  char *frag
);