# Implementation of snake game in C++

The game is inspired by the famous slither.io and follows its main concepts.

# Installation instructions for Linux

The program is compatible with both Windows and Linux, and the Makefile has been configured to support both operating systems. However, the following instructions will be detailed for Linux.



You can edit the file mixins/headers/parameters.h to adjust the options you want to modify.

Navigate to the root directory of the project and run the command:

```
make
```

* If you encounter an error stating that SFML is not installed, you need to install it. On Linux, the command is as follows:
```
sudo apt-get install libsfml-dev
```

* Once the project is compiled, start the Client:
```
./build/client 
```


* To avoid recompiling the program on other players' PCs, you can copy the build directory and run the above commands to start the game.
