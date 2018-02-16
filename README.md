# COMP345 Project

## How it works

### Map class

The map class consists of the map object and two nested classes, *nodes* and *links*. *Nodes* represent the individual territories, and *links* represent adjacencies.

Each *node* contains two linked lists of *links,* *links* going into the node, and *links* going out of the node. Thus, each *link* is also a part of both lists.

To manage these from outside the map class (as through a driver), all *nodes* and *links* are added to a std::map upon creation. *Nodes* use their given name as their UID, *links* use a UID in the form `${from}To${to}`.

### Map Loader

The map loader class is initialized using a Map object and a path to a text file (std::string). For examples on how the text files should be formatted, look into the "Maps" folder. When formatting the files, duplicating adjacencies (*links*) should be avoided.

The loader separates the text file into two std::stringstreams, *nodes* and *links*. Iterating through both of these strings, it first creates every *node* (adding in modifiers, terrain, and edge values), then creates all the *links*

### Dice

The dice rolls a random number from 1-6. Any number greater than 3 is converted to a 0. It stores each occurrence in an array, and returns the rolled value.

### Player

The player object is invoked with a name, Factions object, and map object. Each player starts with a default amount of Victory Points.

Picking a faction will modify the victory points accordingly, and add that faction as the player's *Primary.* If there is already a *primary,* it is set as the *secondary.* If there is already a *secondary,*, it is returned to the deck. If the *secondary* has the *spirit* power, it is instead set as *spirit*

Whenever a node is conquered by the player, that node is added to the nodes vector. Additionally, tokens will be moved from the faction to the node, and the node's race will be set.

When a node is lost, all tokens (-1) are returned to the respective faction, and the node is removed from the player's node vector.

### The deck

The deck consists of the races and powers defined in the GameConfig folder.

When initialized, both vectors are randomly shuffled, and the top 6 combinations can be queried.

Each of the 6 positions has a corresponding VP value, based on previous actions. When one of these factions is taken, a corresponding amount of VP is taken from the player and added to the pool, then given based on the faction's pool. The other values are then adjusted accordingly

When a combination is taken, it creates a faction object before removing it from the "deck."
