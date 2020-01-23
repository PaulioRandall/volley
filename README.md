
# (Discontinued) Volley

\*\*\***This project is no longer active and has been archived.**\*\*\*

Volley is a small Lua embedded executable designed to do service tests for JSON based APIs and placed inside code repositories with the source code it serves.

- End to end testing
- Contract driven development
- Test driven development

This is both a learning project (C, Lua and makefiles) and experimental product. Lean development principles and continuous improvement are core to the project.

## External libraries

Parson (https://github.com/kgabis/parson) is being used for JSON serialisation.

## Prerequisites

> Written and tested on Ubuntu Linux

The Lua library (`liblua.a`) is required to build the application. This can be installed via a package manager or the source code can be downloaded, compiled and `liblua.a` installed into `/usr/local/lib` (copy/paste).

## Compile & Test

Compile and test:

```
cd tests
./test.sh
```

## Compile & Run

Compile and run:

```
cd src
make
./bigben ../scripts/test.lua
```

Build:

```
$ cd src
$ make
$ make clean
```

Run... path to a Lua script must be provided as the first argument:

```
$ ./bigben ../scripts/test.lua
```

#### Make

Task name | Action
:---: | :---
`make` | Same as `bigben`
`make bigben` | Builds the application
`make clean` | Removes all object files

## Volley Functions

Extra Lua functions, written in C, are available to aid in testing

Name | Description
:---: | :---
`ben_tabulate(string)` | Parses a JSON string into a Lua table
`ben_stringify(table)` | Serialises a Lua table representing JSON into a JSON string
`ben_is_array(table)` | Returns true if the supplied JSON table is a JSON array
`ben_is_object(table)` | Returns true if the supplied JSON table is a JSON object

#### De-serialise JSON string into a table

`ben_tabulate(string)` parses a JSON string into a Lua table

- Fails if the input string is not supplied
- Fails if the input string is nil
- Fails if the input string is not parsable JSON

```lua
json_str = [[
{
  "bool": true,
  "number": 3.14,
  "string": "Lua",
  "array": [
  "item 1",
  "item 2"
  ],
  "object": {
    "a": false,
    "b": 9.4,
    "c": "C",
  }
}
]]

json_table = ben_tabulate(json_str)
pi = json_table[number]
```

#### Stringify a JSON table

`ben_stringify(table)` takes a Lua table representing a JSON structure and serialises it into a string

- Fails if the input table is not supplied
- Fails if the input table is nil
- Fails if the input table is not, in fact, a table
- If the input table does not represent a JSON table the behaviour is undefined

```lua
json_table = wildJsonTableAppeared()

json_str = ben_stringify(json_table)
print(json_str)
```

#### Is a JSON table an array?

`ben_is_array(table)` takes a Lua table representing a JSON structure and returns true if it's a JSON array

- Fails if the input table is not supplied
- Fails if the input table is nil
- Fails if the input table is not, in fact, a table
- If the input table does not represent a JSON table the behaviour is undefined

```lua
json_table = wildJsonTableAppeared()

is_array = ben_is_array(json_table)
print("Is an array?... " .. tostring(is_array))
```

#### Is a JSON table an object?

`ben_is_object(table)` takes a Lua table representing a JSON structure and returns true if it's a JSON object

- Fails if the input table is not supplied
- Fails if the input table is nil
- Fails if the input table is not, in fact, a table
- If the input table does not represent a JSON table the behaviour is undefined

```lua
json_table = wildJsonTableAppeared()

is_object = ben_is_object(json_table)
print("Is an object?... " .. tostring(is_object))
```
