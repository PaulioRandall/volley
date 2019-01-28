
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
#include <unistd.h>
#include "../include/utisocket.h"

/*
 * ^utisocket.h
 */
int find_addresses(
  char *hostname,
  char *port,
  struct addrinfo **addr) {

  struct addrinfo hints;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC; // Any IP version
  hints.ai_socktype = SOCK_STREAM; // TCP

  return getaddrinfo(hostname, port, &hints, addr);
}

/*
 * ^utisocket.h
 */
int try_connect(struct addrinfo *addr) {

  struct addrinfo *next;
  int sockfd;
  int connected;

  for(next = addr; next != NULL; next = next->ai_next) {

    sockfd = socket(
      next->ai_family,
      next->ai_socktype,
      next->ai_protocol
    );

    if(sockfd == -1) {
      continue;
    }

    connected = connect(
      sockfd,
      next->ai_addr,
      next->ai_addrlen
    );

    if(connected != -1) {
      return sockfd;
    }

    close(sockfd);
  }

  return -1;
}

/*
 * ^utisocket.h
 */
int send_data(int sockfd, char *data) {

  size_t total = strlen(data);
  size_t sent = 0;
  size_t next;

  while(1) {
    next = write(sockfd, data+sent, total-sent);

    if(next < 0) {
      return -1;
    }

    if(next == 0) {
      break;
    }

    sent += next;
  }

  return 0;
}

/*
 * ^utisocket.h
 */
int read_chunk(int sockfd, char* buffer, size_t buffer_size) {
  
  int result;

  memset(buffer, 0, buffer_size);
  result = read(sockfd, buffer, buffer_size - 1);

  if(result >= 0) {
    buffer[result] = '\0';
  }

  return result;
}

/*
 * ^utisocket.h
 */
void close_socket(int sockfd) {
  shutdown(sockfd, SHUT_RDWR);
	close(sockfd);
}
