#COMP345 Project

##How it works

###Map class

The map class consists of the map object and two nested classes, *nodes* and *links*. *Nodes* represent the individual territories, and *links* represent adjacencies.

Each *node* contains two linked lists of *links,* *links* going into the node, and *links* going out of the node. Thus, each *link* is also a part of both lists.

To manage these from outside the map class (as through a driver), all *nodes* and *links* are added to a std::map upon creation. *Nodes* use their given name as their UID, *links* use a UID in the form `${from}To${to}`.

###Map Loader

The map loader class is initialized using a Map object and a path to a text file (std::string). For examples on how the text files should be formatted, look into the "Maps" folder. When formatting the files, duplicating adjacencies (*links*) should be avoided.

The loader separates the text file into two std::stringstreams, *nodes* and *links*. Iterating through both of these strings, it first creates every *node* (adding in modifiers, terrain, and edge values), then creates all the *links*