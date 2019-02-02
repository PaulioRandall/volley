
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

#define PRINT_INDENT_SIZE 2

#define STACK_TOP -1

#define TABLE_STACK_INDEX -3
#define TABLE_STACK_KEY_INDEX -2
#define TABLE_STACK_VALUE_INDEX -1

/**************************************************/
/* Validates a table is at the top of the Lua stack
/* causing a panic if not
/*
/* *lua: Lua state environment
/**************************************************/
void assert_table_on_stack(lua_State *lua);

/**************************************************/
/* Prints a lua stack trace
/*
/* *lua: Lua state environment
/**************************************************/
void print_lua_stack_trace(lua_State *lua);

/**************************************************/
/* Handles unrecoverable errors by printing them and
/* exiting the application
/*
/* *lua: Lua state environment
/**************************************************/
void panic_lua(lua_State *lua);

/**************************************************/
/* Handles unrecoverable errors by printing them and
/* exiting the application
/*
/* *lua: Lua state environment
/* msg[]: Message to print on exit
/**************************************************/
void panic(lua_State *lua, const char msg[]);

/**************************************************/
/* Validates the correct number of arguments are
/* passed to a function, an error occurs if not
/*
/* *lua: Lua state environment
/* func_name[]: Name of the C function called within
/*             a Lua script
/* expects: Number of arguments the function expects
/**************************************************/
void assert_arg_count(lua_State *lua, const char func_name[], int expects);

/**************************************************/
/* Returns the next Lua/C function argument as a
/* string; This function should only be used if no
/* pushes to the Lua stack have been made
/*
/* *lua: Lua state environment
/* msg[]: Error message to display if an error
/*        occurs
/**************************************************/
const char* pop_str_arg(lua_State *lua, char msg[]);
