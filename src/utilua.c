
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
#include "../include/utilua.h"

/**
 * TODO: Identify more improvements here
 * TODO: Standardise and shorten names
 * TODO: Reread Lua documentation to see if some of
 * TODO: these could be done better
 * TODO: Update styling and use char arrays where
 * TODO: instead where appropriate
 */

/**************************************************/
/* ^utilua.h
/**************************************************/
void assert_table_on_stack(lua_State *lua) {
  if(!lua_istable(lua, STACK_TOP)) {
    print_lua_stack_trace(lua);
    panic(lua, "(BUG) Expected table at top of Lua stack");
  }
}

/**************************************************/
/* ^utilua.h
/**************************************************/
void print_lua_stack_trace(lua_State *lua) {

  // TODO: Can this be simplified?

  lua_Debug debug;
  int exists, depth = 0;

  fprintf(stderr, "\n*** Stack trace ***\n");

  exists = lua_getstack(lua, depth, &debug);
  while (exists != 0) {

    lua_getinfo(lua, "nSl", &debug);

    if (strcmp(debug.what, "Lua") == 0) {
      fprintf(stderr, "%d: (Lua:%d) within '%s' of '%s'\n",
        depth,
        debug.currentline,
        (debug.name ? debug.name : "NAMELESS-HORROR"),
        debug.short_src
      );

    } else if (strcmp(debug.what, "C") == 0) {
      fprintf(stderr, "%d: (C) within '%s'\n",
        depth,
        (debug.name ? debug.name : "???")
      );

    } else {
      fprintf(stderr, "%d: (Lua:%s:%d) within '%s' of '%s'\n",
        depth,
        debug.what,
        debug.currentline,
        (debug.name ? debug.name : "NAMELESS-HORROR"),
        debug.short_src
      );
    }

    depth++;
    exists = lua_getstack(lua, depth, &debug);
  };
}

/**************************************************/
/* ^utilua.h
/**************************************************/
void panic_lua(lua_State *lua) {
  
  const char *msg;
  
  msg = lua_tostring(lua, STACK_TOP);
  fprintf(stderr, "%s\n", msg);
  lua_pop(lua, STACK_TOP);
  lua_error(lua);
}

/**************************************************/
/* ^utilua.h
/**************************************************/
void panic(lua_State *lua, const char msg[]) {
  lua_pushstring(lua, msg);
  panic_lua(lua);
}

/**************************************************/
/* ^utilua.h
/**************************************************/
void assert_arg_count(lua_State *lua, const char func_name[], int expects) {

  // TODO: How could this be simplified?

  char *msg, *panic_msg;
  int len, stack_height;

  stack_height = lua_gettop(lua);
  if(stack_height == expects) {
    return;
  }

  if(stack_height < expects) {
    msg = "%s is missing arguments, expected %d";
  } else {
    msg = "%s was given too many arguments, expected %d";
  }

  len = snprintf(NULL, 0, msg, func_name, expects);
  len++; // '\0'
  panic_msg = (char*) malloc(len);
  snprintf(panic_msg, len, msg, func_name, expects);

  print_lua_stack_trace(lua);
  panic(lua, panic_msg);
}

/**************************************************/
/* ^utilua.h
/**************************************************/
const char* pop_str_arg(lua_State *lua, char msg[]) {

  // TODO: Does lua_tostring make a copy?
  // TODO: Does it need to be freed?

  const char *result;

  if(lua_type(lua, STACK_TOP) != LUA_TSTRING) {
    print_lua_stack_trace(lua);
    panic(lua, msg);
  }

  result = lua_tostring(lua, STACK_TOP);
  lua_pop(lua, 1);

  return result;
}

/**************************************************/
/* ^utilua.h
/**************************************************/
void keyed_str_into_table(lua_State *lua, const char key[], const char value[]) {

  assert_table_on_stack(lua);

  lua_pushstring(lua, key);
  lua_pushstring(lua, value);
  lua_settable(lua, TABLE_STACK_INDEX);
}

/**************************************************/
/* ^utilua.h
/**************************************************/
void keyed_num_into_table(lua_State *lua, const char key[], const double value) {

  assert_table_on_stack(lua);

  lua_pushstring(lua, key);
  lua_pushnumber(lua, value);
  lua_settable(lua, TABLE_STACK_INDEX);
}

/**************************************************/
/* ^utilua.h
/**************************************************/
void keyed_bool_into_table(lua_State *lua, const char key[], const int value) {

  assert_table_on_stack(lua);

  lua_pushstring(lua, key);
  lua_pushboolean(lua, value);
  lua_settable(lua, TABLE_STACK_INDEX);
}

/**************************************************/
/* ^utilua.h
/**************************************************/
void indexed_str_into_table(lua_State *lua, const int index, const char value[]) {

  assert_table_on_stack(lua);

  lua_pushinteger(lua, index + 1);
  lua_pushstring(lua, value);
  lua_settable(lua, TABLE_STACK_INDEX);
}

/**************************************************/
/* ^utilua.h
/**************************************************/
void indexed_num_into_table(lua_State *lua, const int index, const double value) {

  assert_table_on_stack(lua);

  lua_pushinteger(lua, index + 1);
  lua_pushnumber(lua, value);
  lua_settable(lua, TABLE_STACK_INDEX);
}

/**************************************************/
/* ^utilua.h
/**************************************************/
void indexed_bool_into_table(lua_State *lua, const int index, const int value) {

  assert_table_on_stack(lua);

  lua_pushinteger(lua, index + 1);
  lua_pushboolean(lua, value);
  lua_settable(lua, TABLE_STACK_INDEX);
}
