# Capstone Proejct Overview: 2 Player Snake Game 
Snake game with added features. 2 player snake game using a multithreading. Game screen is added for before and after the gameplay.

## Dependencies for Running Locally
* cmake >= 3.12
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * libsdl2-ttf packaged is required (To install for Debian-linux `sudo apt install libsdl2-ttf-dev`)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

* To play 
P1: W/S/A/D for left screen
P2: Arrow Keyboards for right screen

## Project rubric requirements
* Loops. Functions, I/O
1. Criteria - The project demonstrates an understanding of C++ functions and control structures
- It includes Game Loop approach "Input -> Update -> Render". The following approach is implemented in file in game.cpp function void Game::Run().In a game loop, while game is being played, players' keyboard inputs are handled and snakes' move and scores are updated and renders on each frame. 

2. The project reads data from a file and process the data, or the program writes data to a file.
- GetFont function(AssetManager.cpp line 43) reads font data. It reads a file located on filepath and returns a font pointer which is later to be used text texture to render on screen. 

3. The project accepts use input and processes the input.
- the program listen for user's keyboard input(Enter key). When user enters Enter key. Game starts. when the game ends, the program then wait for another keyboard input to reply the game. In game.cpp line 59, 60 and line 97 and 98, program waits for user's keyboard key input.

* Object Oriendted Programming
4. Criteria The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks
- In this project, there are 7 classes that perform task to implement 2 plyaer snake games. Game class controls game play. Only game class instance is used in main.cpp to run the program. Renderer class holds much of graphic functionality. It holds methods and variables to set up and render game graphic functionality. Controller class handles keyboards inputs. AssetManager class is a helper class that loads asset. The asset used in this program is font file. This class reads and process a file. Text class, Snake class and Food class are the entities which is rendered on screen.

5. Classes use appropriate access specifiers for class members
- There are two types of class in the program in terms of way of instantiation. In runtime, Game class, Renderer class, Controller class, AssetManger class needs to be instantiated only once. Therefore, its classes are constructed in such a way that class constructors are private specifiers and static pointers to theses classes are public specifiers. Other Classes that needs to instantiated multiple times are constructed in conventional way. In all classes, all class data members are explicitly specified as public or private.

6. Classes constructors utillze member initialization lists.
In snake.cpp line 8 and food.cpp line 9, the class utilizes member initialization list.


7. Classes abstract implementation details from their interfaces.
- In all header files, class member functinos document their effect or behavior, either through function names, comments. 


* Memory Management
8. The project uses destructors appropriately.
- In game.cpp line 17 and line 36, In render.cpp line 14 and line 68, in controller.cpp line 35, in AssetManager.cpp line 14 and line line 25, class destructor and Release() function clears memeory and set pointers to null when it is goes out of scope.

9. The project uses smart pointers instead of raw pointers.
- Controller class uses smart pointer(controller.h line 12 ~ 13) instead of raw pointer.  

* Concurrecy
10. The project uses multithreading.
- The program uses multipthreading for handling keyboard input. while main thread runs game loop and renders the screen, sub thread handles keyboard inputs which updates positions of snake entities. In game.cpp line 33, a thread is declared in constructor for Game class and joined in line 36 when destructor for Game class is called.

11. A promise and future is used in the project.
- In game.cpp(line 59 and line 97), a future is created using async() function and waits until EnterKeyReturn function(controllerc.cpp line 48) returns the value. EnterKeyReturn wait for the user the enter Enter key. 

12. A mutes or lock is used in the project.
- Thread function EnterKeyReturn(controller.cpp line 48) and HandleInpt(controller.cpp line 71) uses std::lock_guard to protect data.

