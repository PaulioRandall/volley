
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
/* Deserialises a JSON string into a table
/*
/* +String: JSON as a string
/*
/* @*lua: Lua state environment
/*****************************************************************************/
int ben_tabulate(lua_State *lua);

/*****************************************************************************/
/* Formats a JSON table into a string
/*
/* +Table: JSON table
/*
/* @*lua: Lua state environment
/*****************************************************************************/
int ben_stringify(lua_State *lua);

/*****************************************************************************/
/* Returns true if the input JSON table is an array
/*
/* +Table: JSON table
/*
/* @*lua: Lua state environment
/*****************************************************************************/
int ben_is_array(lua_State *lua);

/*****************************************************************************/
/* Returns true if the input JSON table is an object
/*
/* +Table: JSON table
/*
/* @*lua: Lua state environment
/*****************************************************************************/
int ben_is_object(lua_State *lua);
