
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
#include "lua.h"
#include "../include/parson.h"
#include "../include/uti.h"
#include "../include/utilua.h"
#include "../include/funjson.h"

/*****************************************************************************/
/* Copies a key value pair from the JSON object to a Lua table;
/* assumes that the value is of the type specified in the function
/* name and that a Lua table has been placed at the top of the Lua
/* stack
/*
/* @*lua: Lua state environment
/* @*obj: JSON object containing the key value pair
/* @*key: Key to the value within the JSON object
/*****************************************************************************/
void obj_str_to_table(lua_State *lua, JSON_Object *obj, const char *key);
void obj_num_to_table(lua_State *lua, JSON_Object *obj, const char *key);
void obj_bool_to_table(lua_State *lua, JSON_Object *obj, const char *key);
void obj_obj_to_table(lua_State *lua, JSON_Object *parent, const char *key);
void obj_array_to_table(lua_State *lua, JSON_Object *parent, const char *key);

/*****************************************************************************/
/* Copies a value from the JSON array and inserts it in to a Lua table;
/* assumes that the value is of the type specified in the function
/* name and that a Lua table has been placed at the top of the Lua
/* stack
/*
/* @*lua: Lua state environment
/* @*array: JSON array containing the value
/* @*index: Index of the value within the JSON object
/*****************************************************************************/
void array_str_to_table(lua_State *lua, JSON_Array *array, const int index);
void array_num_to_table(lua_State *lua, JSON_Array *array, const int index);
void array_bool_to_table(lua_State *lua, JSON_Array *array, const int index);
void array_obj_to_table(lua_State *lua, JSON_Array *array, const int index);
void array_array_to_table(lua_State *lua, JSON_Array *array, const int index);

/*****************************************************************************/
/* Creates a Lua table from the JSON entity and places
/* it at the top of the Lua stack
/*
/* @*lua: Lua state environment
/* @*obj: Object to convert
/* @*array: Array to convert
/*****************************************************************************/
void json_object_to_table(lua_State *lua, JSON_Object *obj);
void json_array_to_table(lua_State *lua, JSON_Array *array);

/*****************************************************************************/
/* Maps a primitive Lua type to a JSON type or
/* 'JSONNull' if the type could not be mapped
/*
/* @lua_type: Type of the primitive in Lua
/*****************************************************************************/
enum json_value_type lua_to_json_primitve(int lua_type);

/*****************************************************************************/
/* Returns the type of JSON table
/*
/* @*lua: Lua state environment
/*****************************************************************************/
enum json_value_type json_table_type(lua_State *lua);

/*****************************************************************************/
/* Concaternates two strings returning the result,
/* both original strings are used up in the process
/* and should not be used
/*
/* @*json: String to append to
/* @*str: String to be appended
/*****************************************************************************/
char* jsoncat(char *json, const char *str);

/*****************************************************************************/
/* Concaternates two strings returning the result,
/* both original strings are used up in the process
/* and should not be used
/*
/* @*json: Base string to append to
/* @*tmp: Template string
/* @*fmt: String or double to format with
/*****************************************************************************/
char* json_format(char *json, const char *tmp, const char *fmt);
char* json_format_double(char *json, const char *tmp, const double fmt);

/*****************************************************************************/
/* Pads the supplied string with spaces consuming it
/* in the process; the result will be returned
/*
/* @*str: String to pad
/* @amount: Amount to pad by
/*****************************************************************************/
char* pad_with_spaces(char *str, int amount);

/*****************************************************************************/
/* Formats a JSON key value pair on the stack;
/* assumes the key and value are on the stack
/*
/* @*lua: Lua state environment
/* @*json: JSON string to append to
/* @indent: Spaces to indent when printing
/* @type: JSON type of the value
/* @include_key: True if the key whould be printed for each item
/*****************************************************************************/
char* format_json_value(lua_State *lua, char *json, int indent, int include_key, enum json_value_type type);

/*****************************************************************************/
/* Formats a table or its contents as a JSON string
/*
/* @*lua: Lua state environment
/* @*json: JSON string to append too
/* @indent: Spaces to indent when printing
/* @include_key: True if the key whould be formated for each item
/*****************************************************************************/
char* format_table_iteratively(lua_State *lua, char *json, int indent, int include_key);
char* format_table_as_json(lua_State *lua, char *json, int indent, int include_key);


/*****************************************************************************/
/* ^
/*****************************************************************************/
void obj_str_to_table(lua_State *lua, JSON_Object *obj, const char *key) {

  const char *value = json_object_get_string(obj, key);
  keyed_str_into_table(lua, key, value);
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
void obj_num_to_table(lua_State *lua, JSON_Object *obj, const char *key) {

  double value = json_object_get_number(obj, key);
  keyed_num_into_table(lua, key, value);
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
void obj_bool_to_table(lua_State *lua, JSON_Object *obj, const char *key) {

  int value = json_object_get_boolean(obj, key);
  keyed_bool_into_table(lua, key, value);
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
void obj_obj_to_table(lua_State *lua, JSON_Object *parent, const char *key) {

  JSON_Object *obj;

  lua_pushstring(lua, key);
  obj = json_object_get_object(parent, key);

  json_object_to_table(lua, obj);
  lua_settable(lua, TABLE_STACK_INDEX);
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
void obj_array_to_table(lua_State *lua, JSON_Object *parent, const char *key) {

  JSON_Array *array;

  lua_pushstring(lua, key);
  array = json_object_get_array(parent, key);

  json_array_to_table(lua, array);
  lua_settable(lua, TABLE_STACK_INDEX);
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
void array_str_to_table(lua_State *lua, JSON_Array *array, const int index) {

  const char *value = json_array_get_string(array, index);
  indexed_str_into_table(lua, index, value);
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
void array_num_to_table(lua_State *lua, JSON_Array *array, const int index) {

  double value = json_array_get_number(array, index);
  indexed_num_into_table(lua, index, value);
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
void array_bool_to_table(lua_State *lua, JSON_Array *array, const int index) {

  int value = json_array_get_boolean(array, index);
  indexed_bool_into_table(lua, index, value);
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
void array_obj_to_table(lua_State *lua, JSON_Array *parent, const int index) {

  JSON_Object *obj;

  lua_pushinteger(lua, index);
  obj = json_array_get_object(parent, index);

  json_object_to_table(lua, obj);
  lua_settable(lua, TABLE_STACK_INDEX);
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
void array_array_to_table(lua_State *lua, JSON_Array *parent, const int index) {

  JSON_Array *array;

  lua_pushinteger(lua, index);
  array = json_array_get_array(parent, index);

  json_array_to_table(lua, array);
  lua_settable(lua, TABLE_STACK_INDEX);
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
void json_object_to_table(lua_State *lua, JSON_Object *obj) {

  size_t item_count;
  const char *key;
  JSON_Value *value;
  JSON_Value_Type type;
  int i;

  lua_newtable(lua);
  item_count = json_object_get_count(obj);

  for (i = 0; i < item_count; i++) {

    key = json_object_get_name(obj, i);
    value = json_object_get_value(obj, key);
    type = json_value_get_type(value);

    switch (type) {
      case JSONString:
        obj_str_to_table(lua, obj, key);
        break;

      case JSONNumber:
        obj_num_to_table(lua, obj, key);
        break;

      case JSONBoolean:
        obj_bool_to_table(lua, obj, key);
        break;

      case JSONObject:
        obj_obj_to_table(lua, obj, key);
        break;

      case JSONArray:
        obj_array_to_table(lua, obj, key);
        break;
    }
  }
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
void json_array_to_table(lua_State *lua, JSON_Array *array) {

  size_t item_count;
  const char *key;
  JSON_Value *value;
  JSON_Value_Type type;
  int i;

  lua_newtable(lua);
  item_count = json_array_get_count(array);

  for (i = 0; i < item_count; i++) {

    value = json_array_get_value(array, i);
    type = json_value_get_type(value);

    switch (type) {
      case JSONString:
        array_str_to_table(lua, array, i);
        break;

      case JSONNumber:
        array_num_to_table(lua, array, i);
        break;

      case JSONBoolean:
        array_bool_to_table(lua, array, i);
        break;

      case JSONObject:
        array_obj_to_table(lua, array, i);
        break;

      case JSONArray:
        array_array_to_table(lua, array, i);
        break;
    }
  }
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
enum json_value_type lua_to_json_primitve(int type) {

  switch (type) {
    case LUA_TSTRING:
      return JSONString;

    case LUA_TNUMBER:
      return JSONNumber;

    case LUA_TBOOLEAN:
      return JSONBoolean;
  }

  return JSONNull;
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
enum json_value_type json_table_type(lua_State *lua) {

  int index;
  int type;

  assert_table_on_stack(lua);

  index = lua_gettop(lua);
  lua_pushnil(lua);

  lua_next(lua, index);
  type = lua_type(lua, TABLE_STACK_KEY_INDEX);
  lua_pop(lua, 2);

  return type == LUA_TNUMBER ? JSONArray : JSONObject;
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
char* jsoncat(char *json, const char *str) {

  size_t len;
  char *result;

  len = strlen(json);
  len += strlen(str);
  len++;

  result = (char*) realloc(json, len);
  strcat(result, str);

  return result;
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
char* json_format(char *json, const char *tmp, const char* fmt) {

  int str_len;
  size_t result_len;
  char *str;
  char *result;

  str_len = 1 + snprintf(NULL, 0, tmp, fmt);
  str = (char*) malloc(sizeof(char) * str_len);
  snprintf(str, str_len, tmp, fmt);

  result_len = strlen(json);
  result_len += strlen(str);
  result_len++;

  result = (char*) realloc(json, result_len);
  strcat(result, str);

  free(str);

  return result;
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
char* json_format_double(char *json, const char *tmp, const double fmt) {

  int str_len;
  size_t result_len;
  char *str;
  char *result;

  str_len = 1 + snprintf(NULL, 0, tmp, fmt);
  str = (char*) malloc(sizeof(char) * str_len);
  snprintf(str, str_len, tmp, fmt);

  result_len = strlen(json);
  result_len += strlen(str);
  result_len++;

  result = (char*) realloc(json, result_len);
  strcat(result, str);

  free(str);

  return result;
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
char* pad_with_spaces(char *str, int amount) {

  int len;
  char *tmp;
  char *result;

  if(amount == 0) {
    return str;
  }

  len = 1 + snprintf(NULL, 0, "%*s", amount, "");
  tmp = (char*) malloc(sizeof(char) * len);
  snprintf(tmp, len, "%*s", amount, "");

  result = jsoncat(str, tmp);
  free(tmp);

  return result;
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
char* format_json_value(lua_State *lua, char *json, int indent, int include_key, enum json_value_type type) {

  int value;

  json = pad_with_spaces(json, indent);

  if(include_key) {
    json = json_format(json, "\"%s\": ", lua_tostring(lua, TABLE_STACK_KEY_INDEX));
  }

  switch (type) {
    case JSONString:
      json = json_format(json, "\"%s\"", lua_tostring(lua, TABLE_STACK_VALUE_INDEX));
      break;

    case JSONNumber:
      json = json_format_double(json, "%1f", lua_tonumber(lua, TABLE_STACK_VALUE_INDEX));
      break;

    case JSONBoolean:
      value = lua_toboolean(lua, TABLE_STACK_VALUE_INDEX);
      json = json_format(json, "%s", value ? "true" : "false");
      break;
  }

  return json;
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
char* format_table_iteratively(lua_State *lua, char *json, int indent, int include_key) {

  int table_index;
  int type;
  enum json_value_type js_type;
  int has_next;

  assert_table_on_stack(lua);

  table_index = lua_gettop(lua);
  lua_pushnil(lua);

  has_next = lua_next(lua, table_index);
  while (has_next == TRUE) {

    type = lua_type(lua, TABLE_STACK_VALUE_INDEX);
    js_type = lua_to_json_primitve(type);

    if(js_type == JSONNull) {
      json = format_table_as_json(lua, json, indent, include_key);
    } else {
      json = format_json_value(lua, json, indent, include_key, js_type);
    }

    lua_pop(lua, 1);
    has_next = lua_next(lua, table_index);

    if(has_next) {
      json = jsoncat(json, ",\n");
    } else {
      json = jsoncat(json, "\n");
    }
  }

  return json;
}

/*****************************************************************************/
/* ^
/*****************************************************************************/
char* format_table_as_json(lua_State *lua, char *json, int indent, int include_key) {

  enum json_value_type type;

  type = json_table_type(lua);
  json = pad_with_spaces(json, indent);

  if (include_key) {
    json = json_format(json, "\"%s\": ", lua_tostring(lua, TABLE_STACK_KEY_INDEX));
  }

  if(type == JSONArray) {
    json = jsoncat(json, "[\n");
    json = format_table_iteratively(lua, json, indent + PRINT_INDENT_SIZE, 0);
    json = pad_with_spaces(json, indent);
    json = jsoncat(json, "]");

  } else {
    json = jsoncat(json, "{\n");
    json = format_table_iteratively(lua, json, indent + PRINT_INDENT_SIZE, 1);
    json = pad_with_spaces(json, indent);
    json = jsoncat(json, "}");
  }

  return json;
}

/*****************************************************************************/
/* ^funjson.h
/*****************************************************************************/
int ben_stringify(lua_State *lua) {

  char* json;

  assert_arg_count(lua, "stringify(table)", 1);

  json = (char*) malloc(sizeof(char));
  json[0] = NULL_CHAR;
  json = format_table_as_json(lua, json, 0, 0);

  lua_pop(lua, STACK_TOP);
  lua_pushstring(lua, json);

  return 1;
}

/*****************************************************************************/
/* ^funjson.h
/*****************************************************************************/
int ben_is_array(lua_State *lua) {

  enum json_value_type type;

  assert_arg_count(lua, "ben_is_array(table)", 1);

  type = json_table_type(lua);
  lua_pop(lua, STACK_TOP);

  if(type == JSONArray) {
   lua_pushboolean(lua, 1);
  } else {
   lua_pushboolean(lua, 0);
  }

  return 1;
}

/*****************************************************************************/
/* ^funjson.h
/*****************************************************************************/
int ben_tabulate(lua_State *lua) {

  const char *input;
  JSON_Value *root;
  JSON_Object *obj;

  assert_arg_count(lua, "ben_tabulate(str)", 1);
  input = pop_str_arg(lua, "Argument must be JSON as a string");
  root = json_parse_string(input);

  if(root == NULL) {
    print_lua_stack_trace(lua);
    panic(lua, "Could not parse JSON string");
  }

  obj = json_value_get_object(root);
  json_object_to_table(lua, obj);

  json_value_free(root);

  return 1;
}

/*****************************************************************************/
/* ^funjson.h
/*****************************************************************************/
int ben_is_object(lua_State *lua) {

  enum json_value_type type;

  assert_arg_count(lua, "ben_is_object(table)", 1);

  type = json_table_type(lua);
  lua_pop(lua, STACK_TOP);

  if(type == JSONObject) {
   lua_pushboolean(lua, 1);
  } else {
   lua_pushboolean(lua, 0);
  }

  return 1;
}
