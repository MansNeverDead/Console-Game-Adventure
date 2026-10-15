It's main function is to show the map.

it's Inputs are the **dimensions** of the Map thus it's X and Y axis and the map itself those are received from [[Main]].

First it clears the console of whatever happened before.

tells the User to move is "Z/Q/S/D".

Afterwards it loops through the loops and uses [[Char Translator]] to translate the numbers into characters which it'll then display with **cout**. 

If the X **AND** Y of the map is equal to the player's current location, it prints H according to [[Struct Entity]].

Else it'll continue to print the basic terrains according to [[Enum Ground]].