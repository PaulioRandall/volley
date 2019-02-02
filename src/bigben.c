
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
#include <stdio.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "../include/utilua.h"
#include "../include/funjson.h"
#include "../include/funhttp.h"

/* Lua */
lua_State* lua;

/*
 * Expects a filename as the first argument
 */
int main ( int argc, char *argv[] ) {

  char* script;

  if(argc != 2) {
    printf("Syntax: %s lua_script\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  script = argv[1];

  lua = luaL_newstate();
	luaL_openlibs(lua);

  /*
   * Register global constants
   */
  lua_pushinteger(lua, PRINT_INDENT_SIZE);
  lua_setglobal(lua, "INDENT_SIZE");

  /*
   * Register C/Lua functions
   */
  lua_register(lua, "ben_tabulate", ben_tabulate);
  lua_register(lua, "ben_stringify", ben_stringify);
  lua_register(lua, "ben_is_array", ben_is_array);
  lua_register(lua, "ben_is_object", ben_is_object);
  lua_register(lua, "ben_GET", ben_GET);

  luaL_dofile(lua, script);

  lua_close(lua);
  return 0;
}
