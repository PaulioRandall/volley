
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

#include "lua.h"
#include "../include/utilua.h"
#include "../include/utitable.h"

/**************************************************/
/* ^utitable.h
/**************************************************/
void keyed_str_into_table(lua_State *lua, const char key[], const char value[]) {

  assert_table_on_stack(lua);

  lua_pushstring(lua, key);
  lua_pushstring(lua, value);
  lua_settable(lua, TABLE_STACK_INDEX);
}

/**************************************************/
/* ^utitable.h
/**************************************************/
void keyed_num_into_table(lua_State *lua, const char key[], const double value) {

  assert_table_on_stack(lua);

  lua_pushstring(lua, key);
  lua_pushnumber(lua, value);
  lua_settable(lua, TABLE_STACK_INDEX);
}

/**************************************************/
/* ^utitable.h
/**************************************************/
void keyed_bool_into_table(lua_State *lua, const char key[], const int value) {

  assert_table_on_stack(lua);

  lua_pushstring(lua, key);
  lua_pushboolean(lua, value);
  lua_settable(lua, TABLE_STACK_INDEX);
}

/**************************************************/
/* ^utitable.h
/**************************************************/
void indexed_str_into_table(lua_State *lua, const int index, const char value[]) {

  assert_table_on_stack(lua);

  lua_pushinteger(lua, index + 1);
  lua_pushstring(lua, value);
  lua_settable(lua, TABLE_STACK_INDEX);
}

/**************************************************/
/* ^utitable.h
/**************************************************/
void indexed_num_into_table(lua_State *lua, const int index, const double value) {

  assert_table_on_stack(lua);

  lua_pushinteger(lua, index + 1);
  lua_pushnumber(lua, value);
  lua_settable(lua, TABLE_STACK_INDEX);
}

/**************************************************/
/* ^utitable.h
/**************************************************/
void indexed_bool_into_table(lua_State *lua, const int index, const int value) {

  assert_table_on_stack(lua);

  lua_pushinteger(lua, index + 1);
  lua_pushboolean(lua, value);
  lua_settable(lua, TABLE_STACK_INDEX);
}
