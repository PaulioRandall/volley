
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

/**
 * Represets a data file as a single string
 *
 * @size: Size of the allocated data
 * @*data: File data as a string
 */
struct FileData {
  int size;
  char *data;
};

/*
 * Prints a FileData struct
 *
 * @*file_data: Pointer to the file data
 */
void print_file_data(struct FileData *file_data);

/*
 * Reads the contents of a file as a string
 *
 * @*file_name: Pointer to a file name string
 */
struct FileData* read_file(const char *file_name);

/*
 * Frees all memory allocated to a FileData struct
 *
 * @*file_data: Pointer to the file data
 */
void free_file_data(struct FileData *file_data);

/**
 * Represets a data file as a an array of lines
 *
 * @size: Size of the allocated data
 * @*line_len: Array of line lengths
 * @**lines: Array of file lines as strings
 */
struct FileLines {
  int size;
  int *line_len;
  char **lines;
};

/*
 * Reads the contents of a file as an array of lines
 *
 * @*file_name: Pointer to a file name string
 */
struct FileLines* read_lines(const char *file_name);

/*
 * Prints a FileLines struct
 *
 * @*file_lines: Pointer to the file lines
 */
void print_file_lines(struct FileLines *file_lines);

/*
 * Frees all memory allocated to a FileLines struct
 *
 * @*file_lines: Pointer to the file lines to free
 */
void free_file_lines(struct FileLines *file_lines);
