
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
#include "../include/files.h"

/*
 * ^files.h
 */
void print_file_data(struct FileData *file_data) {
  printf("File size: %d\n", file_data->size);
  printf("%s\n", file_data->data);
}

/*
 * Returns the file size of a file, the cursor
 * is reset in the process; back to the start of
 * the file
 *
 * @*fp: Pointer to an opened file
 */
int file_size(FILE *fp) {

  int size = 0;

  fseek(fp, 0L, SEEK_END);
  size = ftell(fp);
  fseek(fp, 0L, SEEK_SET);
  size++;

  return size;
}

/*
 * ^files.h
 */
struct FileData* read_file(const char *file_name) {

  FILE *fp;
  char err_str[256];
  struct FileData *result;
  size_t len;

  fp = fopen(file_name, "rb");

  if (fp == NULL) {
    sprintf(err_str, "Error opening '%s'", file_name);
    perror(err_str);
    exit(EXIT_FAILURE);
  }

  result = malloc(sizeof *result);
  result->size = file_size(fp);
  result->data = (char *) malloc(sizeof(char) * (result->size + 1));

  len = fread(result->data, 1, result->size, fp);
  result->data[len] = 0;

  fclose(fp);
  return result;
}

/*
 * ^files.h
 */
void free_file_data(struct FileData *file_data) {
  free(file_data->data);
  free(file_data);
}

/*
 * Allocates or reallocates memory for lines within a FileLines struct depending
 * on whether the supplied structure is NULL or not
 *
 * Returns a pointer to the allocated memory
 *
 * @*file_lines: FileLines struct to reallocate or NULL for a new one
 * @increment_by: Number of lines to assign or increment the size by
 */
struct FileLines* ialloc_file_lines(struct FileLines *file_lines, int increment_by) {

  int new_size = increment_by;

  if (file_lines == NULL) {
    file_lines = malloc(sizeof *file_lines);
    file_lines->size = new_size;
    file_lines->line_len = (int *) malloc(sizeof(int*) * new_size);
    file_lines->lines = (char **) malloc(sizeof(char*) * new_size);

  } else {
    new_size += file_lines->size;

    if (file_lines->size != new_size) {
      file_lines->size = new_size;
      file_lines->line_len = (int *) realloc(file_lines->line_len, sizeof(int*) * new_size);
      file_lines->lines = (char **) realloc(file_lines->lines, sizeof(char*) * new_size);
    }
  }

  return file_lines;
}

/*
 * Appends a new line to a FileLines struct by reallocating the struct and
 * copying the appending the line; the original line is NOT freed
 *
 * @*file_lines: FileLine struct to append to
 * @*line: Line to append
 * @line_len: Length of the line to append
 */
struct FileLines* append_line(struct FileLines* file_lines, char* line, int line_len) {

  char *str;
  int line_index;

  file_lines = ialloc_file_lines(file_lines, 1);
  line_index = file_lines->size - 1;

  file_lines->line_len[line_index] = line_len;
  file_lines->lines[line_index] = (char *) malloc(sizeof(char) * (line_len + 1));

  if(line_len > 0) {
    str = (char*) malloc(sizeof(char) * (line_len + 1));
    strncpy(str, line, line_len);
    str[line_len] = '\0';
    strcpy(file_lines->lines[line_index], str);
    free(str);

  } else {
    strcpy(file_lines->lines[line_index], line);
  }

  return file_lines;
}

/*
 * ^files.h
 */
struct FileLines* read_lines(const char *file_name) {

  FILE *fp;
  char err_str[256];
  struct FileLines *result = NULL;
  int line_len;
  size_t max_line_len = 1024;
  char *line;

  fp = fopen(file_name, "rb");

  if (fp == NULL) {
    sprintf(err_str, "Error opening '%s'", file_name);
    perror(err_str);
    exit(EXIT_FAILURE);
  }

  line = (char*) malloc(sizeof(char) * max_line_len);
  line_len = getline(&line, &max_line_len, fp);

  while (line_len != -1) {

    if (line_len > 1) {
      result = append_line(result, line, line_len - 1);
    } else {
      result = append_line(result, "", 0);
    }

    line_len = getline(&line, &max_line_len, fp);
  }

  free(line);

  fclose(fp);
  return result;
}

/*
 * ^files.h
 */
void print_file_lines(struct FileLines *file_lines) {
  printf("Total lines: %d\n", file_lines->size);
  for (int i = 0; i < file_lines->size; i++) {
    printf("Line %d (%d): %s\n", i + 1, file_lines->line_len[i], file_lines->lines[i]);
  }
}

/*
 * ^files.h
 */
void free_file_lines(struct FileLines *file_lines) {
  for (int i = 0; i < file_lines->size; i++) {
    free(file_lines->lines[i]);
  }
  free(file_lines->lines);
  free(file_lines->line_len);
  free(file_lines);
}
