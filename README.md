# Assassins (v2)
This project runs an assassins game that involves each player receiving and attempting to "eliminate" a target.

### Purpose
This method works by using logs rather than a constantly-running server.  I wasn't confident enough in my Javascript skills to make something more complicated in the backend, but this worked great.

## Method
This project uses logs to track data across the running of the program.  The initial list, which contains all the players, is taken and randomizes the targets and builds a map of everyone and their target.  This game can be approximated as a circular, doubly-linked list.  The logs contain the current players, the player statistics for the players that have died, and the log of all events that have happened across the game.

A `Log` class contains the methods for writing to and reading from the logs.  The `Container` class (somewhat poorly named) houses the LinkedList.  An original design of this project had the container just contain the list and associated methods, but then this turned to be able to do everything in the project.  The `Player` class are the nodes in the list.

The `main()` method runs a shell that allows for the commands to be executed.  The main commands are *kill*, *wither* (kill by natural cause, mainly running out of time), *map* (printing the map), and *get* (getting player stats).

Filenames are hardcoded because they don't ever need to be changed, however, a quick BMI fix can make this changeable using command-line arguments.

## Endstate
A working game!  All the logs are kept locally and not pushed because this would compromise the game.  They may be pushed later, who knows?