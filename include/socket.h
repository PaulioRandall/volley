
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

/*****************************************************************************/
/* Identify the internet addresses of a host name and service returning the
/* result of getaddrinfo()
/*
/* hostname[]: Name of the target host
/* port[]: Number of the target hosts port
/* **addr: Result container for the details
/*****************************************************************************/
int find_addresses(
  char hostname[],
  char port[],
  struct addrinfo **addr
);

/*****************************************************************************/
/* Tries to connect to each address returning the socket descriptor once a
/* connection has been established or ERR if no connection could be made
/*
/* *addr: Addresses to connect too
/*****************************************************************************/
int try_connect(struct addrinfo *addr);

/*****************************************************************************/
/* Send data to a connected server returning 0 if successful and ERR if not
/*
/* sockfd: Socket file descriptor representing the connection
/* data[]: Data to send
/*****************************************************************************/
int send_data(int sockfd, char data[]);

/*****************************************************************************/
/* Reads a chunk of data from the server returning the number of bytes read if
/* successful, 0 indicates that the end of the stream has been hit and ERR
/* indicates an error. The amount read will be upto 'buffer_size - 1' with a
/* terminator being appended after the last byte read.
/*
/* sockfd: Socket file descriptor representing the connection
/* buf[]: Buffer to store the data
/* size: Size of the buffer
/*****************************************************************************/
int read_chunk(int sockfd, char buf[], size_t size);

/*****************************************************************************/
/* Shutsdown and closes a socket connection.
/*
/* sockfd: Socket file descriptor
/*****************************************************************************/
void close_socket(int sockfd);
