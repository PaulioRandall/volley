

input = [[
{
  "name": "Misty",
  "hairColour": "Chestnut",
  "age": 32,
  "employed": true,
  "drinks": [
    "tea",
    "gin"
  ],
  "favourites": {
    "food": "cheesecake",
    "shapes": {
    	"platonicSolid": "dodecahedron",
    	"regular": "star"
    }
  }
}
]]

json = ben_tabulate(input)
str = ben_stringify(json)
print(str)

print("")


is_array = ben_is_array(json["drinks"]);
is_object = ben_is_object(json["drinks"]);
print("Is 'drinks' an array? -> " .. tostring(is_array))
print("Is 'drinks' an object? -> " .. tostring(is_object))

is_array = ben_is_array(json["favourites"]);
is_object = ben_is_object(json["favourites"]);
print("Is 'favourites' an array? -> " .. tostring(is_array))
print("Is 'favourites' an object? -> " .. tostring(is_object))

print("")

req = {}
res = ben_GET(req);
print(ben_stringify(res))